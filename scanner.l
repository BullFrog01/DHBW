%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
\[	 	{	return LISTBEGIN;	}
\] 		{	return LISTEND;		}
\(		{	return ARGBEGIN;	}
\) 		{	return ARGEND;		}	
\, 		{	return COMMA;		}
\> 		{	return GREATER;		}
\< 		{	return SMALLER;		}
\:\-	{	return COND;		}
\=		{	return EQUAL;		}
\.		{	return POINT;		}
\|		{	return PIPE;		}
[A-Z][A-Za-z0-9]* 	{yylval.character = strdup(yytext);
						return VAR;}
[a-z][A-Za-z0-9]*	{yylval.character = strdup(yytext); 
						return CONST;}
[1-9][0-9]*|0		{return NUM;}
\n		{	return END;}
[ ]+ ;

