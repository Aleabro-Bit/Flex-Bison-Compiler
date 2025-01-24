%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "abstract_syntax_tree.h"

int yydebug = 0;
extern FILE *yyin;
extern int yylineno;

int yylex();

// Declare functions
void print_token(int token);
void add_variable(char *name, int value);
int get_variable_value(char *name);
%}

%define parse.error verbose
//union declares types to be used in the values of symbols in the parser
%union {
    double num;
    char *st;
    char *op;
    struct ast *a;
    struct symbol *s; // which symbol
    struct symlist *sl; // symbol list
    int fn;          // which function
}

%token STEP TO FROM WHEN OTHERWISE WHETHER RETURN DEFINE UNTIL SHIFT EVENT EOL THEN BOOLEAN
%token <op> PLUS MINUS MUL DIV POW ASSIGN ABS
%token <num> NUM BINARY ROMAN
%token <st> STR   
%token <fn> FUNC DATA_TYPE
%token <s> ID

%type <a> expression statement statements whether when  shift condition explist  assignment return flow ufunction funcall START declare init value
%type <sl> symlist

%nonassoc <fn> CMP
%right ASSIGN
%left PLUS MINUS POW
%left MUL DIV
%nonassoc ABS UMINUS

%start START
%%

START: /* nothing */
    | statements {$$ = newast('L', $1, NULL); printf("= %4.4g\n", eval($1)); treefree($1); }
    | START statements EOL {$$ = newast('L', $1, $2); print_ast($2, 0, " ");  printf("= %4.4g\n>", eval($2)); treefree($2); }
    | START EOL { printf("> "); }
    ;
statements: ufunction { $$ = $1; }
    | statements statement ';' { if ($2 == NULL) 
        $$ = $1;
    else 
        $$ = newast('L', $1, $2); 
        } // expression or statement list
    | statement  { $$ = $1; }
    ;
statement:
    | declare { $$ = $1; }
    | assignment { $$ = $1; } 
    | funcall { $$ = $1; }
    | return { $$ = $1; }
    | flow  { $$ = $1; }
    | ufunction { $$ = $1; }
    | expression { $$ = $1; }
    ;
flow: 
    | whether
    | when
//    | from
    | shift
    ;
declare: DATA_TYPE ID init {
    struct symbol *sym = lookup($2->name);
    if (sym->type != 0) {
        yyerror("Variable '%s' already declared", $2->name);
    } else {
        sym->type = $1; // Assegna il tipo dalla regola DATA_TYPE
    }
    $$ = newdeclare(sym, NULL, $3);
} //TODO: add declare
    ;
init: ASSIGN value {
    struct symbol *sym = lookup($2->s); // Cerca la variabile
    if (sym->type != 0 && sym->type != $2->nodetype) {
        yyerror("Type mismatch: cannot assign value to variable '%s'", $2->s);
    } else {
        $$ = newasgn(sym, $2);
    }
}
 | { $$ = NULL; }
  ;
assignment: ID ASSIGN expression { $$ = newasgn($1, $3); }
    ;
whether: WHETHER '(' condition ')' THEN ':' statements { $$ = newflow('I', $3, $7, NULL); } //TODO: change syntax
    | WHETHER '(' condition ')' THEN ':' statements OTHERWISE ':' statements { $$ = newflow('I', $3, $7, $10); } 
    ;

when: WHEN condition UNTIL statements { $$ = newflow('W', $2, $4, NULL); } //TODO: change syntax
    ;

//from: FROM expression TO expression ';' STEP expression '%' statements '%' { $$ = newflow('F', $2, $4, $6, $8); } //TODO: add for flow
    ;
shift: SHIFT '(' expression ')' '%' EVENT '(' condition ')' ASSIGN expression '%'
    ;
condition: expression CMP expression { $$ = newcmp($2, $1, $3); }
    | expression {}    
    ;
expression: expression PLUS expression { $$ = newast('+', $1, $3); }
    | expression MINUS expression { $$ = newast('-', $1, $3); }
    | expression MUL expression { $$ = newast('*', $1, $3); }
    | expression DIV expression { $$ = newast('/', $1, $3); }
    | expression POW expression { $$ = newast('^', $1, $3); }
    | ABS expression ABS { $$ = newast('|', $2, NULL); }
    | MINUS expression %prec UMINUS{ $$ = newast('M', $2, NULL); }
    | '(' expression ')' { $$ = $2; }
    | value { $$ = $1; }
    ;
value: 
    | NUM { $$ = newnum($1);}
    | BINARY { $$ = newnum($1); }
    | ROMAN { $$ = newnum($1); }
    | ID { $$ = newref($1); }
    | STR { $$ = newstr($1); }
    ;
explist: expression
    | expression ',' explist { $$ = newast('L', $1, $3); }
    ;
symlist: ID          { $$ = newsymlist($1, NULL); }
    | ID ',' symlist { $$ = newsymlist($1, $3); }
    ;
return: RETURN expression ';' { $$ = newast('R', $2, NULL); } //TODO: add return
    ;
ufunction: DEFINE DATA_TYPE ID '(' symlist ')' '{' statements '}' { dodef($3,$5,$8); }
    ;
funcall: ID '(' explist ')' { $$ = newcall($1, $3); }
    | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    ;

%%

int main(void) {
    yyparse();
    return 0;
}

// Simple symbol table
void add_variable(char *name, int value) {
    // This is a simplified symbol table
    printf("Adding variable: %s = %d\n", name, value);
}

int get_variable_value(char *name) {
    // For simplicity, just return a dummy value
    printf("Getting value of variable: %s\n", name);
    return 42;
}

