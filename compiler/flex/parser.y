%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *yytext;  // Provided by the lexer

enum {
    NUM = 1,
    STR,
    IDENTIFIER,
    COMMENT,
    KEYWORD,
    OPERATOR,
    ROMAN,
    BINARY,
    DATA_TYPE,
    FUNC,
    INSTRUCTION
};

// Structures for storing token values
struct {
    int num;
    char *st;
} yylval;

// Declare functions
void print_token(int token);
void add_variable(char *name, int value);
int get_variable_value(char *name);
%}

%union {
    int num;
    char *str;
}

%token <num> NUM BINARY ROMAN
%token <str> STR IDENTIFIER KEYWORD OPERATOR FUNC INSTRUCTION
%token COMMENT

%type <num> expression
%type <str> statement

%%

program:
    program statement
    | /* empty */
    ;

statement:
    assignment
    | function_declaration
    | if_statement
    | while_statement
    ;

assignment:
    IDENTIFIER '=' expression {
        add_variable($1, $3);
        printf("Assignment: %s = %d\n", $1, $3);
    }
    ;

function_declaration:
    FUNC IDENTIFIER '(' ')' '{' program '}' {
        printf("Function declaration: %s\n", $2);
    }
    ;

if_statement:
    "if" '(' expression ')' statement {
        printf("If statement: condition = %d\n", $3);
    }
    ;

while_statement:
    "while" '(' expression ')' statement {
        printf("While loop: condition = %d\n", $3);
    }
    ;

expression:
    NUM {
        $$ = $1;
    }
    | BINARY {
        $$ = $1;
    }
    | ROMAN {
        $$ = $1;
    }
    | IDENTIFIER {
        $$ = get_variable_value($1);
    }
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
