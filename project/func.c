# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "helper.h"

/* factorial built in function*/
 double factorial(double n) {
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
struct ast *current = arg; // Nodo attuale

    while (current) {  
        val_t value = eval(current); // Valuta il nodo sinistro

        if (value.type == 1) {
            printf("%g", value.data.number);
        } else if (value.type == 2) {
            printf("%s", value.data.string);
        } else if (value.type == 3) {
            print_list(value.data.list);
        } else {
            yyerror("Unsupported type in print");
        }

        // Se ci sono altri argomenti, aggiunge uno spazio tra di loro
        if (current->r) {
            printf(" ");
        }

        current = current->r; // Passa al prossimo argomento
    }

    printf("\n"); // Nuova riga alla fine
}

/* Returns the size of a list */
int list_length(struct list *head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

/* Access a particular element of the list */
val_t *get(struct list *head, int index) {
    int i = 0;
    while (head) {
        if (i == index) {
            return head->value;  // Returns the current value
        }
        head = head->next;
        i++;
    }
    return NULL;  // Return null if value is out of bounds
}

val_t *get2D(struct list *head, int row, int col) {
    int i = 0;
    while (head) { // Iteriamo sulle righe (lista esterna)
        if (i == row) { // Se siamo nella riga giusta
            struct list *inner_list = head->value->data.list; // Lista interna (colonne)
            return get(inner_list, col); // Usiamo get() per ottenere la colonna
        }
        head = head->next;
        i++;
    }
    return NULL; // Se gli indici sono fuori dai limiti
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

val_t split(struct ast *a) {
    val_t v = eval(a->l); // Valutiamo l'argomento

    if (v.type != 2) { // Controllo: l'argomento deve essere una stringa
        yyerror("split() expects a string");
        return (val_t){.type = 3, .data.list = NULL}; // Ritorna una lista vuota in caso di errore
    }

    char *input = strdup(v.data.string); // Copia della stringa per strtok
    char *token = strtok(input, " "); // Dividiamo la stringa in parole
    struct list *head = NULL;
    struct list *current = NULL;

    while (token != NULL) {
        struct list *new_node = (struct list *)malloc(sizeof(struct list));
        if (!new_node) {
            yyerror("Out of memory");
            exit(1);
        }

        val_t *value = (val_t *)malloc(sizeof(val_t));
        if (!value) {
            yyerror("Out of memory");
            exit(1);
        }

        value->type = 2; // Tipo stringa
        value->data.string = strdup(token); // Copiamo la parola

        new_node->value = value;
        new_node->next = NULL;

        if (!head) {
            head = new_node; // Primo nodo
        } else {
            current->next = new_node;
        }
        current = new_node;

        token = strtok(NULL, " "); // Passiamo al prossimo token
    }

    free(input); // Libera la copia della stringa

    return (val_t){.type = 3, .data.list = head}; // Restituiamo direttamente la lista
}
/* Create a linked list from an AST structure */
struct list *linked_list_ast(struct ast *args) {
    struct list *head = NULL;  // Head of the linked list
    struct list *current = NULL;

    while (args) {
        
        struct list *new_node = (struct list *)malloc(sizeof(struct list));
        if (!new_node) {
            yyerror("Out of memory");
            exit(1);
        }
    
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

        new_node->value = value;
        new_node->next = NULL;

        if (!head) {
            head = new_node;  // First node is the head
        } else {
            current->next = new_node;  
        }
        current = new_node;

        if (args->nodetype == 'L') {  
            args = args->r;           
        } else {  
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

struct list *concat_lists(struct list *l1, struct list *l2) {
    struct list *new_list = NULL, *current = NULL;

    // Copy the first list
    while (l1) {
        struct list *new_node = malloc(sizeof(struct list));
        new_node->value = l1->value;
        new_node->next = NULL;

        if (!new_list) new_list = new_node;
        else current->next = new_node;
        current = new_node;

        l1 = l1->next;
    }

    // Copy the second list
    while (l2) {
        struct list *new_node = malloc(sizeof(struct list));
        new_node->value = l2->value;
        new_node->next = NULL;

        if (!new_list) new_list = new_node;
        else current->next = new_node;
        current = new_node;

        l2 = l2->next;
    }

    return new_list;
}

val_t count_char(val_t v) {
    val_t result;
    result.type = 1; 

    if (v.type == 2 && v.data.string) { 
        result.data.number = strlen(v.data.string); 
    } else {
        yyerror("char_count() expects a string");
        result.data.number = 0; 
    }
    
    return result;
}
