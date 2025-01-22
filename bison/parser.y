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

%union {
    double num;
    char *st;
    char op;
    struct ast *a;
}

%token BOOLEAN DOUBLE INT LIST STEP TO FROM WHEN OTHERWISE WHETHER RETURN DEFINE UNTIL SHIFT EVENT
%token <op> PLUS MINUS MUL DIV EQ GT GE LT LE POW NOTEQUAL NEWLINE ASSIGN ABS
%token <num> NUMBER NUM BINARY ROMAN
%token <st> STR ID FUNC KEYWORD DATA_TYPE SPECIAL_CHAR 
%type <a> expression statement statements whether when from shift condition 
%right ASSIGN
%left PLUS MINUS
%left MUL DIV
%nonassoc ABS
%start START
%%

START: START instruction
    | instruction
    | %empty
    ;
instruction: statement 
    ;
statements: statement
    | statements statement
    ;
statement: whether
    | when
    | from
    | shift
    | expression ASSIGN expression
    | expression
    ;
whether: WHETHER  '(' condition ')' '%' statements '%' OTHERWISE '%' statements '%' 
    ;

when: WHEN '(' condition ')' '%' statements '%' UNTIL '(' condition ')' 
    ;

from: FROM expression TO expression ';' STEP expression '%' statements '%'
    ;
shift: SHIFT '(' expression ')' '%' EVENT '(' condition ')' ASSIGN expression '%'
    ;
condition: expression EQ expression
    | expression NOTEQUAL expression
    | expression GT expression
    | expression GE expression
    | expression LT expression
    | expression LE expression
    ;
expression: NUM { $$ = newnum($1);}
    | expression PLUS expression { $$ = newast('+', $1, $3); }
    | expression MINUS expression { $$ = newast('-', $1, $3); }
    | expression MUL expression { $$ = newast('*', $1, $3); }
    | expression DIV expression { $$ = newast('/', $1, $3); }
    | ABS expression ABS { $$ = newast('|', $2, NULL); }
    | MINUS expression { $$ = newast('M', $2, NULL); }
    | '(' expression ')' { $$ = $2; }
    | ID 
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

