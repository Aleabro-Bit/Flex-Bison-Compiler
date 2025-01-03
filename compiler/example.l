%{
#include <stdio.h>
%}

%%

[0-9]+       { printf("Number: %s\n", yytext); }
[a-zA-Z]+    { printf("Word: %s\n", yytext); }
\n           { /* Ignore newlines */ }
.            { printf("Other: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

