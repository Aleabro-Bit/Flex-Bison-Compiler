# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "abstract_syntax_tree.h"

/* Initial size*/
#define NHASH 100
struct symbol *symtab = NULL;
size_t symtab_size = 0; // Current size
size_t symtab_count = 0; // Number of symbols currently used

/* symbol table */
/* hash a symbol */
static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while(c = *sym++) { hash = hash*9 ^ c; }
    return hash;
}

/* Expand the symbol table */
void expand_symtab() {
    size_t new_size = (symtab_size == 0) ? NHASH : symtab_size * 2;
    struct symbol *new_symtab = calloc(new_size, sizeof(struct symbol));
    if (!new_symtab) {
        perror("ERROR: Unable to expand symbol table");
        exit(EXIT_FAILURE);
    }

    // Reallocate the symbols
    for (size_t i = 0; i < symtab_size; i++) {
        if (symtab[i].name != NULL) {
            unsigned int new_index = symhash(symtab[i].name) % new_size;
            unsigned int probe = 1;
            while (new_symtab[new_index].name != NULL) {
                new_index = (new_index + probe * (probe)) % new_size; // Quadratic probing
                probe++;
            }
            new_symtab[new_index] = symtab[i];
        }
    }

    // Free the old symbol table and update the global variables
    free(symtab);
    symtab = new_symtab;
    symtab_size = new_size;
}

/* lookup symbol */
struct symbol *lookup(char* sym)
{
    if (symtab_size == 0) {
        expand_symtab(); // Initialize the symbol table
    }
    else if (symtab_count >= symtab_size * 0.7) {
        expand_symtab(); // Expand the symbol table if it's more than 70% full
    }
    unsigned int index = symhash(sym) % symtab_size;
    struct symbol *sp = &symtab[index];
    int scount = symtab_size; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) { 
            return sp;  /* symbol found*/
        }
        if(!sp->name) { /* new entry */
            sp->name = strdup(sym);
            sp->value = 0;
            sp->type = 0;
            sp->string = NULL;
            sp->func = NULL;
            sp->syms = NULL;
            sp->list = NULL;

            symtab_count++;
            return sp; /* new entry */
        }
        if(++sp >= symtab+symtab_size) sp = symtab; /* try the next entry */
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

// Print the symble table
void print_symtab() {
    printf("Symbol Table Contents:\n");
    for (size_t i = 0; i < symtab_size; i++) {
        if (symtab[i].name != NULL) {
            printf("Name: %s, Value: %.2f, Type: %d\n", symtab[i].name, symtab[i].value, symtab[i].type);
        }
    }
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