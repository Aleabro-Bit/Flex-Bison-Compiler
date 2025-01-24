#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern int yylineno; /* from lexer */
void yyerror(const char *s, ...);

/* symbol table */
struct symbol { /* a variable name */
 char *name;
 double value;
 struct ast *func; /* stmt for the function */
 struct symlist *syms; /* list of dummy args */
};

struct symbol *lookup(char*);
/* list of symbols, for an argument list */
struct symlist {
 struct symbol *sym;
 struct symlist *next;
};

enum bifs { /* built-in functions */
 B_sqrt = 1,
 B_exp,
 B_log,
 B_print
};

/* Nodes in the abstract syntax tree */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
    char *s;
};

struct fncall { /* built-in function */
 int nodetype; /* type built in function call */
 struct ast *l;
 enum bifs functype;
};
struct ufncall { 
 int nodetype; /* user function call */
 struct ast *l; /* list of arguments */
 struct symbol *s;
};
struct flow {
int nodetype; /* type IF or While */
 struct ast *cond; /* condition */
 struct ast *tl; /* then branch or do list */
 struct ast *el; /* optional else branch */
};
struct symref {
 int nodetype; /* symbol ref */
 struct symbol *s;
};
struct symasgn {
 int nodetype; /* type = */
 struct symbol *s;
 struct ast *v; /* value */
};

struct numval {
    int nodetype; /* constant */
    double number;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);


/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newstr (char *s);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);
/* evaluate an AST */
double eval(struct ast *);
/* delete and free an AST */
void treefree(struct ast *);


