
/* 1309:forum::f�r::uml�ute:2000 */

/*
  sort :  sort a package of floats
*/

#include "zexy.h"

/* ------------------------- sort ------------------------------- */

/*
SHELL SORT: simple and easy
*/

static t_class *sort_class;

typedef struct _sort
{
  t_object x_obj;

  int bufsize;
  t_float *buffer;

  int ascending;
} t_sort;


static void sort_dir(t_sort *x, t_float f)
{
    x->ascending = (f < 0.f)?0:1;
}

static void sort_buffer(t_sort *x, int argc, t_atom *argv)
{
  int n = argc;
  t_float *buf;
  t_atom *atombuf = argv;

  if (argc != x->bufsize) {
    if (x->buffer) freebytes(x->buffer, x->bufsize * sizeof(t_float));
    x->bufsize = argc;
    x->buffer = getbytes(x->bufsize * sizeof(t_float));
  }

  buf = x->buffer;
  while (n--)
    *buf++ = atom_getfloat(atombuf++);
}

static void sort_list(t_sort *x, t_symbol *s, int argc, t_atom *argv)
{
  int step = argc, n;
  t_atom *atombuf = (t_atom *)getbytes(sizeof(t_atom) * argc);
  t_float *buf;

  int i, loops = 1;

  sort_buffer(x, argc, argv);
  buf = x->buffer;

  while (step > 1) {
    step = (step % 2)?(step+1)/2:step/2;

    //    i = loops++;
    i = loops;
    loops += 2;

    while(i--) { /* there might be some optimization in here */
      for (n=0; n<(argc-step); n++) {
	if (buf[n] > buf[n+step]) {
	  t_float dummy = buf[n];
	  buf[n]        = buf[n+step];
	  buf[n+step]   = dummy;
	}
      }
    }
  }

  if (x->ascending) 
    for (n = 0; n < argc; n++) SETFLOAT(&atombuf[n], buf[n]);
  else
    for (n = 0, i=argc-1; n < argc; n++, i--) SETFLOAT(&atombuf[n], buf[i]);

  outlet_list(x->x_obj.ob_outlet, &s_list, n, atombuf);

  freebytes(atombuf, sizeof(atombuf));
}

static void *sort_new(t_floatarg f)
{
  t_sort *x = (t_sort *)pd_new(sort_class);
  x->ascending = (f < 0.f)?0:1;

  outlet_new(&x->x_obj, &s_list);

  x->bufsize = 0;
  x->buffer = NULL;

  inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("direction"));

  return (x);
}

void z_sort_setup(void)
{
  sort_class = class_new(gensym("sort"), (t_newmethod)sort_new, 
			      0, sizeof(t_sort), 0, A_DEFFLOAT,  0);
  
  class_addlist    (sort_class, sort_list);
  class_addmethod   (sort_class, (t_method)sort_dir, gensym("direction"), A_DEFFLOAT, 0);

  class_sethelpsymbol(sort_class, gensym("zexy/sort"));
}
