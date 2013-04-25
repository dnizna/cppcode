#ifndef SQL_NODE_H
#define SQL_NODE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum SqlItemType
{
  T_CREATE_TABLE,
  T_TYPE_VARCHAR,
  T_TYPE_INT,
  T_TYPE_FLOAT,
  T_IDENTIFY,

  TABLE_ELEMENT,
  TABLE_COLUMN,
};

struct ParserNode
{
  struct ParserNode** child;
  char*        attrstr;
  int          num;

  enum SqlItemType  item;
};

typedef struct 
{
  void* scanner;
  struct ParserNode* node;
} ParserResult;

#ifdef __cplusplus
extern "C" {
#endif

extern void parse_sql(ParserResult* p, char* buff, int len);

#ifdef __cplusplus
}
#endif

#endif
