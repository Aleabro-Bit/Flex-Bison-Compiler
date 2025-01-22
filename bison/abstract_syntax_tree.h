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


/* Nodes in the abstract syntax tree */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
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

/* Build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r) {
    struct ast *a = (struct ast *)malloc(sizeof(struct ast));
    if (!a) {
        yyerror("Out of memory");
        exit(1);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newnum(double d) {
    struct numval *a = (struct numval *)malloc(sizeof(struct numval));
    if (!a) {
        yyerror("Out of memory");
        exit(1);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct ast *)a;
}

struct ast *newcmp(int cmptype, struct ast *l, struct ast *r)
{
    struct ast *a = (struct ast *)malloc(sizeof(struct ast));
    if(!a) {
    yyerror("out of space");
    exit(0);
    }
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newfunc(int functype, struct ast *l)
{
 struct fncall *a = malloc(sizeof(struct fncall));

 if(!a) {
 yyerror("out of space");
 exit(0);
 }
 a->nodetype = 'F';
 a->l = l;
 a->functype = functype;
 return (struct ast *)a;
}

struct ast *newcall(struct symbol *s, struct ast *l)
{
 struct ufncall *a = malloc(sizeof(struct ufncall));

 if(!a) {
 yyerror("out of space");
 exit(0);
 }
 a->nodetype = 'C';
 a->l = l;
 a->s = s;
 return (struct ast *)a;
}

struct ast *newref(struct symbol *s)
{
 struct symref *a = malloc(sizeof(struct symref));

 if(!a) {
 yyerror("out of space");
 exit(0);
 }
 a->nodetype = 'N';
 a->s = s;
 return (struct ast *)a;
}

struct ast *newasgn(struct symbol *s, struct ast *v)
{
 struct symasgn *a = malloc(sizeof(struct symasgn));
if(!a) {
 yyerror("out of space");
 exit(0);
 }
 a->nodetype = '=';
 a->s = s;
 a->v = v;
 return (struct ast *)a;
}

struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
 struct flow *a = malloc(sizeof(struct flow));

 if(!a) {
 yyerror("out of space");
 exit(0);
 }
 a->nodetype = nodetype;
 a->cond = cond;
 a->tl = tl;
 a->el = el;
 return (struct ast *)a;
}

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
void symlistfree(struct symlist *sl)
{
 struct symlist *nsl;
 while(sl) {
 nsl = sl->next;
 free(sl);
 sl = nsl;
 }
}

/* Evaluate an AST */
double eval(struct ast *a) {
    double v;

    switch (a->nodetype) {
    case 'K': /* constant */
        v = ((struct numval *)a)->number;
        break;

    case '+': /* addition */
        v = eval(a->l) + eval(a->r);
        break;

    case '-': /* subtraction */
        v = eval(a->l) - eval(a->r);
        break;

    case '*': /* multiplication */
        v = eval(a->l) * eval(a->r);
        break;

    case '/': /* division */
        v = eval(a->l) / eval(a->r);
        break;
    case '|': /* absolute value */

    v = eval(a->l); if(v < 0) v = -v; break;

    case 'M': /* unary minus */
    v = -eval(a->l); break;
    default:
        yyerror("Unknown nodetype: %c", a->nodetype);
        v = 0;
    }

    return v;
}

/* Delete and free an AST */
void treefree(struct ast *a) {
    if (!a) return;

    switch (a->nodetype) {
    /* two subtrees */
    case '+':
    case '-':
    case '*':
    case '/':
        treefree(a->r);
        break;
    /* one subtree */
    case '|': 
    case 'M':
        treefree(a->l);
    /* no subtree */
    case 'K':
        free(a);
        break;

    default:
        yyerror("Unknown nodetype: %c", a->nodetype);
    }

    free(a);
}

/* Error reporting function */
void yyerror(const char *s, ...) {
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: Error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
