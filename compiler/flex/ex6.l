%{
#include <stdio.h>
#include <stdlib.h>

char *st;
int num;
enum {
	NUM=1,
	STR=2,
	};
void add_string(char ch);

%}

%x STRING COMMENT


%%

(0|[1-9][0-9]*)	{ num = atoi(yytext); return NUM; }

"\"" {BEGIN(STRING);}
<STRING>"\\k"	{ add_string('\n'); }
<STRING>"\""	{ BEGIN(INITIAL); return STR;}
<STRING>"\"\""	{ add_string('"'); }
<STRING>.	{ add_string(*yytext); }

"/--"	{BEGIN(COMMENT);}
<COMMENT>"--/"	{BEGIN(INITIAL);}
<COMMENT>(.|\n)
 
%%

int main(void)
{
st = malloc(1);
st[0] = '\0';
int tok;
while (tok = yylex())
{

switch(tok){
	case STR:
		printf("String: '%s'\n", st);
		break;
	case NUM:
        printf("Number: '%d'\n", num);
        break;
	}
}
return 0;
}

void add_string(char ch)
{
int len = strlen(st);
st = realloc (st, len+2);
st[len] = ch;
st[len+1] = '\0';
}

