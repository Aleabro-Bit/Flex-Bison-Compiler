#include <stdlib.h>
#include "abstract_syntax_tree.h"

/* nodes in the abstract syntax tree */
/* all have common initial nodetype */
struct ast {
 int nodetype;
 struct ast *l;
 struct ast *r;
};
struct fncall { /* built-in function */
 int nodetype; /* type F */
 struct ast *l;
 enum bifs functype;
};
struct ufncall { /* user function */
 int nodetype; /* type C */
 struct ast *l; /* list of arguments */
 struct symbol *s;
};
struct flow {
int nodetype; /* type I or W */
 struct ast *cond; /* condition */
 struct ast *tl; /* then branch or do list */
 struct ast *el; /* optional else branch */
};
struct numval {
 int nodetype; /* type K */
 double number;
};
struct symref {
 int nodetype; /* type N */
 struct symbol *s;
};
struct symasgn {
 int nodetype; /* type = */
 struct symbol *s;
 struct ast *v; /* value */
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next)
{
 struct symlist *sl = (struct symlist *)malloc(sizeof(struct symlist));

 if(!sl) {
 yyerror("out of space");
 exit(0);
 }
 sl->sym = sym;
 sl->next = next;
 return sl;
}
/* free a list of symbols */
void symlistfree(struct symlist *sl)
{
 struct symlist *nsl;
 while(sl) {
 nsl = sl->next;
 free(sl);
 sl = nsl;
 }
}

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);
/* evaluate an AST */
double eval(struct ast *);
/* delete and free an AST */
void treefree(struct ast *);
/* interface to the lexer */
extern int yylineno; /* from lexer */

