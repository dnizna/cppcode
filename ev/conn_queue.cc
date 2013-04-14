#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "conn_queue.h"

conn_queue::conn_queue()
{
  head =  NULL;
  pthread_mutex_init(&lock, NULL);
}

conn_queue::~conn_queue()
{
  conn_item* item;
  while(head != NULL)
  {
    item = head;
    head = head->next;
    free(item);
  }
}

/** 出队列 */
conn_item* conn_queue::pop()
{
  if(head == NULL)
    return NULL;
  pthread_mutex_lock(&lock);
  conn_item* item = head;
  head = head->next;
  pthread_mutex_unlock(&lock);
  return item;
}

/** 入队列*/
void conn_queue::push(conn_item* item)
{
  pthread_mutex_lock(&lock);
  item->next = head;
  head = item;
  pthread_mutex_unlock(&lock);
}
