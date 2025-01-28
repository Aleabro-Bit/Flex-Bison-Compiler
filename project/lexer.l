%{
#include "parser.tab.h"
#include "abstract_syntax_tree.h"

static char *string_buffer = NULL;
static size_t string_buffer_len = 0;

void init_string_buffer();
void add_string(char ch);
char *get_string_buffer();
void free_string_buffer();

void print_token(int token);
int roman_to_int(const char *roman);

%}
%option noyywrap nounput noinput yylineno case-insensitive
ID [a-zA-Z][a-zA-Z0-9_]*
DEC [0-9]+(\.[0-9]+)?
BIN 0[bB][01]+ 
ROM M*(CM|CD|D?C*)(XC|XL|L?X*)(IX|IV|V?I*)
%x STRING COMMENT

%%

"define"        { return DEFINE; } // Define keyword
"return"        { return RETURN; }
"whether"       { return WHETHER; } // If keyword
"then"          { return THEN; } // If keyword
"otherwise"     { return OTHERWISE; } // Else keyword
"when"          { return WHEN; } // While keyword
"until"         { return UNTIL; } // While keyword
"from"          { return FROM; } // For keyword
"to"            { return TO; }

"num"   { yylval.fn = 1; return DATA_TYPE; }
"str"   { yylval.fn = 2; return DATA_TYPE; }
"bool"  { yylval.fn = 3; return DATA_TYPE; }
"list"  { yylval.fn = 4; return DATA_TYPE; }
"void"  { yylval.fn = 5; return DATA_TYPE; }
"roman" {yylval.fn = 6; return DATA_TYPE; }
"binary" {yylval.fn = 7; return DATA_TYPE; }

"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(MUL);
"/"     return(DIV);
"^"     return(POW);
"="     return(ASSIGN);
"!>"    return(STEP);
"|"     return(ABS);

"and" |
"or"  |
"not" 


">"     { yylval.fn = 1; return CMP;}
"<"     { yylval.fn = 2; return CMP;}
"<>"    { yylval.fn = 3; return CMP;}
"=="    { yylval.fn = 4; return CMP;}
">="    { yylval.fn = 5; return CMP;}
"<="    { yylval.fn = 6; return CMP;}

"sqrt"  { yylval.fn = B_sqrt; return FUNC;}
"exp"   { yylval.fn = B_exp; return FUNC;}
"log"   { yylval.fn = B_log; return FUNC;}
"print" { yylval.fn = B_print; return FUNC;}
"fact"  { yylval.fn = B_fact; return FUNC;}
"sin"   { yylval.fn = B_sin; return FUNC;}
"cos"   { yylval.fn = B_cos; return FUNC;}
"tan"   { yylval.fn = B_tan; return FUNC;}


[,:{}=()~;]	{ yylval.st = strdup(yytext); return *yytext;}

{DEC}	    { yylval.num = atof(yytext); return NUM; }
{BIN}       { yylval.num = strtol(yytext + 2, NULL, 2); return BINARY; }
{ROM}       { yylval.num = roman_to_int(yytext); return ROMAN; }

"<<" {BEGIN(STRING);}
<STRING>"#k"	{ add_string('\n'); }
<STRING>">>"	{ BEGIN(INITIAL); yylval.st = get_string_buffer();  return STR; }
<STRING>"#j"	{ add_string('\t'); }
<STRING>"\"\""	{ add_string('"'); }
<STRING>.	{ add_string(*yytext); }

"/--"	{BEGIN(COMMENT);}
<COMMENT>"--/"	{BEGIN(INITIAL);}
<COMMENT>(.|\n)
"---".*\n    {}

{ID} {
    yylval.s = lookup(yytext);
    return ID;
}

[ \t]+           { ; } // [ \t\n]+
\n      {return EOL;}
.                  { return *yytext; }
%%

void init_string_buffer() {
    free_string_buffer(); // Free initialized buffer
    string_buffer = malloc(1);
    if (!string_buffer) {
        fprintf(stderr, "Errore di memoria: impossibile allocare il buffer della stringa.\n");
        exit(1);
    }
    string_buffer[0] = '\0';
    string_buffer_len = 0;
}

void add_string(char ch) {
    string_buffer = realloc(string_buffer, string_buffer_len + 2);
    if (!string_buffer) {
        fprintf(stderr, "Errore di memoria: impossibile espandere il buffer della stringa.\n");
        exit(1);
    }
    string_buffer[string_buffer_len++] = ch;
    string_buffer[string_buffer_len] = '\0'; // Null-terminate
}

char *get_string_buffer() {
    char *result = strdup(string_buffer); // Copy the content of the buffer
    free_string_buffer();                 
    return result;
}

void free_string_buffer() {
    free(string_buffer);
    string_buffer = NULL;
    string_buffer_len = 0;
}





