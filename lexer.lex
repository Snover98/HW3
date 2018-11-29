%{
/*C lang stuff*/
#include "tokens.h"
%}

%option noyywrap
%option yylineno
%option caseless



%%

															badInput(yytext); /*DEFAULT*/
%%

