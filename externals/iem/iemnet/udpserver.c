/* udpserver.c
 * copyright (c) 2010 IOhannes m zm�lnig, IEM
 * copyright (c) 2006-2010 Martin Peach
 * copyright (c) 2004 Olaf Matthes
 */

/*                                                                              */
/* A server for bidirectional communication from within Pd.                     */
/* Allows to send back data to specific clients connected to the server.        */
/*                                                                              */
/* This program is free software; you can redistribute it and/or                */
/* modify it under the terms of the GNU General Public License                  */
/* as published by the Free Software Foundation; either version 2               */
/* of the License, or (at your option) any later version.                       */
/*                                                                              */
/* This program is distributed in the hope that it will be useful,              */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of               */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                */
/* GNU General Public License for more details.                                 */
/*                                                                              */
/* You should have received a copy of the GNU General Public License            */
/* along with this program; if not, write to the Free Software                  */
/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.  */
/*                                                                              */

/* ---------------------------------------------------------------------------- */
//#define DEBUG
#include "iemnet.h"
#include <stdio.h>

#define MAX_CONNECT 32 /* maximum number of connections */

/* ----------------------------- udpserver ------------------------- */

static t_class *udpserver_class;
static const char objName[] = "udpserver";

typedef struct _udpserver_socketreceiver
{
  struct _udpserver *sr_owner;

  long           sr_host;
  unsigned short sr_port;
  t_int          sr_fd;
  t_iemnet_sender*sr_sender;
  t_iemnet_receiver*sr_receiver;
} t_udpserver_socketreceiver;

typedef struct _udpserver
{
  t_object                    x_obj;
  t_outlet                    *x_msgout;
  t_outlet                    *x_connectout;
  t_outlet                    *x_sockout; // legacy
  t_outlet                    *x_addrout; // legacy
  t_outlet                    *x_statout; 

  t_udpserver_socketreceiver  *x_sr[MAX_CONNECT]; /* socket per connection */
  t_int                       x_nconnections;

  t_int                       x_connectsocket;    /* socket waiting for new connections */
  t_int                       x_port;

  int                         x_defaulttarget; /* the default connection to send to; 0=broadcast; >0 use this client; <0 exclude this client */

  t_iemnet_receiver*x_receiver;
} t_udpserver;

static void udpserver_receive_callback(void*x, t_iemnet_chunk*,int argc, t_atom*argv);

static t_udpserver_socketreceiver *udpserver_socketreceiver_new(t_udpserver *owner, int sockfd, struct sockaddr_in*addr)
{
  t_udpserver_socketreceiver *x = (t_udpserver_socketreceiver *)getbytes(sizeof(*x));
  if(NULL==x) {
    error("%s_socketreceiver: unable to allocate %d bytes", objName, sizeof(*x));
    return NULL;
  } else {
    x->sr_owner=owner;

    x->sr_fd=sockfd;

    x->sr_host=ntohl(addr->sin_addr.s_addr);
    x->sr_port=ntohs(addr->sin_port);

    x->sr_sender=iemnet__sender_create(sockfd);
    x->sr_receiver=iemnet__receiver_create(sockfd, x, udpserver_receive_callback);
  }
  return (x);
}

static void udpserver_socketreceiver_free(t_udpserver_socketreceiver *x)
{
  DEBUG("freeing %x", x);
  if (x != NULL)
    {
      int sockfd=x->sr_fd;
      t_iemnet_sender*sender=x->sr_sender;
      t_iemnet_receiver*receiver=x->sr_receiver;



      x->sr_owner=NULL;
      x->sr_sender=NULL;
      x->sr_receiver=NULL;

      x->sr_fd=-1;

      freebytes(x, sizeof(*x));

      if(sender)  iemnet__sender_destroy(sender);
      if(receiver)iemnet__receiver_destroy(receiver);

      sys_closesocket(sockfd);
    }
  DEBUG("freeed %x", x);
}

static int udpserver_socket2index(t_udpserver*x, int sockfd)
{
  int i=0;
  for(i = 0; i < x->x_nconnections; i++) /* check if connection exists */
    {
      if(x->x_sr[i]->sr_fd == sockfd)
        {
          return i;
        }
    }  
  return -1;
}

/* checks whether client is a valid (1-based) index
 *  if the id is invalid, returns -1
 *  if the id is valid, return the 0-based index (client-1)
 */
static int udpserver_fixindex(t_udpserver*x, int client)
{
  if(x->x_nconnections <= 0)
    {
      pd_error(x, "[%s]: no clients connected", objName);
      return -1;
    }
  
  if (!((client > 0) && (client <= x->x_nconnections)))
    {
      pd_error(x, "[%s] client %d out of range [1..%d]", objName, client, x->x_nconnections);
      return -1;
    }
  return (client-1);
}


/* ---------------- udpserver info ---------------------------- */
static void udpserver_info_client(t_udpserver *x, int client)
{
  // "client <id> <socket> <IP> <port>"
  // "bufsize <id> <insize> <outsize>"
  static t_atom output_atom[4];
  if(x&&x->x_sr&&x->x_sr[client]) {
    int sockfd = x->x_sr[client]->sr_fd;
    unsigned short port   = x->x_sr[client]->sr_port;
    long address = x->x_sr[client]->sr_host;
    char hostname[MAXPDSTRING];

    int insize =iemnet__receiver_getsize(x->x_sr[client]->sr_receiver);
    int outsize=iemnet__sender_getsize  (x->x_sr[client]->sr_sender  );

    snprintf(hostname, MAXPDSTRING-1, "%d.%d.%d.%d", 
             (address & 0xFF000000)>>24,
             (address & 0x0FF0000)>>16,
             (address & 0x0FF00)>>8,
             (address & 0x0FF));
    hostname[MAXPDSTRING-1]=0;

    SETFLOAT (output_atom+0, client+1);
    SETFLOAT (output_atom+1, sockfd);
    SETSYMBOL(output_atom+2, gensym(hostname));
    SETFLOAT (output_atom+3, port);

    outlet_anything( x->x_statout, gensym("client"), 4, output_atom);

    SETFLOAT (output_atom+0, client+1);
    SETFLOAT (output_atom+1, insize);
    SETFLOAT (output_atom+2, outsize);
    outlet_anything( x->x_statout, gensym("bufsize"), 3, output_atom);
  }
}


static void udpserver_info(t_udpserver *x) {
  static t_atom output_atom[4];
  int sockfd=x->x_connectsocket;


  int port=x->x_port;

  if(sockfd<0) {
    // no open port
    error("[%s] no valid sock", objName);
  }


  if(x->x_port<=0) {
    struct sockaddr_in  server;
    socklen_t           serversize=sizeof(server);
    if(!getsockname(sockfd, (struct sockaddr *)&server, &serversize)) {
      x->x_port=ntohs(server.sin_port);
      port=x->x_port;
    } else {
      error("[%s] gesockname failed for %d", objName, sockfd);
    }
  }

  SETFLOAT (output_atom+0, port);
  outlet_anything( x->x_statout, gensym("port"), 1, output_atom);
}


static void udpserver_info_connection(t_udpserver *x, t_udpserver_socketreceiver*y)
{
  iemnet__addrout(x->x_statout, x->x_addrout, y->sr_host, y->sr_port);
  outlet_float(x->x_sockout, y->sr_fd);
}

/* ---------------- main udpserver (send) stuff --------------------- */
static void udpserver_disconnect_socket(t_udpserver *x, t_floatarg fsocket);
static void udpserver_send_bytes(t_udpserver*x, int client, t_iemnet_chunk*chunk)
{
  DEBUG("send_bytes to %x -> %x[%d]", x, x->x_sr, client);
  if(x->x_sr)DEBUG("client %X", x->x_sr[client]);
  if(x && x->x_sr && x->x_sr[client]) {
    t_atom                  output_atom[3];
    int size=0;

    t_iemnet_sender*sender=sender=x->x_sr[client]->sr_sender;
    int sockfd = x->x_sr[client]->sr_fd;

    if(sender) {
      size=iemnet__sender_send(sender, chunk);
    }

    SETFLOAT(&output_atom[0], client+1);
    SETFLOAT(&output_atom[1], size);
    SETFLOAT(&output_atom[2], sockfd);
    outlet_anything( x->x_statout, gensym("sent"), 3, output_atom);

    if(size<0) {
      // disconnected!
      udpserver_disconnect_socket(x, sockfd);
    }
  }
}



/* broadcasts a message to all connected clients but the given one */
static void udpserver_send_butclient(t_udpserver *x, int but, int argc, t_atom *argv)
{
  int client=0;
  t_iemnet_chunk*chunk=iemnet__chunk_create_list(argc, argv);

  /* enumerate through the clients and send each the message */
  for(client = 0; client < x->x_nconnections; client++)	/* check if connection exists */
    {
      /* socket exists for this client */
      if(client!=but)udpserver_send_bytes(x, client, chunk);
    }
  iemnet__chunk_destroy(chunk);
}
/* sends a message to a given client */
static void udpserver_send_toclient(t_udpserver *x, int client, int argc, t_atom *argv)
{
  t_iemnet_chunk*chunk=iemnet__chunk_create_list(argc, argv);
  udpserver_send_bytes(x, client, chunk);
  iemnet__chunk_destroy(chunk);
}



/* send message to client using client number
   note that the client numbers might change in case a client disconnects! */
/* clients start at 1 but our index starts at 0 */
static void udpserver_send_client(t_udpserver *x, t_symbol *s, int argc, t_atom *argv)
{
  int client=0;
      
  if (argc > 0)
    {
      client=udpserver_fixindex(x, atom_getint(argv));
      if(client<0)return;
      if(argc==1) {
        udpserver_info_client(x, client);
      } else {
        udpserver_send_toclient(x, client, argc-1, argv+1);
      }
      return;
    }
  else 
    {
      for(client=0; client<x->x_nconnections; client++)
        udpserver_info_client(x, client);
    }
}

/* broadcasts a message to all connected clients */
static void udpserver_broadcast(t_udpserver *x, t_symbol *s, int argc, t_atom *argv)
{
  int     client;
  t_iemnet_chunk*chunk=iemnet__chunk_create_list(argc, argv);

  /* enumerate through the clients and send each the message */
  for(client = 0; client < x->x_nconnections; client++)	/* check if connection exists */
    {
      /* socket exists for this client */
      udpserver_send_bytes(x, client, chunk);
    }
  iemnet__chunk_destroy(chunk);
}

/* broadcasts a message to all connected clients */
static void udpserver_broadcastbut(t_udpserver *x, t_symbol *s, int argc, t_atom *argv)
{
  int client=0;
  int but=-1;

  t_iemnet_chunk*chunk=NULL;

  if(argc<2) {
    return;
  }
  if((but=udpserver_fixindex(x, atom_getint(argv)))<0)return;
  udpserver_send_butclient(x, but, argc-1, argv+1);
}

static void udpserver_defaultsend(t_udpserver *x, t_symbol *s, int argc, t_atom *argv)
{
  int client=-1;
  int sockfd=x->x_defaulttarget;
  if(0==sockfd) 
    udpserver_broadcast(x, s, argc, argv);
  else if(sockfd>0) {
    client=udpserver_socket2index(x, sockfd);
    udpserver_send_toclient(x, client, argc, argv);
  } else if(sockfd<0) {
    client=udpserver_socket2index(x, -sockfd);
    udpserver_send_butclient(x, client, argc, argv);     
  }
}
static void udpserver_defaulttarget(t_udpserver *x, t_floatarg f)
{
  int sockfd=0;
  int rawclient=f;
  int client=(rawclient<0)?(-rawclient):rawclient;

  if(client > x->x_nconnections) {
    error("[%s] target %d out of range [0..%d]", objName, client,  x->x_nconnections);
    return;
  }

  // map the client to a persistant socket
  if(client>0) {
    sockfd=x->x_sr[client-1]->sr_fd;
  }

  if(rawclient<0)sockfd=-sockfd;  

  x->x_defaulttarget=sockfd;
}
static void udpserver_targetsocket(t_udpserver *x, t_floatarg f)
{
  int sockfd=f;
  x->x_defaulttarget=sockfd;
}



/* send message to client using socket number */
static void udpserver_send_socket(t_udpserver *x, t_symbol *s, int argc, t_atom *argv)
{
  int     client = -1;
  t_iemnet_chunk*chunk=NULL;
  if(argc) {
    client = udpserver_socket2index(x, atom_getint(argv));
    if(client<0)return;
  } else {
    pd_error(x, "%s_send: no socket specified", objName);
    return;
  }

  /* get socket number of connection (first element in list) */
  if(argc && argv->a_type == A_FLOAT)
    {
      int sockfd=atom_getint(argv);
      client = udpserver_socket2index(x, sockfd);
      if(client < 0)
        {
          error("[%s]: no connection on socket %d", objName, sockfd);
          return;
        }
    }
  else
    {
      error("[%s]: no socket specified", objName);
      return;
    }
  
  chunk=iemnet__chunk_create_list(argc-1, argv+1);
  udpserver_send_bytes(x, client, chunk);
  iemnet__chunk_destroy(chunk);
}

static void udpserver_disconnect(t_udpserver *x, int client)
{
  int k;
  DEBUG("disconnect %x %d", x, client);
  udpserver_info_connection(x, x->x_sr[client]);

  udpserver_socketreceiver_free(x->x_sr[client]);
  x->x_sr[client]=NULL;

  /* rearrange list now: move entries to close the gap */
  for(k = client; k < x->x_nconnections; k++)
    {
      x->x_sr[k] = x->x_sr[k + 1];
    }
  x->x_sr[k + 1]=NULL;
  x->x_nconnections--;


  outlet_float(x->x_connectout, x->x_nconnections);
}


/* disconnect a client by number */
static void udpserver_disconnect_client(t_udpserver *x, t_floatarg fclient)
{
  int client = udpserver_fixindex(x, fclient);

  if(client<0)return;
  udpserver_disconnect(x, client);
}


/* disconnect a client by socket */
static void udpserver_disconnect_socket(t_udpserver *x, t_floatarg fsocket)
{
  int id=udpserver_socket2index(x, (int)fsocket);
  if(id>=0)
    udpserver_disconnect_client(x, id+1);
}



/* disconnect a client by socket */
static void udpserver_disconnect_all(t_udpserver *x)
{
  int id=x->x_nconnections;
  while(--id>=0) {
    udpserver_disconnect(x, id);
  }
}

/* ---------------- main udpserver (receive) stuff --------------------- */
static void udpserver_receive_callback(void *y0, 
				       t_iemnet_chunk*c, 
				       int argc, t_atom*argv) {
  t_udpserver_socketreceiver *y=(t_udpserver_socketreceiver*)y0;
  t_udpserver*x=NULL;
  if(NULL==y || NULL==(x=y->sr_owner))return;
  
  if(argc) {
    udpserver_info_connection(x, y);
    iemnet__streamout(x->x_msgout, argc, argv);
  } else {
    // disconnected
    int sockfd=y->sr_fd;
    udpserver_disconnect_socket(x, sockfd);
  }

  //  error("[%s]: %d bytes in %d packets", objName, bytecount, packetcount);
}

static void udpserver_connectpoll(t_udpserver *x)
{
  struct sockaddr_in  incomer_address;
  unsigned int        sockaddrl = sizeof( struct sockaddr );
  int                 fd = accept(x->x_connectsocket, (struct sockaddr*)&incomer_address, &sockaddrl);
  int                 i;

  if (fd < 0) error("[%s] accept failed", objName);
  else
    {
      t_udpserver_socketreceiver *y = udpserver_socketreceiver_new((void *)x, fd, &incomer_address);
      if (!y)
        {
          sys_closesocket(fd);
          return;
        }
      x->x_nconnections++;
      i = x->x_nconnections - 1;
      x->x_sr[i] = y;

      udpserver_info_connection(x, y);
    }

  outlet_float(x->x_connectout, x->x_nconnections);
}

static void udpserver_port(t_udpserver*x, t_floatarg fportno)
{
  static t_atom ap[1];
  int                 portno = fportno;
  struct sockaddr_in  server;
  socklen_t           serversize=sizeof(server);
  int sockfd = x->x_connectsocket;
  SETFLOAT(ap, -1);
  if(x->x_port == portno) {
    return;
  }

  /* cleanup any open ports */
  if(sockfd>=0) {
    sys_rmpollfn(sockfd);
    sys_closesocket(sockfd);
    x->x_connectsocket=-1;
    x->x_port=-1;
  }


  sockfd = socket(AF_INET, SOCK_DGRAM, 0);


  server.sin_family = AF_INET;

  /* LATER allow setting of inaddr */
  server.sin_addr.s_addr = INADDR_ANY;

  /* assign server port number */
  server.sin_port = htons((u_short)portno);
  /* name the socket */
  if (bind(sockfd, (struct sockaddr *)&server, serversize) < 0)
    {
      sys_sockerror("udpserver: bind");
      sys_closesocket(sockfd);
      outlet_anything(x->x_statout, gensym("port"), 1, ap);
      return;
    }

  x->x_receiver=iemnet__receiver_create(sockfd,
					x, 
					udpserver_receive_callback);


  x->x_connectsocket = sockfd;
  x->x_port = portno;


  // find out which port is actually used (useful when assigning "0")
  if(!getsockname(sockfd, (struct sockaddr *)&server, &serversize)) {
    x->x_port=ntohs(server.sin_port);
  }


  SETFLOAT(ap, x->x_port);
  outlet_anything(x->x_statout, gensym("port"), 1, ap);
}

static void *udpserver_new(t_floatarg fportno)
{
  t_udpserver         *x;
  int                 i;

  x = (t_udpserver *)pd_new(udpserver_class);

  x->x_msgout = outlet_new(&x->x_obj, 0); /* 1st outlet for received data */
  x->x_connectout = outlet_new(&x->x_obj, gensym("float")); /* 2nd outlet for number of connected clients */
  x->x_sockout = outlet_new(&x->x_obj, gensym("float"));
  x->x_addrout = outlet_new(&x->x_obj, gensym("list" ));
  x->x_statout = outlet_new(&x->x_obj, 0);/* 5th outlet for everything else */


  x->x_connectsocket = -1;
  x->x_port = -1;
  x->x_nconnections = 0;

  for(i = 0; i < MAX_CONNECT; i++)
    {
      x->x_sr[i] = NULL;
    }

  x->x_defaulttarget=0;

  udpserver_port(x, fportno);

  return (x);
}

static void udpserver_free(t_udpserver *x)
{
  int     i;

  for(i = 0; i < MAX_CONNECT; i++)
    {
      if (NULL!=x->x_sr[i]) {
        DEBUG("[%s] free %x", objName, x);
        udpserver_socketreceiver_free(x->x_sr[i]);
        x->x_sr[i]=NULL;
      }
    }
  if (x->x_connectsocket >= 0)
    {
      sys_rmpollfn(x->x_connectsocket);
      sys_closesocket(x->x_connectsocket);
    }
}

IEMNET_EXTERN void udpserver_setup(void)
{
  if(!iemnet__register(objName))return;
  error("[%s] does not work yet", objName);

  udpserver_class = class_new(gensym(objName),(t_newmethod)udpserver_new, (t_method)udpserver_free,
                              sizeof(t_udpserver), 0, A_DEFFLOAT, 0);
  class_addmethod(udpserver_class, (t_method)udpserver_disconnect_client, gensym("disconnectclient"), A_DEFFLOAT, 0);
  class_addmethod(udpserver_class, (t_method)udpserver_disconnect_socket, gensym("disconnectsocket"), A_DEFFLOAT, 0);
  class_addmethod(udpserver_class, (t_method)udpserver_disconnect_all, gensym("disconnect"), 0);

  class_addmethod(udpserver_class, (t_method)udpserver_send_socket, gensym("send"), A_GIMME, 0);
  class_addmethod(udpserver_class, (t_method)udpserver_send_client, gensym("client"), A_GIMME, 0);

  class_addmethod(udpserver_class, (t_method)udpserver_broadcast, gensym("broadcast"), A_GIMME, 0);

  class_addmethod(udpserver_class, (t_method)udpserver_defaulttarget, gensym("target"), A_DEFFLOAT, 0);
  class_addmethod(udpserver_class, (t_method)udpserver_targetsocket, gensym("targetsocket"), A_DEFFLOAT, 0);
  class_addlist  (udpserver_class, (t_method)udpserver_defaultsend);


  class_addmethod(udpserver_class, (t_method)udpserver_port, gensym("port"), A_DEFFLOAT, 0);
  class_addbang  (udpserver_class, (t_method)udpserver_info);
}

IEMNET_INITIALIZER(udpserver_setup);


/* end of udpserver.c */