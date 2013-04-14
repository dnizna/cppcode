#ifndef CONN_QUEUE_H
#define CONN_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ev.h"

/** 描述每一个连接 */
struct conn_item {
  /** 连接的socket文件描述符 */
  int fd;
  conn_item* next; 
};

/**
 请求队列
*/
class conn_queue
{
  private:
    conn_item*      head;
    /** 互斥锁 */
    pthread_mutex_t lock;

  public:
    conn_queue();
    ~conn_queue();
    /** 出队列 */ 
    conn_item* pop();
    /** 入队列 */ 
    void push(conn_item* item);
};

#endif
