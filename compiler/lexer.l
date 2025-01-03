%{
#include <ctype.h>
%}

%%

[a-z]      { putchar(toupper(yytext[0])); } /* Convert lowercase to uppercase */
.          { putchar(yytext[0]); }         /* Copy all other characters */
\n         { putchar('\n'); }              /* Handle newlines explicitly */

%%

/* Use %option main to include a main function provided by flex */

