/* Copyright (c) 2003 krzYszcz and others.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

#ifndef __SCRIPTLET_H__
#define __SCRIPTLET_H__

enum { SCRIPTLET_OK = 0, SCRIPTLET_NOFILE, SCRIPTLET_BADFILE,
       SCRIPTLET_IGNORED };

EXTERN_STRUCT _scriptlet;
#define t_scriptlet  struct _scriptlet

typedef t_canvas *(*t_scriptlet_cvfn)(t_pd *);
typedef t_scriptlet *(*t_scriptlet_cmntfn)(t_pd *, char *, char, char *);

int scriptlet_isempty(t_scriptlet *sp);
void scriptlet_reset(t_scriptlet *sp);
void scriptlet_prealloc(t_scriptlet *sp, int sz, int mayshrink);
int scriptlet_add(t_scriptlet *sp,
		  int resolveall, int visedonly, int ac, t_atom *av);
int scriptlet_addstring(t_scriptlet *sp, char *ibuf,
			int resolveall, int visedonly,
			int ac, t_atom *av, t_props *argprops);
int scriptlet_addfloat(t_scriptlet *sp, t_float f);
void scriptlet_setseparator(t_scriptlet *sp, char c);
void scriptlet_push(t_scriptlet *sp);
void scriptlet_qpush(t_scriptlet *sp);
void scriptlet_vpush(t_scriptlet *sp, char *varname);
int scriptlet_evaluate(t_scriptlet *insp, t_scriptlet *outsp,
		       int visedonly, int ac, t_atom *av, t_props *argprops);
char *scriptlet_nextword(char *buf);
int scriptlet_rcload(t_scriptlet *sp, char *rc, char *ext,
		     t_scriptlet_cmntfn cmntfn);
int scriptlet_read(t_scriptlet *sp, t_symbol *fn);
int scriptlet_write(t_scriptlet *sp, t_symbol *fn);
char *scriptlet_getcontents(t_scriptlet *sp, int *lenp);
char *scriptlet_getbuffer(t_scriptlet *sp, int *sizep);
void scriptlet_clone(t_scriptlet *to, t_scriptlet *from);
void scriptlet_free(t_scriptlet *sp);
t_scriptlet *scriptlet_new(t_pd *owner, t_symbol *rptarget, t_symbol *cbtarget,
			   t_symbol *item, t_scriptlet_cvfn cvfn);

#endif
