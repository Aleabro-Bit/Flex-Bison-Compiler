#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define MAX_SCOPE_DEPTH 128

extern int yylineno; /* from lexer */
extern FILE *yyin; 
void yyerror(const char *s, ...);

typedef struct value {
    int type;               // Type of value: 1 = number, 2 = string, 3 = list
    union {
        double number;       
        char *string;  
        struct list *list;      
    } data;
}val_t;

struct list {
    val_t *value;            // Value of the element
    struct list *next;    // Pointer to next element
};

/* symbol table */
struct symbol { /* a variable name */
 char *name;
 double value;
 struct ast *func; /* stmt for the function */
 struct symlist *syms; /* list of dummy args */
 int type;
 char *string;
 struct list *list;
};

/* list of symbols, for an argument list */
struct symlist {
 struct symbol *sym;
 struct symlist *next;
};

enum bifs { /* built-in functions */
    B_sqrt = 1,
    B_exp,
    B_log,
    B_print,
    B_fact,
    B_sin,
    B_cos,
    B_tan,
    B_size,  
    B_get,
    B_input,
    B_split,
    B_casual,
   /* B_get2D, */
    B_count_char
    
};

/* Nodes in the abstract syntax tree */
struct ast {
    int nodetype;          // Kind of node (es. 'F', 'V', 'N', etc.)
    struct ast *l;         /* left child */
    struct ast *r;         /* right child */
    union {                
        char *s;           /* string value for string nodes */
        double number;     /* Value for constant nodes */
        struct symbol *sym; // Riferimento al simbolo (per variabili o funzioni)
        enum bifs functype; /* built-in functions */
        struct {           /* control flow */
            struct ast *cond; /* condition */
            struct ast *tl;   /* then branch or do list */
            struct ast *el;   /* optional else branch */
        } flow;
    
    } data;
};


/* Symbol table functions */
struct symbol *lookup(char*);
struct symbol *declare(char*);
struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
void print_symtab();

struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newdeclare(struct symbol *name);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newstr (char *s);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
struct ast *newfor(struct ast *init, struct ast *cond, struct ast *inc, struct ast *body);
/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);
/* evaluate an AST */
val_t eval(struct ast *);
/* optimize the AST */
void optimize_ast(struct ast *node);
/* delete and free an AST */
void treefree(struct ast *);
void print_ast(struct ast *node, int depth, char *prefix);

/* Functions */
double roman_to_int(const char *roman);
void print_val(val_t val);
double factorial(double n);
void print_func(struct ast *arg);
val_t split(val_t v);

/* Linked List Functions*/
void print_list(struct list *lst);
struct list *linked_list_ast(struct ast *args);
int list_length(struct list *head);
val_t *get(struct list *head, int index);
val_t *get2D(struct list *head, int row, int col);
struct list *concat_lists(struct list *head1, struct list *head2);
val_t count_char(val_t v);

/* Scope*/
typedef struct scope {
    struct symbol *symtab;  
    int symtab_size;
    int symtab_count;
} scope_t;

void push_scope();
void pop_scope();
void print_all_scopes();





