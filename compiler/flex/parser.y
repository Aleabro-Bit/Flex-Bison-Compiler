%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
void yyerror (const char *s) 
int yylex();



// Declare functions
void print_token(int token);
void add_variable(char *name, int value);
int get_variable_value(char *name);
%}

%define parse.error verbose

%union {
    double num;
    char *st;
    char op;
    int fn; // Which function to call
}

%token <num> NUM BINARY ROMAN
%token <str> STR IDENTIFIER FUNC
%token <op> OPERATOR
%token <fn> FUNCTION
%token WHETHER THEN OTHERWISE WHEN LET FROM TO STEP

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <num> TERM
//%type <str> statement

%start START
%%
START: TERM ';' { printf("Result: %f\n", $1); }

TERM: TERM '+' NUM { printf("Result: %f\n", $1 + $3); } 
    | NUM
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

void yyerror (const char *s) {
  printf("Error in line %d: %s\n", yylineno, s);
}