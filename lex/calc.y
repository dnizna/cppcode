%{
#include <stdio.h>
%}
%token NAME NUMBER
%%

statement: NAME '=' expression
      | expression  { printf("= %d\n", $1); }
      ;

expression: expression '+' NUMBER { $$ = $1 + $3; }
    |       expression '-' NUMBER { $$ = $1 - $3; }
    |       expression '*' NUMBER { $$ = $1 * $3; }
    |       NUMBER { $$ = $1; }
      ;
%%

extern FILE* yyin;
main()
{
  do
  {
    yyparse();
  }
  while(!feof(yyin));
}

yyerror(s)
char* s;
{
  fprintf(stderr, "%s\n", s);
}
