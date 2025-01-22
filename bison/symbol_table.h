#include <stdlib.h>
/* interface to the lexer */
extern int yylineno; /* from lexer */
/* symbol table */
struct symbol { /* a variable name */
 char *name;
 double value;
 struct ast *func; /* stmt for the function */
 struct symlist *syms; /* list of dummy args */
};
/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char*);
/* list of symbols, for an argument list */
struct symlist {
 struct symbol *sym;
 struct symlist *next;
};
struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);
enum bifs { /* built-in functions */
 B_sqrt = 1,
 B_exp,
 B_log,
 B_print
};
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
 struct symlist *sl = malloc(sizeof(struct symlist));

 if(!sl) {
 yyerror("out of space");
 exit(0);
 }
 sl->sym = sym;
 sl->next = next;
 return sl;
}
/* free a list of symbols */
voidsymlistfree(struct symlist *sl)
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

