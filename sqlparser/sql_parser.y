%define api.pure
%parse-param {ParserResult* result}
%locations
%no-lines
%verbose
%{
#include "sql_node.h"
#define YYDEBUG 1 
%}

// 指定yyval的类型
%union
{
  struct ParserNode* node;
}

%{
#include "sql_parser.lex.h"
#define YYLEX_PARAM result->scanner
%}

%token CREATE TABLE FLOAT VARCHAR INTEGER
%token <node> NAME
%type <node> create_table_stmt relation_factor table_element_list column_definition data_type
%%

create_table_stmt:
  CREATE TABLE relation_factor '(' table_element_list ')'
  {
    ParserNode* table = (ParserNode*) malloc(sizeof(ParserNode));
    table->num = 2;
    table->item = T_CREATE_TABLE;
    table->child = (ParserNode**) malloc(sizeof(ParserNode) * 2);
    table->child[0] = $3;
    table->child[1] = $5;
    $$ = table; 
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
    ParserNode* element = (ParserNode*)malloc(sizeof(ParserNode));
    element->num = 2;
    element->item = TABLE_ELEMENT;
    element->child = (ParserNode**) malloc(sizeof(ParserNode) * 2);
    element->child[0] = $1;
    element->child[1] = $3;
    $$ = element;    
  }
  ;

column_definition:
  NAME data_type 
  {
    ParserNode* column = (ParserNode*)malloc(sizeof(ParserNode));
    column->num = 2;
    column->item = TABLE_COLUMN;
    column->child = (ParserNode**) malloc(sizeof(ParserNode) * 2);
    column->child[0] = $1;
    column->child[1] = $2;
    $$ = column;
  }
  ;

data_type:
  INTEGER
  {
    ParserNode* node = (ParserNode*)malloc(sizeof(ParserNode));
    node->item = T_TYPE_INT;
    $$ = node;
  }
  | VARCHAR
  {
    ParserNode* node = (ParserNode*)malloc(sizeof(ParserNode));
    node->item = T_TYPE_VARCHAR;
    $$ = node;
  }
  | FLOAT
  {
    ParserNode* node = (ParserNode*)malloc(sizeof(ParserNode));
    node->item = T_TYPE_FLOAT;
    $$ = node;
  }
  ;

%%

void yyerror(YYLTYPE* yyloc, ParserResult* p, char* s, ...)
{
}

/** 语法解析调用入口*/
void parse_sql(ParserResult* p, char* buff, int len)
{
  yylex_init_extra(p, &(p->scanner));
  YY_BUFFER_STATE bp = yy_scan_bytes(buff, len, p->scanner);
  yy_switch_to_buffer(bp, p->scanner);
  yyparse(p);
  yy_delete_buffer(bp, p->scanner);
}
