%{
/*C lang stuff*/
#include "tokens.h"
%}

%option noyywrap
%option yylineno
%option caseless



%%

void								return VOID;

int									return INT;

byte								return BYTE;

b									return B;

bool								return BOOL;

struct								return STRUCT;

and									return AND;

or									return OR;

true								return TRUE;

false								return FALSE;

return								return RETURN;

if									return IF;

else								return ELSE;

while								return WHILE;

break								return BREAK;

continue							return CONTINUE;

;									return SC;

,									return COMMA;

\.									return PERIOD;

\(									return LPAREN

\)									return RPAREN;

\{									return LBRACE;

\}									return RBRACE;

=									return ASSIGN;

(==)|(!=)|(<)|(>)|(<=)|(>=)			return RELOP;




%%

