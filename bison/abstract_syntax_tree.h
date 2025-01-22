#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* Declarations for a calculator fb3-1 */
/* Interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(const char *s, ...);

/* Nodes in the abstract syntax tree */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval {
    int nodetype; /* type 'K' for constant */
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
