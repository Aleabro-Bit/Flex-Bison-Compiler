%{
#include "parser.tab.h"
#include <abstract_syntax_tree.h>

void add_string(char ch);
void print_token(int token);
int roman_to_int(const char *roman);

%}
%option noyywrap nounput noinput yylineno case-insensitive
ID [a-zA-Z][a-zA-Z0-9_]*
DEC [0-9]+(.[0-9]+)?
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
"list"          { return LIST; }
"num"           { return NUMBER; }
"string"        { return STRING; }
"boolean"       { return BOOLEAN; }
"func"          { return FUNC; }
"shift"         { return SHIFT; } //Switch keyword
"event"         { return EVENT; } //Case keyword

"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(MUL);
"/"     return(DIV);
"^"     return(POW);
"="     return(ASSIGN);
"!>"    return(STEP);
"|"     return(ABS);

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

\n      {return EOL;}
[,:{}=()~;]	{ yylval.st = strdup(yytext); return *yytext;}

{DEC}	{ yylval.num = atof(yytext); return NUM; }
{BIN}       { yylval.num = strtol(yytext + 2, NULL, 2); return BINARY; }
{ROM}       { yylval.num = roman_to_int(yytext); return ROMAN; }

"<<" {BEGIN(STRING);}
<STRING>"\\k"	{ add_string('\n'); }
<STRING>">>"	{ BEGIN(INITIAL); return STR; }
<STRING>"\"\""	{ add_string('"'); }
<STRING>.	{ add_string(*yytext); }

"/--"	{BEGIN(COMMENT);}
<COMMENT>"--/"	{BEGIN(INITIAL);}
<COMMENT>(.|\n)
"---".*\n    {}

int|char|float|const|enum|extern|long|double|void|if|else|while|for|auto|return { 
    return KEYWORD; 
}

{ID} {
    yylval.st = strdup(yytext);
    return ID;
}

[ \t]+           { ; } // [ \t\n]+
.                  { return *yytext; }
%%

void add_string(char ch)
{
int len = strlen(yylval.st);
yylval.st = realloc (yylval.st, len+2);
yylval.st[len] = ch;
yylval.st[len+1] = '\0';
}


int roman_to_int(const char *roman) {
    int result = 0;
    while (*roman) {
        switch (*roman) {
            case 'M': result += 1000; break;
            case 'D': result += 500; break;
            case 'C': 
                if (*(roman + 1) == 'M' || *(roman + 1) == 'D') result -= 100;
                else result += 100;
                break;
            case 'L': result += 50; break;
            case 'X': 
                if (*(roman + 1) == 'C' || *(roman + 1) == 'L') result -= 10;
                else result += 10;
                break;
            case 'V': result += 5; break;
            case 'I': 
                if (*(roman + 1) == 'X' || *(roman + 1) == 'V') result -= 1;
                else result += 1;
                break;
            default: return -1; // Invalid Roman numeral
        }
        roman++;
    }
    return result;
}

