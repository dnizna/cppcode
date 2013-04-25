%option header-file="sql_parser.lex.h"
%option reentrant noyywrap nodefault bison-bridge bison-locations
%{
#include "sql_node.h"
#include "sql_parser.tab.h"
%}
%%

CREATE { return CREATE; }
TABLE  { return TABLE; }
INT    { return INT; }
VARCHAR {return VARCHAR; }
FLOAT  { return FLOAT; }

<<EOF>> { return END_P; }

[a-z]* {
  ParserNode* node = (ParserNode*) malloc(sizeof(ParserNode));
  yylval->node = node;
  node->num = 0;
  node->item = T_IDENTIFY;
  strcpy(node->attrstr, yytext);
  return NAME;
}

[\r\n\t ] {} 

. { return yytext[0]; }
