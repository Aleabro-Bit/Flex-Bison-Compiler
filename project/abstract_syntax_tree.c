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
        case 'I': case 'W': case 'T':
            treefree(a->data.flow.cond);
            if (a->data.flow.tl) treefree(a->data.flow.tl);
            if (a->data.flow.el) treefree(a->data.flow.el);
            break;
        default: 
            printf("internal error: free bad node %c\n", a->nodetype);
    }

    free(a); /* always free the node itself */
}

/* factorial built in function*/
static double factorial(double n) {
    if (n < 0) return NAN; // Undefined for negative numbers
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= (int)n; i++) {
        result *= i;
    }
    return result;
}

/* print built in function */
void print_func(struct ast *arg) {            
    val_t value = eval(arg); // Evaluate the argument
    if (value.type == 1) {
        // Print numbers
        printf("%g", value.data.number);
    } else if (value.type == 2) {
        // Print strings
        printf("%s", value.data.string);
    } else {
        yyerror("Unsupported type in print");
    }
    if (arg) {
        // Print a space if more arguments are coming
        printf("\n");
    }
}

/* built-in functions */
static val_t callbuiltin(struct ast *a)
{
    enum bifs functype = a->data.functype;
    val_t v = eval(a->l);
    val_t result = {.type = 1, .data.number = 0.0}; // Default return value

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
            return result = (val_t){.type = 1, .data.number = 0.0};
 }
}

static val_t calluser(struct ast *a) {
    struct symbol *fn = a->data.sym; /* Name of the function */
    struct symlist *sl; /* Dummy arguments */
    struct ast *args = a->l; /* Real arguments */
    val_t *oldval, *newval; /* saved values of the arguments */
    val_t v = {0}; 
    int nargs, i;

    if (!fn->func) {
        yyerror("Call to undefined function: %s", fn->name);
        return v = (val_t){.type = 1, .data.number = 0.0};
    }

    /* Count number of arguments */
    sl = fn->syms;
    for (nargs = 0; sl; sl = sl->next)
        nargs++;

    /* Save values */
    oldval = (val_t *)malloc(nargs * sizeof(val_t));
    newval = (val_t *)malloc(nargs * sizeof(val_t));
    if (!oldval || !newval) {
        yyerror("Out of space in %s", fn->name);
        return v = (val_t){.type = 1, .data.number = 0.0};
    }

    /* Evaluate arguments */
    for (i = 0; i < nargs; i++) {
        if (!args) {
            yyerror("Too few args in call to %s", fn->name);
            free(oldval);
            free(newval);
            return v = (val_t){.type = 1, .data.number = 0.0};
        }
        if (args->nodetype == 'L') { /* If it's a list node */
            newval[i] = eval(args->l);
            args = args->r;
        } else { /* End of list */
            newval[i] = eval(args);
            args = NULL;
        }
    }
    /* Save old values and assign new values*/
    sl = fn->syms;
    for (i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i].data.number = s->value; /* Save old value */
        s->value = newval[i].data.number; /* Assign new value */
        sl = sl->next;
    }
    free(newval);

    /* Evaluate function */
    v = eval(fn->func);

    /* Recover original value of arguments */
    sl = fn->syms;
    for (i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        s->value = oldval[i].data.number;
        sl = sl->next;
    }
    free(oldval);

    return v;
}
struct list *linked_list_ast(struct ast *args);
void print_list(struct list *lst);
/* evaluate an AST */
val_t eval(struct ast *a)
{
    val_t v;
    v.type = 1; // Default type is number
    v.data.number = 0.0; // Default value is 0.0
    v.data.string = strdup(""); // Default string value is empty

    if(!a) {
    yyerror("internal error, null eval");
    exit(1);
    }

    switch(a->nodetype) {
        /* constant */
        case 'K': 
            v.type = 1; // Number
            v.data.number = a->data.number; 
            break;
        /* string */
        case 'S': 
            v.type = 2; // String
            v.data.string = strdup(a->data.s);
            break;
        /* name reference */
        case 'N': 
            struct symbol *sym = a->data.sym;
            if (sym->type == 2) { //string
                v.type = 2;
                v.data.string = strdup(sym->string);
            } else {
                v.type = 1; // Number
                v.data.number = sym->value;
            }
            break;
        /* declaration */
        case 'D':
            //Variable declaration is handled during parsing; nothing to be done here
            v.type = 1;
            v.data.number = 0.0;
            break;
        /* assignment */
        case '=': 
            {
            struct symbol *sym = a->data.sym; // Symbol being assigned

            if (a->l == NULL) {
                // Variable declaration without initialization
                if (sym->type == 1 || sym->type == 6 || sym->type == 7) { 
                    sym->value = 0.0; // Default value for numeric type
                    v.type = 1;
                } else if (sym->type == 2) {
                    sym->value = 0.0; // Default "dummy" value for strings (or handle differently)
                    sym->string = strdup("");   // Or set to a valid default string value
                    v.type = sym->type;
                } else if (sym->type == 3) { // Default list initialization
                    sym->list = NULL; // Empty list
                    v.type = 3;
                    v.data.list = NULL;
                }else {
                    yyerror("Unkown type of variable '%s'", sym->name);
                    return v = (val_t){.type = 1, .data.number = 0.0};
                }
                // Add handling for other types if needed
                break;
            }
            
            val_t val = eval(a->l);         // Evaluate the expression on the left-hand side
            // Handle assignment from another variable
            if (sym->type != val.type && sym->type != 3) {
                yyerror("Type mismatch: cannot assign type %d to variable '%s' of type %d",
                        val.type, sym->name, sym->type);
                if (sym->type == 1 || sym->type == 6 || sym->type == 7) {  /* Numeric type*/
                    return v = (val_t){.type = 1, .data.number = sym->value};
                } else if (sym->type == 2) { /* String type*/
                    return v = (val_t){.type = 2, .data.string = strdup(sym->string)};
                }
                return v = (val_t){.type = 1, .data.number = 0.0}; 
            }
            // Handle numeric assignment (constant, variable, or expression)
            if (sym->type == 1 || sym->type == 6 || sym->type == 7) {
                v.type = 1;
                sym->value = val.data.number;
                v.data.number = sym->value;
            }
            else if (sym->type == 2) {
                free(sym->string); // Free the old string value
                sym->string = strdup(val.data.string); // Assign the new string value
                v.type = sym->type;
                v.data.string = strdup(sym->string);
            }
            else if (sym->type == 3) {
        if (a->l->nodetype == 'L') { // Se il nodo è di tipo lista
            struct list *lst = linked_list_ast(a->l); // Crea la lista
            sym->list = lst; // Assegna la lista alla variabile
            v.type = 3;
            v.data.list = lst;
            }
            } 
            // TODO: add additional types if needed
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

            if (left.type == 2 && right.type == 2) { // Strings (concatenation)
                size_t len = strlen(left.data.string) + strlen(right.data.string) + 1;
                v.type = 2;
                v.data.string = malloc(len);
                snprintf(v.data.string, len, "%s%s", left.data.string, right.data.string);
            }
            else { // Numbers
                v.type = 1;
                v.data.number = left.data.number + right.data.number;
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
            if (left.type == 2|| right.type == 2) {
                yyerror("Invalid operands to arithmetic operator: both must be numbers");
                exit(1);
            }

            v.type = 1;
            switch (a->nodetype) {
                case '-': v.data.number = left.data.number - right.data.number; break;
                case '*': v.data.number = left.data.number * right.data.number; break;
                case '/': v.data.number = left.data.number / right.data.number; break;
                case '^': v.data.number = pow(left.data.number, right.data.number); break;
            }
            break;
        }
        case '|': {
            val_t left = eval(a->l);
            if (left.type == 2) {
                yyerror("Invalid operand to arithmetic operator: must be a number");
                exit(1);
            }
            v.type = 1;
            v.data.number = fabs(eval(a->l).data.number); break;
        }

        case 'M': {
            val_t left = eval(a->l);
            if (left.type == 2) {
                yyerror("Invalid operand to arithmetic operator: must be a number");
                exit(1);
            }
            v.type = 1;
            v.data.number = -eval(a->l).data.number; break;
        }
        case '!': {
            if(!a->l) {
                yyerror("Invalid operand to 'not' operator");
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

            v.type = 1;
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
                v = a->data.flow.tl ? eval(a->data.flow.tl) : (val_t){.type = 1, .data.number = 0.0};
            } else {
                v = a->data.flow.el ? eval(a->data.flow.el) : (val_t){.type = 1, .data.number = 0.0};
            } 
            break;
        /* while/do */
        case 'W':
        v.data.number = 0; /* a default value */
        if (a->data.flow.tl && a->data.flow.el) {
            do {
                v = eval(a->data.flow.tl);
            } while (eval(a->data.flow.cond).data.number != 0);
        }
        if(a->data.flow.tl ) {
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
            v.type = 3; // Tipo lista
            v.data.list = linked_list_ast(a->l); // Costruisci la lista
            if (a->l) eval(a->l);
            if (a->r) eval(a->r);
        break;
        case 'F': v = callbuiltin(a); break;
        case 'C': v = calluser(a); break;
        default: printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}


/* define a function */
void dodef(struct symbol *name, struct symlist *syms, struct ast *func)
{
 if(name->syms) symlistfree(name->syms);
 if(name->func) treefree(name->func);
 name->syms = syms;
 name->func = func;
}

/* Error reporting function */
void yyerror(const char *s, ...) {
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: Error: ", 1);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}

void print_val(val_t val) {
    switch (val.type) {
        case 1: // Numeric type
            printf("Number: %.6f\n", val.data.number);
            break;
        case 2: // String type
            printf("String: %s\n", val.data.string);
            break;
        case 3: // List type
            printf("List: ");
            print_list(val.data.list);
            printf("\n");
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
    

    // Add details based on the node type
    switch (node->nodetype) {
        /* Constant value*/
        case 'K': printf(", Value: %f\n", node->data.number);break;
        /* Variable reference*/
        case 'N': 
            if (node->data.sym->type == 2) { // String variable
                printf(", Variable: %s, Value (string): %s\n", node->data.sym->name, node->data.sym->string);
            } else if (node->data.sym->type == 3) { // List variable
                printf(", Variable: %s, Value (list): ", node->data.sym->name);
                print_list(node->data.sym->list);
                printf("\n");  
            }
            else { // Numeric variable
                printf(", Variable: %s, Value (number): %f\n", node->data.sym->name, node->data.sym->value);
            }
        break;
        /*Assignment*/
        case '=': printf(", Assignment to: %s\n", node->data.sym->name); break;
        /* Built-in function*/
        case 'F': printf(", Built-in Function: %d\n", node->data.functype); break;
        /* User-defined function*/
        case 'C': printf(", User Function: %s\n", node->data.sym->name);break;
        /* String literal */
        case 'S': printf(", String: %s\n", node->data.s);break;
        /* Arithmetic operations*/

        /* If/else */
        case 'I': printf(" (If/Else)\n");break;
        /*While loop*/
        case 'W': printf(" (While Loop)\n"); break;
        /*For loop*/
        case 'T':   printf(" (For Loop)\n");break;
        default: printf("\n"); break;
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

/* Create a linked list from an AST structure */
struct list *linked_list_ast(struct ast *args) {
    struct list *head = NULL;  // Head of the linked list
    struct list *current = NULL;

    while (args) {
        // Crea un nuovo nodo della lista
        struct list *new_node = (struct list *)malloc(sizeof(struct list));
        if (!new_node) {
            yyerror("Out of memory");
            exit(1);
        }
        // Valuta il valore dell'AST corrente
        val_t *value = (val_t *)malloc(sizeof(val_t));
        if (!value) {
            yyerror("Out of memory");
            exit(1);
        }
        val_t result = eval(args);
        if (result.type == 1) { 
            value->type = 1;
            value->data.number = result.data.number;
        } else if (result.type == 2) { 
            value->type = 2;
            value->data.string = strdup(result.data.string);
        } else if (result.type == 3) { 
            value->type = 3;
            value->data.list = result.data.list;
        }

        // Assegna il valore e inizializza il nodo
        new_node->value = value;
        new_node->next = NULL;

        // Aggiungi il nodo alla lista
        if (!head) {
            head = new_node;  // Primo nodo
        } else {
            current->next = new_node;  // Collegamento al successivo
        }
        current = new_node;

        // Passa al prossimo nodo AST (iterazione sulla lista AST)
        if (args->nodetype == 'L') {  // Nodo lista (sinistra = valore, destra = prossimo elemento)
            args = args->r;           // Vai al prossimo elemento
        } else {  // Fine della lista
            args = NULL;
        }
    }
       
    return head;
}

void print_list(struct list *lst) {
    printf("(");
    struct list *current = lst;
    while (current) {
        if (current->value->type == 3) {
            print_list(current->value->data.list); 
        } else if (current->value->type == 1) {
            printf("%.2f", current->value->data.number);
        } else if (current->value->type == 2) {
            printf("\"%s\"", current->value->data.string);
        }
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf(")");
}
