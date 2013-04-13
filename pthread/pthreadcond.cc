#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "test.h"

/**
初始化条件变量            pthread_cond_init 语法
基于条件变量阻塞          pthread_cond_wait 语法
解除阻塞特定线程          pthread_cond_signal 语法
在指定的时间之前阻塞      pthread_cond_timedwait 语法
在指定的时间间隔内阻塞    pthread_cond_reltimedwait_np 语法
解除阻塞所有线程          pthread_cond_broadcast 语法
销毁条件变量状态          pthread_cond_destroy 语法
*/


pthread_cond_t c_t;
pthread_mutex_t m_t;
int count = 0;
int inc_num = 100, dec_num = 100;

void* inc(void* ptr)
{
  while(inc_num--)
  {
    pthread_mutex_lock(&m_t);
    while( count == 1)
    {
      pthread_cond_signal(&c_t);
      pthread_cond_wait(&c_t, &m_t);
    }
    count++;
    pthread_mutex_unlock(&m_t);
  }
}

void* dec(void* ptr)
{
  while(dec_num--)
  {
    pthread_mutex_lock(&m_t);
    while(count == 0)
    {
    /** 该函数把调用线程投入睡眠并释放调用线程持有的互斥锁。当其他线程
        发送信号到与c_t相关的条件变量后，该线程再次持有该互斥锁*/
      pthread_cond_signal(&c_t);
      pthread_cond_wait(&c_t, &m_t);
    }
    count--;
    printf("the count value is %d  %d %d\n", count, inc_num, dec_num);
    pthread_mutex_unlock(&m_t);
  }
}

void pthread_cond()
{
  pthread_cond_init(&c_t, NULL);
  pthread_t id_inc, id_dec;

  pthread_create(&id_inc, NULL, inc, NULL);
  pthread_create(&id_dec, NULL, dec, NULL);

  pthread_join(id_inc, NULL);
  pthread_join(id_dec, NULL);
}
