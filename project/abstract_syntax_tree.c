# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "abstract_syntax_tree.h"

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];

/* symbol table */
/* hash a symbol */
static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while(c = *sym++) hash = hash*9 ^ c;
    return hash;
}

/* lookup symbol */
struct symbol *lookup(char* sym)
{
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) { 
            return sp;  /* symbol found*/
        }
        if(!sp->name) { /* new entry */
            sp->name = strdup(sym);
            sp->value = 0;
            sp->type = 0;
            sp->func = NULL;
            sp->syms = NULL;
            return sp; /* new entry */
        }
        if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

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

/* Build a number AST node */
struct ast *newnum(double d) {
    struct ast *a = (struct ast *)malloc(sizeof(struct ast));
    if (!a) {
        yyerror("Out of memory");
        exit(1);
    }
    a->nodetype = 'K'; // 'K' for "constant"
    a->data.number = d;
    a->l = NULL;
    a->r = NULL;
    return a;
}

/* build a comparison AST node */
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r)
{
    struct ast *a = newast('0' + cmptype, l, r); // '0' + cmptype represents comparison
    return a;
}
/* build a declaration node */
struct ast *newdeclare(struct symbol *name, struct symlist *args, struct ast *body) {
    name->syms = args;
    name->func = body;
    struct ast *a = newast('D', NULL, NULL);
    a->data.sym = name;
    return a;
}

/* build a function call AST node */
struct ast *newfunc(int functype, struct ast *l)
{
    struct ast *a = newast('F', l, NULL); // 'F' for built-in function
    a->data.functype = functype;
    return a;
}

/* build a user function call AST node */
struct ast *newcall(struct symbol *s, struct ast *l)
{
    struct ast *a = newast('C', l, NULL); // 'C' for user function call
    a->data.sym = s;
    return a;
}

/* create a reference to a symbol*/
struct ast *newref(struct symbol *s)
{
struct ast *a = newast('N', NULL, NULL); // 'N' for name reference
    a->data.sym = s;
    return a;
}

/* create an assignment node */
struct ast *newasgn(struct symbol *s, struct ast *v)
{
    struct ast *a = newast('=', v, NULL); // '=' for assignment
    a->data.sym = s;
    return a;
}

/* build a flow control AST node */
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
    struct ast *a = newast(nodetype, NULL, NULL);
    a->data.flow.cond = cond;
    a->data.flow.tl = tl;
    a->data.flow.el = el;
    return a;
}

/* build a string AST node */
struct ast *newstr(char *s) {
    struct ast *a = malloc(sizeof(struct ast));
    if (!a) {
        yyerror("out of space");
        exit(1);
    }
    a->nodetype = 'S'; 
    a->data.sym = (struct symbol*)strdup(s); // Store the string as symbol name
    free(s); // Free the original string
    return a;
}

/* Create a symbol list */
struct symlist *newsymlist(struct symbol *sym, struct symlist *next)
{
 struct symlist *sl = (struct symlist*)malloc(sizeof(struct symlist));

 if(!sl) {
 yyerror("out of space");
 exit(1);
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

/* free a tree of ASTs */
void treefree(struct ast *a)
{
    if (!a) return;
    switch(a->nodetype) {
        /* two subtrees */
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': 
        case 'L':
            treefree(a->r);
        /* one subtree */
        case '|': case 'M': case 'C': case 'F':
            treefree(a->l);
        /* no subtree */
        case 'K': case 'N': 
            break;
        case 'S': 
            if (a->data.sym) free(a->data.sym); 
            break;
        case '=':
            treefree(a->l);
            break;
        /* up to three subtrees */
        case 'I': case 'W':
            treefree(a->data.flow.cond);
            if (a->data.flow.tl) treefree(a->data.flow.tl);
            if (a->data.flow.el) treefree(a->data.flow.el);
            break;
        default: 
            printf("internal error: free bad node %c\n", a->nodetype);
    }

    free(a); /* always free the node itself */
}

static double callbuiltin(struct ast *);
static double calluser(struct ast *);

double eval(struct ast *a)
{
    double v;

    if(!a) {
    yyerror("internal error, null eval");
    exit(1);
    }

    switch(a->nodetype) {
        /* constant */
        case 'K': 
            v = a->data.number; 
            break;
        /* string */
        case 'S': 
                printf("String: %s\n", a->data.sym->name);
                return 0.0;
        /* name reference */
        case 'N': 
            v = a->data.sym->value; 
            break;
        /* assignment */
        case '=': 
            struct symbol *sym = a->data.sym;
            double val = eval(a->l);

            if ((sym->type == 1 && a->l->nodetype != 'K') || // Numeric type mismatch
                    (sym->type == 2 && a->l->nodetype != 'S')) { // String type mismatch
                    yyerror("Type mismatch for variable '%s'", sym->name);
                    return 0.0;
                }

            // Assign value
            v = sym->value; 
            break;
        /* expressions */
        case '+': v = eval(a->l) + eval(a->r); break;
        case '-': v = eval(a->l) - eval(a->r); break;
        case '*': v = eval(a->l) * eval(a->r); break;
        case '/': v = eval(a->l) / eval(a->r); break;
        case '|': v = fabs(eval(a->l)); break;
        case '^': v = pow(eval(a->l), eval(a->r)); break; 
        case 'M': v = -eval(a->l); break;
        /* comparisons */
        case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;
        case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;
        case '3': v = (eval(a->l) != eval(a->r))? 1 : 0; break;
        case '4': v = (eval(a->l) == eval(a->r))? 1 : 0; break;
        case '5': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;
        case '6': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;
        /* control flow */
        /* null expressions allowed in the grammar, so check for them */
        /* if/then/else */
        case 'I':
            if( eval( a->data.flow.cond) != 0) { 
                v = a->data.flow.tl ? eval(a->data.flow.tl) : 0.0;
            } else {
                v = a->data.flow.el ? eval(a->data.flow.el) : 0.0;
            } 
            break;
        /* while/do */
        case 'W':
        v = 0.0; /* a default value */
        if(a->data.flow.tl) {
            while( eval(a->data.flow.cond) != 0) 
                v = eval(a->data.flow.tl); 
        }
        break; /* value of last statement is value of while/do */

        /* list of statements */
        case 'L': eval(a->l); v = eval(a->r); break;
        case 'F': v = callbuiltin(a); break;
        case 'C': v = calluser(a); break;
        default: printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

static double callbuiltin(struct ast *a)
{
    enum bifs functype = a->data.functype;
    double v = eval(a->l);

    switch(functype) {
        case B_sqrt:
            return sqrt(v);
        case B_exp:
            return exp(v);
        case B_log:
            return log(v);
        case B_print:
            printf("= %4.4g\n", v);
        return v;
        default:
            yyerror("Unknown built-in function %d", functype);
            return 0.0;
 }
}

/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *func)
{
 if(name->syms) symlistfree(name->syms);
 if(name->func) treefree(name->func);
 name->syms = syms;
 name->func = func;
}

static double calluser(struct ast *a)
{
    struct symbol *fn = a->data.sym; /* function name */
    struct symlist *sl; /* dummy arguments */
    struct ast *args = a->l; /* actual arguments */
    double *oldval, *newval; /* saved arg values */
    double v;
    int nargs, i;
    if(!fn->func) {
    yyerror("call to undefined function", fn->name);
    return 0;
    }
    /* count the arguments */
    sl = fn->syms;
    for(nargs = 0; sl; sl = sl->next)
    nargs++;
    /* prepare to save them */
    oldval = (double *)malloc(nargs * sizeof(double));
    newval = (double *)malloc(nargs * sizeof(double));
    if(!oldval || !newval) {
    yyerror("Out of space in %s", fn->name); return 0.0;
    }

    /* evaluate the arguments */
    for(i = 0; i < nargs; i++) {
        if(!args) {
            yyerror("too few args in call to %s", fn->name);
            free(oldval); free(newval);
        return 0.0;
        }
        if(args->nodetype == 'L') { /* if this is a list node */
            newval[i] = eval(args->l);
            args = args->r;
        } else { /* if it's the end of the list */
            newval[i] = eval(args);
            args = NULL;
        }
    }

    /* save old values of dummies, assign new ones */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl->next;
    }
    free(newval);
    /* evaluate the function */
    v = eval(fn->func);
    /* put the real values of the dummies back */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        s->value = oldval[i];
        sl = sl->next;
    }
    free(oldval);
    return v;
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

// Funzione ricorsiva per stampare l'AST
void print_ast(struct ast *node, int depth, char *prefix) {
    if (!node) return;

    // Stampa prefisso e tipo di nodo
    printf("%s%sNode type: '%c'", prefix, (depth == 0) ? "Root -> " : "|__ ", node->nodetype);

    // Aggiungi dettagli in base al tipo di nodo
    switch (node->nodetype) {
        case 'K': printf(", Value: %f\n", node->data.number); break;
        case 'N': printf(", Variable: %s, Value: %f\n", node->data.sym->name, node->data.sym->value); break;
        case '=': printf(", Assignment to: %s\n", node->data.sym->name); break;
        case 'F': printf(", Built-in Function: %d\n", node->data.functype); break;
        case 'C': printf(", User Function: %s\n", node->data.sym->name); break;
        case 'I': printf(" (If/Else)\n"); break;
        case 'W': printf(" (While Loop)\n"); break;
        default: printf("\n"); break;
    }

    // Costruisci il nuovo prefisso
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, (depth == 0) ? "" : "    ");

    // Gestione figli e flussi di controllo
    if (node->nodetype == 'I' || node->nodetype == 'W') {
        if (node->data.flow.cond) {
            printf("%s|__ Condition:\n", new_prefix);
            print_ast(node->data.flow.cond, depth + 1, new_prefix);
        }
        if (node->data.flow.tl) {
            printf("%s|__ Then branch:\n", new_prefix);
            print_ast(node->data.flow.tl, depth + 1, new_prefix);
        }
        if (node->data.flow.el) {
            printf("%s|__ Else branch:\n", new_prefix);
            print_ast(node->data.flow.el, depth + 1, new_prefix);
        }
    } else {
        if (node->l) print_ast(node->l, depth + 1, new_prefix);
        if (node->r) print_ast(node->r, depth + 1, new_prefix);
    }
}
