%{
#include <stdio.h>
#include <stdlib.h>
#include "listbib.h"
void yyerror(char *message);
%}

%start S
%union {
	char* character;
	int integer;
	struct varlist *VarlistCell;
	struct termlist *TermlistCell;
	struct clause *ClauseCell;
}

%token LISTBEGIN LISTEND 
%token ARGBEGIN ARGEND
%token COMMA POINT
%token PIPE
%token COND
%token EQUAL SMALLER GREATER
%token VAR CONST NUM
%token END

%type <integer> NUM
%type <character> VAR
%type <character> CONST
%type <ClauseCell> A
%type <TermlistCell> B
%type <TermlistCell> C
%type <VarlistCell> D
%type <VarlistCell> DL
%type <VarlistCell> E
%type <TermlistCell> F
%type <character> G


%left COMMA

%%
S : A END {printTermlist($1);};

A : B POINT	{$$ = createClause($1);}
| B COND C POINT {$$ = createClause(appendTermlist($1, $3));};

B : CONST ARGBEGIN DL ARGEND {$$ = createTermlistCell($3, $1);};

DL : D {$$ = $1;}
| DL COMMA D {$$ = appendVarlist($1, $3);};

D : VAR {$$ = createVarlistCell($1);}
| LISTBEGIN LISTEND {$$ = NULL;} //leere Listen werden nicht beachtet
| LISTBEGIN E LISTEND {$$ = $2;};

E : VAR {$$ = createVarlistCell($1);}
| VAR PIPE D {$$ = addVarlistCell(createVarlistCell($1), &$3);};

C : B {$$ = $1;}
| C COMMA B {$$ = appendTermlist($1, $3);}
| F {$$ = $1;}
| C COMMA F {$$ = appendTermlist($1, $3);};

F : VAR G VAR {$$ = createTermlistCell(addVarlistCell(createVarlist($1), createVarlist($3)), $2);}; 

G : GREATER {$$ = ">";} 
| SMALLER {$$ = "<";}
| EQUAL {$$ = "=";}
| GREATER EQUAL {$$ = ">=";}
| SMALLER EQUAL {$$ = "<=";}
| SMALLER GREATER {$$ = "<>";};

%%
int main(int argc, char **argv)
{
  yyparse();
  return 0;
}

void yyerror(char *message)
{
  printf ("Good Bye!\n");
}
