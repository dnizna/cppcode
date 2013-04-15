#include <stdio.h>
#include <stdlib.h>
#include <libdrizzle-5.1/libdrizzle.h>

int main()
{
  drizzle_st* conn;
  drizzle_return_t ret;
  drizzle_result_st*  result;
  /** 创建连接对象 */
  if((conn = drizzle_create("10.232.36.177", 3142, "admin", "admin", "test", 0)) == NULL)
  {
    fprintf(stderr, "create sql connection object fail.\n");
    exit(1);
  }
  /** 连接 */
  if((ret = drizzle_connect(conn)) != DRIZZLE_RETURN_OK)
  {
    fprintf(stderr, "sql connection fail.\n");
    exit(1);
  }
  /** 执行查询语句 */ 
  result = drizzle_query(conn, "select * from test", 0, &ret);
  if(ret  != DRIZZLE_RETURN_OK)
  {
    fprintf(stderr, "execute sql fail.\n");
    exit(1);
  }
  drizzle_result_buffer(result);
  int num_field = drizzle_result_column_count(result);
  printf("total %d fields\n", num_field);
  /** 获取结果集 */
  drizzle_row_t row; 
  while((row = drizzle_row_next(result)))
  {
    printf("Data: ");
    for(uint16_t col = 0; col < num_field; ++col)
    {
      printf("%s\t", row[col]);
    }
    puts("");
  }
  /** 释放资源 */
  drizzle_result_free(result);
  drizzle_quit(conn);

  return 0;
}
