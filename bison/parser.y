%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <abstract_syntax_tree.h>

int yydebug = 1;
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
    char op;
    struct ast *a;
    struct symbol *s; // which symbol
    struct symlist *sl; // symbol list
    int fn;          // which function
}

%token BOOLEAN DOUBLE INT LIST STEP TO FROM WHEN OTHERWISE WHETHER RETURN DEFINE UNTIL SHIFT EVENT EOL THEN 
%token <op> PLUS MINUS MUL DIV POW ASSIGN ABS
%token <num> NUMBER NUM BINARY ROMAN
%token <st> STR ID KEYWORD DATA_TYPE SPECIAL_CHAR
%token <fn> FUNC 

%type <a> expression statement statements whether when from shift condition list explist
%type <sl> symlist

%nonassoc <fn> CMP
%right ASSIGN
%left PLUS MINUS
%left MUL DIV
%nonassoc ABS UMINUS

%start START
%%

START: /* nothing */
    | START statement EOL { printf("= %4.4g\n",eval($2)); treefree($2); }
    | START DEFINE ID '(' symlist ')' ASSIGN list EOL { 
        dodef($3, $5, $8);
        printf("Defined %s\n> ", $3->name); }
    | START error EOL { yyerrok; printf("> "); }
    ;
statements: statement
    | statements statement
    ;
statement: 
    | whether
    | when
    | from
    | shift
    | expression
    ;
list: /* do nothing */ { $$ = NULL; }
    | statement ';' list { if ($3 == NULL) 
        $$ = $1;
    else 
        $$ = newast('L', $1, $3); } // expression or statement list
    | statement
    ;
whether: WHETHER condition THEN list { $$ = newflow('I', $2, $4, NULL); } //TODO: change syntax
    | WHETHER condition THEN list OTHERWISE list { $$ = newflow('I', $2, $4, $6); } 
    ;

when: WHEN condition UNTIL list { $$ = newflow('W', $2, $4, NULL); } //TODO: change syntax
    ;

from: FROM expression TO expression ';' STEP expression '%' statements '%'
    ;
shift: SHIFT '(' expression ')' '%' EVENT '(' condition ')' ASSIGN expression '%'
    ;
condition: expression CMP expression { $$ = newcmp($2, $1, $3); }
    | expression
    ;
expression: expression PLUS expression { $$ = newast('+', $1, $3); }
    | expression MINUS expression { $$ = newast('-', $1, $3); }
    | expression MUL expression { $$ = newast('*', $1, $3); }
    | expression DIV expression { $$ = newast('/', $1, $3); }
    | ABS expression ABS { $$ = newast('|', $2, NULL); }
    | MINUS expression %prec UMINUS{ $$ = newast('M', $2, NULL); }
    | '(' expression ')' { $$ = $2; }
    | NUM { $$ = newnum($1);}
    | ID { $$ = newref($1); }
    | ID ASSIGN expression { $$ = newasgn($1, $3); }
    | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    | ID '(' explist ')' { $$ = newcall($1, $3); }
    ;
explist: expression
    | expression ',' explist { $$ = newast('L', $1, $3); }
    ;
symlist: ID          { $$ = newsymlist($1, NULL); }
    | ID ',' symlist { $$ = newsymlist($1, $3); }
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

