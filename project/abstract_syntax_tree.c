# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "helper.h"

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
        case B_size:
            if (v.type == 3) { // If it's a list
                result.data.number = list_length(v.data.list);
            } else {
                yyerror("length() expects a list");
            }
            return result;
        case B_get:
            if (v.type == 3 && a->l->r) { 
                val_t index_val = eval(a->l->r); // Evaluate the index
                if (index_val.type == 1 || index_val.type == 6 || index_val.type == 7) { // Assume that the index is a number
                    double index = index_val.data.number;
                    val_t list_node = eval(a->l->l);
                    val_t *element = get(list_node.data.list, index);
                    if (element) {
                        result = *element; // Element found
                        
                    } else {
                        yyerror("Index out of bounds");
                    }
                } else {
                    yyerror("get() expects a numeric index");
                }
            } else {
                yyerror("get() expects a list and an index");
            }
            return result;
        /*case B_get2D:
        if (v.type == 3 && a->l->r && a->l->r->r) { 
            val_t index_row = eval(a->l->r);
            val_t index_col = eval(a->l->r->r);

            if (index_row.type == 1 && index_col.type == 1) { 
                val_t list_node = eval(a->l->l);
                val_t *element = get2D(list_node.data.list, (int)index_row.data.number, (int)index_col.data.number);
                if (element) {
                    return *element; 
                } else {
                    yyerror("Index out of bounds");
                }
            } else {
                yyerror("get2D() expects two numeric indices");
            }
        } else {
            yyerror("get2D() expects a 2D list and two indices");
        }
        return (val_t){.type = 1, .data.number = 0.0}; // Default return
        */
        case B_input: {
            char buffer[1024]; // Buffer for input of up to 1024 characters

        // Print the prompt
        if (v.type == 2 && v.data.string) {
            printf("%s: ", v.data.string);
        } else {
            printf("Input: ");
        }

        // Read the input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            yyerror("Error reading input");
            return (val_t){.type = 2, .data.string = strdup("")}; 
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Conversion in number
        char *endptr;
        double num = strtod(buffer, &endptr);

        if (*endptr == '\0') { // If the buffer in converted into a number
            result.type = 1;
            result.data.number = num;
        } else { // else assume it's a string
            result.type = 2;
            result.data.string = strdup(buffer);
        }

        return result;
        }
        case B_split: {
            if (v.type == 2) {
                result.type = 3;
                result = split(v);
            } else {
                yyerror("split() expects a string");
            }
            return result;
        }
        case B_count_char:
        if (v.type == 2) { 
            result = count_char(v);
            return result;
        } else {
            yyerror("count() expects a string");
            return (val_t){.type = 1, .data.number = 0}; 
        }

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
            } 
            else if(sym->type == 3) { //list
                v.type = 3;
                v.data.list = sym->list;
            }
            else {
                v.type = 1; // Number
                v.data.number = sym->value;
            }
            break;
        /* declaration */
        case 'D':
            //Variable declaration is handled during parsing; nothing to be done here
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
                    v.type = sym->type;
                    v.data.list = NULL;
                } else {
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
                } else if (sym->type == 3) { /* List type*/
                    return v = (val_t){.type = 3, .data.list = sym->list};
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
                if (val.type == 3 && val.data.list) { //list already declared
                    sym->list = val.data.list; 
                }
                else {
                struct list *lst = linked_list_ast(a->l); // Create a list from the AST
                sym->list = lst; 
                v.type = sym->type;
                v.data.list = lst;
                }
                } 
            break;
        }
        
        /* expressions */
        case '+': {
            val_t left = eval(a->l);
            val_t right = eval(a->r);
            
            if (left.type == 2 && right.type == 2) { // Strings (concatenation)
                size_t len = strlen(left.data.string) + strlen(right.data.string) + 1;
                v.type = 2;
                v.data.string = malloc(len);
                snprintf(v.data.string, len, "%s%s", left.data.string, right.data.string);
            }
            else if (left.type == 3 && right.type == 3) { // Lists (concatenation)
                v.type = 3;
                v.data.list = concat_lists(left.data.list, right.data.list);
            }
            else if (left.type == 3 && right.type != 3) { // Add element to list
            v.type = 3;
            struct list *new_value = linked_list_ast(a->r);
            v.data.list = concat_lists(left.data.list, new_value);  // Aggiunge il nuovo elemento
            }
            else if (left.type != right.type) {
                yyerror("Type mismatch in '+' operation");
                return v;
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
            push_scope(); // Push a new scope
            val_t cond_val = eval(a->data.flow.cond);
            if (cond_val.data.number != 0) { 
                v = a->data.flow.tl ? eval(a->data.flow.tl) : (val_t){.type = 1, .data.number = 0.0};
            } else {
                v = a->data.flow.el ? eval(a->data.flow.el) : (val_t){.type = 1, .data.number = 0.0};
            } 
            pop_scope(); // Pop the scope
            break;
        /* while/do */
        case 'W':
        push_scope(); // Push a new scope
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
        pop_scope(); // Pop the scope
        break; /* value of last statement is value of while/do */

        /* for loop */
        case 'T':
        push_scope(); // Push a new scope 
        eval(a->l); // Initialize
            while (eval(a->data.flow.cond).data.number != 0) { // Control the condition
                eval(a->r->l); // Execute the body
                eval(a->r->r); // Execute the step
            }
        pop_scope(); // Pop the scope
        break;
        
        /* list of statements */
        case 'L': 
        val_t left_val = eval(a->l);  

            // If the first element is a list, create a new list
            if (left_val.type == 3) {
                v.type = 3;
                v.data.list = linked_list_ast(a->l);
            } else {
                v = left_val; 
            }

            if (a->r) {
                val_t right_val = eval(a->r);
                // If both elements are lists, concatenate them
                if (left_val.type == 3 && right_val.type == 3) {
                    v.data.list = concat_lists(left_val.data.list, right_val.data.list);
                }
            }
        break;
        case 'F': v = callbuiltin(a); break;
        case 'C': push_scope(); v = calluser(a); pop_scope(); break;
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
