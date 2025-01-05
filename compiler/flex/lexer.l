%{

#include "parser.tab.h"


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
    CONTROL_STRUCTURE,
    SPECIAL_CHAR,
    FUNC,
    INSTRUCTION,
	};
void add_string(char ch);
void print_token(int token);
int roman_to_int(const char *roman);

struct {
    int num;
    char *st;
} yylval;

%}
%option noyywrap nounput noinput
ID [a-zA-Z][a-zA-Z0-9_]*
DEC [0-9]+
BIN 0[bB][01]+ 
ROM M*(CM|CD|D?C*)(XC|XL|L?X*)(IX|IV|V?I*)
%x STRING COMMENT

%%

"define"        { return KEYWORD; } // Define keyword
"return"        { return KEYWORD; }
"whether"       { return KEYWORD; } // If keyword
"otherwise"     { return KEYWORD; } // Else keyword
"when"          { return KEYWORD; } // While keyword
"from"          { return KEYWORD; } // For keyword
"to"            { return KEYWORD; }
"step"          { return KEYWORD; }
"list"          { return DATA_TYPE; }
"int"           { return DATA_TYPE; }
"float"         { return DATA_TYPE; }
"string"        { return DATA_TYPE; }
"boolean"       { return DATA_TYPE; }

"==" | "+" | "-" | "*" | "/" | "<" | ">" | "&&" | "||" | "!" { return yytext[0]; }

"{"            { return SPECIAL_CHAR; }
"}"            { return SPECIAL_CHAR; }
"("            { return SPECIAL_CHAR; }
")"            { return SPECIAL_CHAR; }
";"            { return SPECIAL_CHAR; }
","            { return SPECIAL_CHAR; }

"func"          { return FUNC; }
\n            { return INSTRUCTION; }

{DEC}	{ yylval.num = atoi(yytext); return NUM; }
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
    return IDENTIFIER;
}

[ \t\n]+           { ; }


.                  { printf("Unknown token: %s\n", yytext); }
%%

int main(void) {
    yylval.st = malloc(1);
    int tok;
    while ((tok = yylex()) != EOF) {
        print_token(tok);
    }
    return 0;
}

void add_string(char ch)
{
int len = strlen(yylval.st);
yylval.st = realloc (yylval.st, len+2);
yylval.st[len] = ch;
yylval.st[len+1] = '\0';
}

void print_token(int token) {
    switch (token) {
        case NUM:
            printf("Decimal Number: %d\n", yylval.num);
            break;
        case BINARY:
            printf("Binary Number: %d\n", yylval.num);
            break;
        case ROMAN:
            printf("Roman Number: %d\n", yylval.num);
            break;
        case STR:
            printf("String: %s\n", yylval.st);
            break;
        case FUNC:
            printf("Function declaration: '%s'\n", yylval.st);
            break;
        case IDENTIFIER:
            printf("Identifier: %s\n", yytext);
            break;
        case KEYWORD:
            printf("Keyword");
            break;
        
    }
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
