%{
#include "parser.tab.h"
#include "helper.h"

static char *string_buffer = NULL;
static size_t string_buffer_len = 0;

void init_string_buffer();
void add_string(char ch);
char *get_string_buffer();
void free_string_buffer();

%}
%option noyywrap nounput noinput yylineno case-insensitive
ID [a-zA-Z][a-zA-Z0-9_]*
DEC [0-9]+(\.[0-9]+)?
BIN 0[bB][01]+ 
ROM 0(M*(CM|CD|D?C*)(XC|XL|L?X*)(IX|IV|V?I*))
%x STRING COMMENT

%%

"define"        { return DEFINE; }      // Define keyword
"give_back"     { return RETURN; }      // Return keyword
"whether"       { return WHETHER; }     // If keyword
"then"          { return THEN; }        // If keyword
"otherwise"     { return OTHERWISE; }   // Else keyword
"when"          { return WHEN; }        // While keyword
"until"         { return UNTIL; }       // Do keyword
"from"          { return FROM; }        // For keyword
"to"            { return TO; }

"num"   { yylval.dt = 1; return DATA_TYPE; }
"str"   { yylval.dt = 2; return DATA_TYPE; }
"list"  { yylval.dt = 3; return DATA_TYPE; }
"void"  { yylval.dt = 5; return DATA_TYPE; }
"roman" {yylval.dt = 6; return DATA_TYPE; }
"binary" {yylval.dt = 7; return DATA_TYPE; }

"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(MUL);
"/"     return(DIV);
"^"     return(POW);
"%"     return(MOD);
"="     return(ASSIGN);
"!>"    return(STEP);
"|"     return(ABS);

"and" return(AND);
"or"  return(OR);  
"not" return(NOT); 


">"     { yylval.fn = 1; return CMP;}
"<"     { yylval.fn = 2; return CMP;}
"<>"    { yylval.fn = 3; return CMP;}
"=="    { yylval.fn = 4; return CMP;}
">="    { yylval.fn = 5; return CMP;}
"<="    { yylval.fn = 6; return CMP;}

"sqrt"          { yylval.fn = B_sqrt; return FUNC;}
"exp"           { yylval.fn = B_exp; return FUNC;}
"log"           { yylval.fn = B_log; return FUNC;}
"print"         { yylval.fn = B_print; return FUNC;}
"fact"          { yylval.fn = B_fact; return FUNC;}
"sin"           { yylval.fn = B_sin; return FUNC;}
"cos"           { yylval.fn = B_cos; return FUNC;}
"tan"           { yylval.fn = B_tan; return FUNC;}
"size"          { yylval.fn = B_size; return FUNC;}
"get"           { yylval.fn = B_get; return FUNC;}
"input"         { yylval.fn = B_input; return FUNC;}
"split"         { yylval.fn = B_split; return FUNC;}
"count_char"    { yylval.fn = B_count_char; return FUNC;}
"casual"        { yylval.fn = B_casual; return FUNC;}


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
    yylval.s = calloc(1, sizeof(struct symbol));
    yylval.s->name = strdup(yytext);
    return ID;
}

[ \t\n]+           { ; } // [ \t\n]+

.                  { return *yytext; }
%%

void init_string_buffer() {
    free_string_buffer(); // Free initialized buffer
    string_buffer = malloc(1);
    if (!string_buffer) {
        fprintf(stderr, "Error impossible to allocate the buffer\n");
        exit(1);
    }
    string_buffer[0] = '\0';
    string_buffer_len = 0;
}

void add_string(char ch) {
    string_buffer = realloc(string_buffer, string_buffer_len + 2);
    if (!string_buffer) {
        fprintf(stderr, "Error in memory: impossible to expand the buffer.\n");
        exit(1);
    }
    string_buffer[string_buffer_len] = ch;
    string_buffer_len++;
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





