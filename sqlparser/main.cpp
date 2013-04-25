#include <stdio.h>
#include <stdlib.h>

#include "sql_node.h"
#include "create_table_stmt.h"

void travel_stmt_column(ParserNode* node, CreateTableStmt& createStmt)
{
  if(node == NULL ) return;
  if(node->item == TABLE_COLUMN)
  {
    ParserNode* column_value = node->child[0];
    ParserNode* column_type  = node->child[1];
  
    ColumnNode column_node;
    column_node.type = column_type->item;
    strcpy(column_node.value, column_value->attrstr);
   
    createStmt.add_column(column_node);
    return;
  }

  int num = node->num;
  for(int i = 0; i < num; ++i)
  {
    travel_stmt_column(node->child[i], createStmt);
  }
}

void sql_tree_to_stmt(ParserNode* node, CreateTableStmt& createStmt)
{
  if(node->item == T_CREATE_TABLE)
  {
    createStmt.set_table_name(node->child[0]->attrstr);
  }
  
  travel_stmt_column(node->child[1], createStmt);
}

int main()
{
  char* sql1 = "CREATE TABLE tabletest ( pk INT, name VARCHAR, count FLOAT)";
  ParserResult* result = (ParserResult*)malloc(sizeof(ParserResult));
  parse_sql(result, sql1, strlen(sql1));

  CreateTableStmt createStmt1;
  sql_tree_to_stmt(result->node, createStmt1);
  createStmt1.print();

  char* sql2 = "CREATE TABLE hahs ( name VARCHAR, pppp INT, good FLOAT, price FLOAT, aaa VARCHAR)";
  ParserResult* result2 = (ParserResult*)malloc(sizeof(ParserResult));
  CreateTableStmt createStmt2;
  parse_sql(result2, sql2, strlen(sql2));
  sql_tree_to_stmt(result2->node, createStmt2);
  createStmt2.print();

  return 0;
}
