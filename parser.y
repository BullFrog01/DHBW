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
	typedef struct lin_list_upper
	{
		char *payloadU;
		LinList_lower_p lowerList;
		struct lin_list_upper *next; // Zeiger auf das nächste Element
	} LinListCell_upper, *LinList_upper_p;
	LinList_upper_p upperlist_p;	
}

%token LISTBEGIN LISTEND ARGBEGIN ARGEND
%token COMMA POINT
%token PIPE
%token COND
%token EQUAL SMALLER GREATER
%token VAR CONST NUM
%token END

%type <integer> NUM
%type <character> VAR
%type <character> CONST
%type <upperlist_p> A
%type <upperlist_p> B
%type <upperlist_p> C

%left COMMA

%%
S : A END {printUpper($1);};

A : B POINT	{$$ = $1;}//zusätzliche Liste upper erstellen
| B COND C POINT {appendUpper($1, $3);} {$$ = $1;};

B : CONST ARGBEGIN D ARGEND {$$ = createList($1);}; // upper list füllen mit const $1 ; übergebn liste $3 an pointer 

D : VAR //erstes Listenelement lower
| LISTBEGIN LISTEND		//in lower
| LISTBEGIN E LISTEND 	//erzeuge Listenelement: payload=[E]
| D COMMA D;			//verbinde Listenelemente


E : VAR
| VAR PIPE R;

R : LISTBEGIN LISTEND
| LISTBEGIN E LISTEND
| VAR;

C : B {$$ = $1;} //erstes Listenelement -> Liste erstellen
| C COMMA B {appendUpper($1, $3);}// B an Liste anhängen
| F {$$ = $$;}
| C COMMA F;

F : VAR G VAR;

G : GREATER
| SMALLER
| EQUAL; //greater/smaller equal fehlt
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
