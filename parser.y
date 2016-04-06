%{
#include <stdio.h>
#include <stdlib.h>
  void yyerror(char *message);
%}

%start S
%union {
	char* character;
	int integer;	
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

%left COMMA;

%%
S : A END {printf("Test");};

A : B POINT
| B COND C POINT;

B : CONST ARGBEGIN D ARGEND;

D : VAR
| LISTBEGIN LISTEND
| LISTBEGIN E LISTEND
| D COMMA D;


E : VAR
| VAR PIPE R;

R : LISTBEGIN LISTEND
| LISTBEGIN E LISTEND
| VAR;

C : B
| B COMMA B
| F
| F COMMA B;

F : VAR G VAR
| VAR G G VAR;

G : GREATER
| SMALLER
| EQUAL
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
