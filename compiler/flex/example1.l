%x COMMENT
%s HEX
%s OCT
NUM [0-9A-F]+
ID [a-z]+
%%
"/*" BEGIN(COMMENT);
<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>.
{ID} printf("ID: %s\n", yytext);
<HEX>{NUM} printf("Num: %ld\n", strtol(yytext, NULL, 16));
<OCT>{NUM} printf("Num: %ld\n", strtol(yytext, NULL, 8));
{NUM} printf("Num: %d\n", atoi(yytext));
"/HEX" BEGIN(HEX);
"/OCT" BEGIN(OCT);
"/DEC" BEGIN(INITIAL);
.
