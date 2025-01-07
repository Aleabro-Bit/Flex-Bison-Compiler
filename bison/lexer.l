%{

#include "parser.tab.h"

void add_string(char ch);
void print_token(int token);
int roman_to_int(const char *roman);

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

"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(MUL);
"/"     return(DIV);
"^"     return(POW);
"=="    return(EQ);
"!="    return(NOTEQUAL);
">"     return(GT);
">="    return(GE);
"<"     return(LT);
"<="    return(LE);

[,:{}=()~;]	{ yylval.st = strdup(yytext); return *yytext;}
\n          { return *yytext; }


"func"          { return FUNC; }


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
    return ID;
}

[ \t\n]+           { ; }


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

