%{
#include <stdio.h>
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

%type <integer> NUM
%type <character> VAR
%type <character> CONST

%%
S : A B;

A : R POINT
| R COND RL POINT;

RL : R
|RL COMMA R;

R : CONST ARGOPEN L ARGCLOSE;

L : L COMMA C
| C;

C : LISTBEGIN K LISTEND
| VAR;

K : C PIPE K
| C;

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
