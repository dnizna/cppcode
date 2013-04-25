%define api.pure
%parse-param {ParseResult* result}

%{
#include "sql_node.h"
%}

// 指定yyval的类型
%union
{
  struct ParserNode* node;
}
%token CREATE TABLE FLOAT VARCHAR INTEGER
%token <node> NAME
%type <node> create_table_stmt relation_factor table_element_list column_definition data_type
%%

create_table_stmt:
  CREATE TABLE relation_factor '(' table_element_list ')'
  {
    ParseNode* table = (ParseNode*) malloc(sizeof(ParseNode));
    table->num = 2;
    table->item = T_CREATE_TABLE;
    table->child = (ParseNode**) malloc(sizeof(ParseNode) * 2);
    table->child[0] = $3;
    table->child[1] = $5;
    $$ = element; 
  }
  ;

relation_factor:
  NAME
  { $$ = $1; }
  ;

table_element_list:
  column_definition
  {
    $$ = $1;
  }
  | table_element_list ',' column_definition
  {
    ParseNode* element = (ParseNode*)malloc(sizeof(ParseNode));
    element->num = 2;
    element->item = TABLE_ELEMENT;
    element->child = (ParseNode**) malloc(sizeof(ParseNode) * 2);
    element->child[0] = $1;
    element->child[1] = $3;
    $$ = element;    
  }
  ;

column_definition:
  NAME data_type 
  {
    ParseNode* column = (ParseNode*)malloc(sizeof(ParseNode));
    column->num = 2;
    column->item = TABLE_COLUMN
    column->child = (ParseNode**) malloc(sizeof(ParseNode) * 2);
    column->child[0] = $1;
    column->child[1] = $2;
    $$ = column;
  }
  ;

data_type:
  INTEGER
  {
    $$ = (ParseNode*)malloc(sizeof(ParseNode));
    $$->item = T_TYPE_INT;
  }
  | VARCHAR
  {
    $$ = (ParseNode*)malloc(sizeof(ParseNode));
    $$->item = T_TYPE_VARCHAR;
  }
  | FLOAT
  {
    $$ = (ParseNode*)malloc(sizeof(ParseNode));
    $$->item = T_TYPE_FLOAT;
  }
  ;

%%

/** 语法解析调用入口*/
void parse_sql(ParserResult* p, char* buff, int len)
{
  yylex_init_extra(p, &(p->scanner));
  YY_BUFFER_STATE bp = yy_scan_bytes(buff, len, p->scanner);
  yy_switch_to_buffer(bp, p->scanner);
  yy_parser(p);
  yy_delete_buffer(bp, p->scanner);
}
