%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int yylineno;
void yyerror (const char *s) ;
int yylex();
int vars[256];



// Declare functions
void print_token(int token);
void add_variable(char *name, int value);
int get_variable_value(char *name);
%}

%define parse.error verbose

%union {
    double num;
    char *st;
}

%token PLUS MINUS MUL DIV EQ GT GE LT LE POW NOTEQUAL
%token <num> NUM BINARY ROMAN
%token <st> STR ID FUNC KEYWORD DATA_TYPE SPECIAL_CHAR 

%type <num> TERM 

%right '='
%left  PLUS MINUS
%left  MUL DIV
%right POW
%start START
%%

START: START TERM ';' { printf("R: %f\n", $2); }
     | %empty

TERM: TERM MINUS TERM { $$ = $1 - $3; }
    | TERM PLUS TERM { $$ = $1 + $3; }
    | TERM MUL TERM { $$ = $1 * $3; }
    | TERM DIV TERM { $$ = $1 / $3; }
    | TERM POW TERM { $$ = pow($1, $3); }
    | ID '=' TERM   { $$ = $3; vars[(int)$1[0]] = $3; }
    | NUM /* default action: $$ = $1 */
    | ID { $$ = vars[(int)$1[0]]; }
    


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

void yyerror (const char *s) {
  printf("Error in line %d: %s\n", yylineno, s);
}