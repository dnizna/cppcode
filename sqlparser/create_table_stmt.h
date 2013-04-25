#ifndef CREATE_TABLE_STMT_H
#define CREATE_TABLE_STMT_H

#define MAX_COLUMN  10
#define MAX_LEN 100

#include "sql_node.h"
#include <string.h>

struct ColumnNode
{
  SqlItemType type;
  char        value[MAX_LEN];
};

class CreateTableStmt
{
  public:
    CreateTableStmt()
    {
      column_num = 0;
    }
 
    char* get_table_name()
    {
      return table_name;
    }

    void set_table_name(char* name)
    {
      strcpy(table_name, name);
    }
    
    const ColumnNode& get_column(int index) const
    {
      return columns[index];
    }

    int get_column_num() const
    {
      return column_num;
    }

    void add_column(const ColumnNode& columnNode)
    {
      columns[column_num].type = columnNode.type;
      strcpy(columns[column_num].value, columnNode.value);
      column_num++;
    }
    
  private:
    char table_name[MAX_LEN];

    int  column_num;
    ColumnNode  columns[MAX_COLUMN];
};

#endif
