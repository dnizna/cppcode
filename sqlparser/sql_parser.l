%{
#include "sql_node.h"
%}
%%

CREATE { return CREATE; }
TABLE  { return TABLE; }
[A-Z_][A-Za-z_]* {
  ParseNode* node = (ParseNode*) malloc(sizeof(ParseNode));
  yyval->node = node;
  node->num = 0;
  node->item = T_IDENTIFY;
  strcpy(node->attrstr, yytext);
  return NAME;
}

[\r\n\t ] {} 
