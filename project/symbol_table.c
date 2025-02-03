# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "helper.h"

/* Initial size*/
#define NHASH 100
#define MAX_SCOPE_DEPTH 128

scope_t scope_stack[MAX_SCOPE_DEPTH];
int scope_top = 0;  // Last active scope

/* symbol table */
/* hash a symbol */
static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while((c = *sym++)) { hash = hash*9 ^ c; }
    return hash;
}

/* Expand the symbol table */
void expand_symtab(int scopeidx) {
    size_t new_size = (scope_stack[scopeidx].symtab_size == 0) ? NHASH : scope_stack[scopeidx].symtab_size * 2;    struct symbol *new_symtab = calloc(new_size, sizeof(struct symbol));
    if (!new_symtab) {
        perror("ERROR: Unable to expand symbol table");
        exit(EXIT_FAILURE);
    }

    // Reallocate the symbols
    for (size_t i = 0; i < scope_stack[scopeidx].symtab_size; i++) {
        if (scope_stack[scopeidx].symtab[i].name != NULL) {
            unsigned int new_index = symhash(scope_stack[scopeidx].symtab[i].name) % new_size;
            unsigned int probe = 1;
            while (new_symtab[new_index].name != NULL) {
                new_index = (new_index + probe * (probe)) % new_size; // Quadratic probing
                probe++;
            }
            new_symtab[new_index] = scope_stack[scopeidx].symtab[i];
        }
    }

    // Free the old symbol table and update the global variables
    free(scope_stack[scopeidx].symtab);
    scope_stack[scopeidx].symtab = new_symtab;
    scope_stack[scopeidx].symtab_size = new_size;
}

/* lookup symbol */
struct symbol *_lookup(char* sym, int scopeidx, int newentry)
{
    if (scope_stack[scopeidx].symtab_size == 0){
        expand_symtab(scopeidx); //initialize the symbol table
    }
    else if (scope_stack[scopeidx].symtab_count >= 0.7 * scope_stack[scopeidx].symtab_size) {
        expand_symtab(scopeidx); // Expand the symbol table if it's more than 70% full
    }
    unsigned int index = symhash(sym) % scope_stack[scopeidx].symtab_size;    
    struct symbol *sp = &scope_stack[scopeidx].symtab[index];
    int scount = scope_stack[scopeidx].symtab_size; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) { 
            return sp;  /* symbol found*/
        }
        if(!sp->name) { /* new entry */
            if (newentry){
            sp->name = strdup(sym);
            sp->value = 0;
            sp->type = 0;
            sp->string = NULL;
            sp->func = NULL;
            sp->syms = NULL;
            sp->list = NULL;

            scope_stack[scopeidx].symtab_count++;
            return sp; /* new entry */
            } else {
                return NULL; 
            }
        }
        if(++sp >= scope_stack[scopeidx].symtab+scope_stack[scopeidx].symtab_size) sp = scope_stack[scopeidx].symtab; /* try the next entry */   
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct symbol *lookup (char *sym) {
	struct symbol *s = NULL;
	for (int i = scope_top; i >= 0; i--) {
		s = _lookup(sym, i, 0);
		if (s)
			break;
	}
	if (!s)
		s = _lookup(sym, scope_top, 1);

	return s;
}

struct symbol *declare (char *sym) {
	struct symbol *s = _lookup(sym, scope_top, 1);

	return s;
}

// Print the symble table
void print_symtab() {
printf("Symbol Table Contents:\n");
	for (int x = scope_top; x >= 0; x--) {
		printf("\nLevel %d:\n", x);
		for (size_t i = 0; i < scope_stack[x].symtab_size; i++) {
			if (scope_stack[x].symtab[i].name != NULL) {
				printf("Name: %s, Value: %.2f, Type: %d\n", scope_stack[x].symtab[i].name, scope_stack[x].symtab[i].value, scope_stack[x].symtab[i].type);
        }
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

/* Scope */

void push_scope() {
    if (scope_top >= MAX_SCOPE_DEPTH - 1) {
        yyerror("Scope stack overflow");
        exit(1);
    }
    scope_top++;
    scope_stack[scope_top].symtab = NULL;
    scope_stack[scope_top].symtab_size = 0;
    scope_stack[scope_top].symtab_count = 0;

    //printf("Scope created, level: %d\n", scope_top);
}

void pop_scope() {
    if (scope_top < 0) {
        yyerror("Error: pop on empty scope stack");
        return;
    }
    free(scope_stack[scope_top--].symtab);
}

void print_all_scopes() {
    printf("\n=== Print all scopes ===\n");
    for (int i = scope_top; i >= 0; i--) {
        printf("Scope level %d:\n", i);
    for (int j = 0; j < scope_stack[i].symtab_count; j++) {
            struct symbol *sym = &scope_stack[i].symtab[j];
            printf("  - Nome: %s, Valore: %.2f, Tipo: %d\n", 
                   sym->name, sym->value, sym->type);
        }
        if (scope_stack[i].symtab_count == 0) {
            printf("  (empty)\n");
        }
        printf("-----------------------------\n");
    }
    printf("=== Finish scope print ===\n\n");
}
