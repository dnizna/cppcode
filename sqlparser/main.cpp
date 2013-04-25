#include <stdio.h>
#include <stdlib.h>

#include "sql_node.h"
#include "create_table_stmt.h"

int main()
{
  char* sql = "CREATE TABLE tabletest ( pk INT, name VARCHAR)";
  ParserResult* result = (ParserResult*)malloc(sizeof(ParserResult));

  puts("begin");
  parse_sql(result, sql, strlen(sql));

  puts("end");
  ParserNode* node = result->node; 
  if(node->item == T_CREATE_TABLE)
  {
    printf("tree num is : %d\n", node->num);
    printf("table name is : %s\n", node->child[0]->attrstr);
  }
 
  return 0;
}
