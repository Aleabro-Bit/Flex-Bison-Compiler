# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "abstract_syntax_tree.h"


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

struct ast *newfor(struct ast *init, struct ast *cond, struct ast *step, struct ast *body) {
    // Nodo che combina il corpo del ciclo con lo step
    struct ast *body_with_step = malloc(sizeof(struct ast));
    if (!body_with_step) {
        yyerror("Out of space");
        exit(1);
    }
    body_with_step->nodetype = 'L'; // Node of the list
    body_with_step->l = body;      // Body of the cycle
    body_with_step->r = step;      // Step 

    // Nodo del ciclo `for`
    struct ast *fornode = malloc(sizeof(struct ast));
    if (!fornode) {
        yyerror("Out of space");
        exit(1);
    }
    fornode->nodetype = 'T';            // Nodo `F` per il ciclo `for`
    fornode->l = init;                  // Inizializzazione
    fornode->data.flow.cond = cond;     // Condizione
    fornode->r = body_with_step;        // Corpo + Step
    return fornode;
}

/* build a return AST node */
struct ast *newreturn(int nodetype, struct ast *value) {
    struct ast *node = malloc(sizeof(struct ast));
    if (!node) {
        yyerror("out of space");
        exit(1);
    }
    node->nodetype = nodetype;  
    node->l = value;       
    node->r = NULL;        
    return node;
}

/* build a string AST node */
struct ast *newstr(char *s) {
struct ast *a = malloc(sizeof(struct ast));
    if (!a) {
        yyerror("out of space");
        exit(1);
    }
    a->nodetype = 'S'; // String node
    a->data.s = strdup(s); // Save the string in the node
    free(s); 
    if (!a->data.s) {
        yyerror("out of space for string");
        exit(1);
    }
    return a;
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
        case '&':
        case 'O':
        case '1': case '2': case '3': case '4': case '5': case '6': 
        case 'L':
            treefree(a->r);
        /* one subtree */
        case '|': case 'M': case 'C': case 'F': case '!':
            treefree(a->l);
        /* no subtree */
        case 'K': case 'N': case 'D':
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

static val_t callbuiltin(struct ast *);
static val_t calluser(struct ast *);
static double factorial(double n);
void print_func(struct ast *arg);

val_t eval(struct ast *a)
{
    val_t v;
    v.type = 0; // Default type is number
    v.data.number = 0.0; // Default value is 0.0

    if(!a) {
    yyerror("internal error, null eval");
    exit(1);
    }

    switch(a->nodetype) {
        /* constant */
        case 'K': 
            v.type = 0; // Number
            v.data.number = a->data.number; 
            break;
        /* string */
        case 'S': 
            v.type = 1; // String
            v.data.string = strdup(a->data.s);
            break;
        /* name reference */
        case 'N': 
            struct symbol *sym = a->data.sym;
            if (sym->type == 2) { //string
                v.type = 1;
                v.data.string = strdup(sym->name);
            } else {
                v.type = 0; // Number
                v.data.number = sym->value;
            }
            break;
        /* declaration */
        case 'D':
            //Variable declaration is handled during parsing; nothing to be done here
            v.type = 0;
            v.data.number = 0.0;
            break;
        /* assignment */
        case '=': 
            {
            struct symbol *sym = a->data.sym; // Symbol being assigned

            if (a->l == NULL) {
                // Variable declaration without initialization
                if (sym->type == 1) { 
                    sym->value = 0.0; // Default value for numeric type
                } else if (sym->type == 2) {
                    sym->value = 0.0; // Default "dummy" value for strings (or handle differently)
                    sym->name = "";   // Or set to a valid default string value
                } 
                // Add handling for other types if needed
                v.type = sym->type - 1;
                v.data.number = sym->value;
                v.data.string = strdup(sym->name);
                break;
            }
            
            val_t val = eval(a->l);         // Evaluate the expression on the left-hand side

            // Handle assignment from another variable
            if (a->l->nodetype == 'N') { 
                struct symbol *source_sym = a->l->data.sym;
                // Check if types of source and destination symbols match
                if (source_sym->type != sym->type) {
                    yyerror("Type mismatch between variable '%s' and '%s'", sym->name, source_sym->name);
                    return v = (val_t){.type = 1, .data.number = 0.0};
                }
            } 
            // Handle numeric assignment (constant, variable, or expression)
            else if (sym->type == 1) { 
                if (a->l->nodetype != 'K' && a->l->nodetype != 'N' &&
                    a->l->nodetype != '+' && a->l->nodetype != '-' &&
                    a->l->nodetype != '*' && a->l->nodetype != '/' &&
                    a->l->nodetype != '^' && a->l->nodetype != 'M') {
                    yyerror("Invalid numeric assignment to variable '%s'", sym->name);
                    return v = (val_t){.type = 1, .data.number = 0.0};
                }
            }
            // Handle string assignment
            else if (sym->type == 2) {
                if (a->l->nodetype != 'S' && a->l->nodetype != 'N') {
                    yyerror("Invalid string assignment to variable '%s'", sym->name);
                    return v = (val_t){.type = 1, .data.number = 0.0};
                }
            }
            // TODO: add additional types if needed

            // Assign value
            sym->value = val.data.number; 
            v.data.number = sym->value; 
            break;
        }
        
        /* expressions */
        case '+': {
            val_t left = eval(a->l);
            val_t right = eval(a->r);
            
            if (left.type != right.type) {
                yyerror("Type mismatch in '+' operation");
                return v;
            }

            if (left.type == 0) { // Numbers
                v.type = 0;
                v.data.number = left.data.number + right.data.number;
            } else if (left.type == 1) { // Strings (concatenation)
                size_t len = strlen(left.data.string) + strlen(right.data.string) + 1;
                v.type = 1;
                v.data.string = malloc(len);
                snprintf(v.data.string, len, "%s%s", left.data.string, right.data.string);
            }
            break;
        }
        case '-': 
        case '*': 
        case '/': 
        case '^': {
            val_t left = eval(a->l);
            val_t right = eval(a->r);

            if (left.type != right.type) {
                yyerror("Type mismatch operation");
                return v;
            }
            if (left.type == 1|| right.type == 1) {
                yyerror("Invalid operands to arithmetic operator: both must be numbers");
                exit(1);
            }

            v.type = 0;
            switch (a->nodetype) {
                case '-': v.data.number = left.data.number - right.data.number; break;
                case '*': v.data.number = left.data.number * right.data.number; break;
                case '/': v.data.number = left.data.number / right.data.number; break;
                case '^': v.data.number = pow(left.data.number, right.data.number); break;
            }
            break;
        }
        case '|': {
            v.type = 0;
            v.data.number = fabs(eval(a->l).data.number); break;
        }

        case 'M': {
            v.type = 0;
            v.data.number = -eval(a->l).data.number; break;
        }
        case '!': {
            if(!a->l) {
                yyerror("Invalid operands to 'not' operator");
                exit(1);
            }
            v.data.number = !(eval(a->l).data.number); break;
        }
        /* comparisons */
        case '1': // Greater than
        case '2': // Less than
        case '3': // Not equal
        case '4': // Equal
        case '5': // Greater than or equal
        case '6': // Less than or equal
        case 'O': // Logical OR
        case '&': // Logical AND
        {
            val_t left = eval(a->l);
            val_t right = eval(a->r);

            if (left.type != right.type) {
                yyerror("Type mismatch for comparison");
                return v;
            }

            v.type = 0;
            switch (a->nodetype) {
                case '1': v.data.number = (left.data.number > right.data.number) ? 1 : 0; break;
                case '2': v.data.number = (left.data.number < right.data.number) ? 1 : 0; break;
                case '3': v.data.number = (left.data.number != right.data.number) ? 1 : 0; break;
                case '4': v.data.number = (left.data.number == right.data.number) ? 1 : 0; break;
                case '5': v.data.number = (left.data.number >= right.data.number) ? 1 : 0; break;
                case '6': v.data.number = (left.data.number <= right.data.number) ? 1 : 0; break;
                case 'O': v.data.number = (left.data.number || right.data.number) ? 1 : 0; break;
                case '&': v.data.number = (left.data.number && right.data.number) ? 1 : 0; break;
            }
            break;
        }
        
        /* control flow */
        /* null expressions allowed in the grammar, so check for them */
        /* if/then/else */
        case 'I':
            val_t cond_val = eval(a->data.flow.cond);
            if (cond_val.data.number != 0) { 
                v = a->data.flow.tl ? eval(a->data.flow.tl) : (val_t){.type = 0, .data.number = 0.0};
            } else {
                v = a->data.flow.el ? eval(a->data.flow.el) : (val_t){.type = 0, .data.number = 0.0};
            } 
            break;
        /* while/do */
        case 'W':
        v.data.number = 0; /* a default value */
        if(a->data.flow.tl) {
            while( eval(a->data.flow.cond).data.number != 0) 
                v = eval(a->data.flow.tl); 
        }
        break; /* value of last statement is value of while/do */

        /* for loop */
        case 'T': 
        eval(a->l); // Initialize

            while (eval(a->data.flow.cond).data.number != 0) { // Controlla condizione
                eval(a->r->l); // Esegui corpo
                eval(a->r->r); // Esegui step
            }
            break;
        
        /* list of statements */
        case 'L': 
        if (a->l) eval(a->l);
        if (a->r) v = eval(a->r);
        break;
        case 'F': v = callbuiltin(a); break;
        case 'C': v = calluser(a); break;
        default: printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

/* built-in functions */
static val_t callbuiltin(struct ast *a)
{
    enum bifs functype = a->data.functype;
    val_t v = eval(a->l);
    val_t result = {.type = 0, .data.number = 0.0}; // Default return value

    switch(functype) {
        case B_sqrt:
            result.data.number = sqrt(v.data.number);
            return result;
        case B_exp:
            result.data.number = exp(v.data.number);
            return result;
        case B_log:
            result.data.number = log(v.data.number);
            return result;
        case B_print:
            struct ast *arg = a->l; // Node to initialize the argument
            print_func(arg);
            break;
        case B_fact:
            result.data.number = factorial(v.data.number);
            return result;
        case B_sin:
            result.data.number = sin(v.data.number);
            return result;
        case B_cos:
            result.data.number = cos(v.data.number);
            return result;
        case B_tan:
            result.data.number = tan(v.data.number);
            return result;
        default:
            yyerror("Unknown built-in function %d", functype);
            return result = (val_t){.type = 0, .data.number = 0.0};
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

static val_t calluser(struct ast *a) {
    struct symbol *fn = a->data.sym; /* Nome della funzione */
    struct symlist *sl; /* Argomenti fittizi */
    struct ast *args = a->l; /* Argomenti reali */
    val_t *oldval, *newval; /* Valori salvati degli argomenti */
    val_t v = {0}; /* Valore di ritorno inizializzato */
    int nargs, i;

    if (!fn->func) {
        yyerror("Call to undefined function: %s", fn->name);
        return v = (val_t){.type = 0, .data.number = 0.0};
    }

    /* Conta il numero di argomenti */
    sl = fn->syms;
    for (nargs = 0; sl; sl = sl->next)
        nargs++;

    /* Prepara a salvare i valori */
    oldval = (val_t *)malloc(nargs * sizeof(val_t));
    newval = (val_t *)malloc(nargs * sizeof(val_t));
    if (!oldval || !newval) {
        yyerror("Out of space in %s", fn->name);
        return v = (val_t){.type = 0, .data.number = 0.0};
    }

    /* Valuta gli argomenti */
    for (i = 0; i < nargs; i++) {
        if (!args) {
            yyerror("Too few args in call to %s", fn->name);
            free(oldval);
            free(newval);
            return v = (val_t){.type = 0, .data.number = 0.0};
        }
        if (args->nodetype == 'L') { /* Se è un nodo di lista */
            newval[i] = eval(args->l);
            args = args->r;
        } else { /* Fine della lista */
            newval[i] = eval(args);
            args = NULL;
        }
    }

    /* Salva i vecchi valori degli argomenti e assegna i nuovi */
    sl = fn->syms;
    for (i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i].data.number = s->value; /* Salva il vecchio valore */
        s->value = newval[i].data.number; /* Assegna il nuovo valore */
        sl = sl->next;
    }
    free(newval);

    /* Valuta la funzione */
    v = eval(fn->func);

    /* Ripristina i valori originali degli argomenti */
    sl = fn->syms;
    for (i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        s->value = oldval[i].data.number;
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

void print_val(val_t val) {
    switch (val.type) {
        case 0: // Numeric type
            printf("Number: %.6f\n", val.data.number);
            break;
        case 1: // String type
            printf("String: %s\n", val.data.string);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

/* recursive function to print the abstract syntax tree */
void print_ast(struct ast *node, int depth, char *prefix) {
    if (!node) return;

    // Print node prefix
    printf("%s%sNode type: '%c'", prefix, (depth == 0) ? "Root -> " : "|__ ", node->nodetype);
    val_t result = eval(node); // Evaluate the node to get its result

    // Add details based on the node type
    switch (node->nodetype) {
        case 'K': // Constant value
            printf(", Value: %f\n", node->data.number);
            break;

        case 'N': // Variable
            if (node->data.sym->name == "str") { // String variable
                printf(", Variable: %s, Value (string): \"%s\"\n", node->data.sym->name, node->data.s);
            } else { // Numeric variable
                printf(", Variable: %s, Value (number): %f\n", node->data.sym->name, node->data.sym->value);
            }
            break;

        case '=': // Assignment
            printf(", Assignment to: %s\n", node->data.sym->name);
            break;

        case 'F': // Built-in function
            printf(", Built-in Function: %d\n", node->data.functype);
            break;

        case 'C': // User-defined function
            printf(", User Function: %s\n", node->data.sym->name);
            break;

        case 'S': // String literal
            printf(", String: \"%s\"\n", node->data.s);
            break;

        case '+': case '-': case '*': case '/': // Arithmetic operations
            printf(", Operation result: %f\n", result.data.number);
            break;

        case 'I': // If/Else
            printf(" (If/Else)\n");
            break;

        case 'W': // While loop
            printf(" (While Loop)\n");
            break;

        case 'T': // For loop
            printf(" (For Loop)\n");
            break;

        default:
            printf("\n");
            break;
    }

    // Create a new prefix for child nodes
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, (depth == 0) ? "" : "    ");

    // Handle control flow nodes and their branches
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
        // Print left and right children
        if (node->l) print_ast(node->l, depth + 1, new_prefix);
        if (node->r) print_ast(node->r, depth + 1, new_prefix);
    }
}


int roman_to_int(const char *roman) {
    int result = 0;
    while (*roman) {
        switch (*roman) {
            case '0': break;
            case 'M': result += 1000; break;
            case 'D': result += 500; break;
            case 'C': 
                if (*(roman + 1) == 'M' || *(roman + 1) == 'D') result -= 100;
                else result += 100;
                break;
            case 'L': result += 50; break;
            case 'X': 
                if (*(roman + 1) == 'C' || *(roman + 1) == 'L') result -= 10;
                else result += 10;
                break;
            case 'V': result += 5; break;
            case 'I': 
                if (*(roman + 1) == 'X' || *(roman + 1) == 'V') result -= 1;
                else result += 1;
                break;
            default: return -1; // Invalid Roman numeral
        }
        roman++;
    }
    return result;
}

static double factorial(double n) {
    if (n < 0) return NAN; // Undefined for negative numbers
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= (int)n; i++) {
        result *= i;
    }
    return result;
}

void print_func(struct ast *arg) {
                while (arg) {
                val_t value = eval(arg); // Evaluate the argument

                if (value.type == 0) {
                    // Print numbers
                    printf("%g", value.data.number);
                } else if (value.type == 1) {
                    // Print strings
                    printf("%s", value.data.string);
                } else {
                    yyerror("Unsupported type in print");
                }

                // Next argument
                arg = arg->r;
                if (arg) {
                    // Print a space if more arguments are coming
                    printf(" ");
                }
            }
            printf("\n"); // Newline at the end
}
