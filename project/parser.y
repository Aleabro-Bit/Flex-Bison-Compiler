%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"
/*TODO: IMPLEMENT SOME BUILT IN FUNCTIONS, RETURN, SCOPE SISTEMARE IL PARSER */
int yydebug = 0;
extern FILE *yyin;
extern int yylineno;

void print_val(val_t val);

int yylex();
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
    int dt;          // which data type
}

%token STEP TO FROM WHEN OTHERWISE WHETHER RETURN DEFINE UNTIL EOL THEN AND OR NOT
%token <op> PLUS MINUS MUL DIV POW ASSIGN ABS
%token <num> NUM BINARY ROMAN
%token <st> STR   
%token <fn> FUNC 
%token <dt> DATA_TYPE
%token <s> ID

%type <a> expr stmt stmts whether when condition explist  assignment return flow ufunction funcall START declare init value from list
%type <sl> symlist

%nonassoc <fn> CMP
%right ASSIGN
%left PLUS MINUS POW
%left MUL DIV
%nonassoc ABS UMINUS

%start START
%%

START: /* nothing */
    | START stmts EOL {$$ = newast('L', $1, $2); val_t result = eval($2); print_ast($2, 0, " ");  print_all_scopes();  }
    | START ufunction EOL
    | START error EOL { yyerrok; printf("> "); }
    | START EOL  { printf("> "); }
    ;
stmts: 
     stmt ';' stmts { if ($3 == NULL) 
        $$ = $1;
    else 
        $$ = newast('L', $1, $3); 
        } // expression or statement list
    | stmt ';' { $$ = $1; }
    ;
stmt:
     declare { $$ = $1; }
    | assignment { $$ = $1; } 
    | funcall { $$ = $1; }
    | return { $$ = $1; }
    | flow  { $$ = $1; }
    | expr { $$ = $1; }
    ;
flow: 
     whether
    | when
    | from
    ;
declare: DATA_TYPE ID init {
     struct symbol *sym = lookup($2->name);
     if (sym->type != 0) {
         yyerror("Variable '%s' already declared", $2->name);
     } else {
         sym->type = $1; // Assegna il tipo dalla regola DATA_TYPE
     }
     struct ast *declare = newdeclare(sym, NULL, NULL);
     struct ast *assign = newasgn(sym, $3);
     $$ = newast('L', declare, assign);
    }

    ;
init: ASSIGN expr { $$ = $2; }
    | { $$ = NULL; }
    ;
assignment: ID ASSIGN expr { $$ = newasgn($1, $3); }
    ;
whether: WHETHER '[' condition ']' THEN ':' '{' stmts '}' { $$ = newflow('I', $3, $8, NULL); } 
    | WHETHER '[' condition ']' THEN ':' '{' stmts '}' OTHERWISE ':' '{'stmts '}' { $$ = newflow('I', $3, $8, $13); } 
    ;

when: WHEN '[' condition ']'  '{' stmts '}' { $$ = newflow('W', $3, $6, NULL); } 
    | WHEN '{' stmts '}' UNTIL '[' condition ']' { $$ = newflow('W', $7, $3, $7); }
    ;

/* from works only if you declare the variable in the from statement */
from: FROM '[' declare TO expr STEP expr ']' '{' stmts '}'
     {
         struct ast *add = newast('+', newref($3->l->data.sym), $7);
         struct ast *ass = newasgn($3->l->data.sym, add);
         struct ast *cmp = newast('6', newref($3->l->data.sym), $5);
         $$ = newfor($3, cmp, ass, $10);
     } 
     ;
condition: expr CMP expr { $$ = newcmp($2, $1, $3); }
    | condition AND condition { $$ = newast('&', $1, $3); }
    | condition OR condition { $$ = newast('O', $1, $3); }
    | NOT condition { $$ = newast('!', $2, NULL); }
    | '(' condition ')' { $$ = $2; } 
    | expr {}    
    ;
expr: expr PLUS expr { $$ = newast('+', $1, $3); }
    | expr MINUS expr { $$ = newast('-', $1, $3); }
    | expr MUL expr { $$ = newast('*', $1, $3); }
    | expr DIV expr { $$ = newast('/', $1, $3); }
    | expr POW expr { $$ = newast('^', $1, $3); }
    | ABS expr ABS { $$ = newast('|', $2, NULL); }
    | MINUS expr %prec UMINUS{ $$ = newast('M', $2, NULL); }
    | '(' expr ')' { $$ = $2; }
    | value { $$ = $1; }
    | funcall { $$ = $1; }
    ;
value: {$$ = NULL;}
    | NUM { $$ = newnum($1);}
    | BINARY { $$ = newnum($1); }
    | ROMAN { $$ = newnum($1); }
    | ID { $$ = newref($1); }
    | STR { $$ = newstr($1); }
    | list { $$ = $1; }
    ;
list: '[' ']' { $$ = NULL; } 
    | '[' explist ']' { $$ = $2; } 
    ;

explist: expr
    | expr ',' explist { $$ = newast('L', $1, $3); }
    ;
symlist: ID          { $$ = newsymlist($1, NULL); }
    | ID ',' symlist { $$ = newsymlist($1, $3); }
    ;
return: RETURN expr ';' { $$ = newast('R', $2, NULL); } //TODO: add return
    ;
ufunction: DEFINE  ID '(' symlist ')' '{' stmts '}' { dodef($2,$4,$7); printf("Function %s defined\n", $2->name); }
    | DEFINE  ID '('  ')' '{' stmts '}' { dodef($2,NULL,$6); printf("Function %s defined\n", $2->name); }
    ;
funcall: ID '(' explist ')' { $$ = newcall($1, $3); }
    | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    ;

%%

int main(int argc, char **argv) {

    if(argc < 2) { /* just read stdin */
        yyparse();
        return 0;
    }
    for(int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            perror(argv[i]);
            return (1);
        }
        yyparse();
        fclose(f);
    }
    return 0;
}
