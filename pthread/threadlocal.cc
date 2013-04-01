#include <stdio.h>
#include <stdlib.h>

#include "test.h"

pthread_key_t key;

typedef struct
{
    int  i1, i2;
} thread_value;


void* fun_thread1(void* arg)
{
    thread_value value = {0, 0 };
    int rt;

    /** 存放threadlocal变量*/
    if(rt = pthread_setspecific(key, (void*)&value))
    {
        fprintf(stderr, "[thread %d] set thread local value faile! error code is %d .\n", pthread_self(), rt);
        return NULL;
    }

    /** 获取threadlocal变量 */
    thread_value* local_value = (thread_value*) pthread_getspecific(key);

    printf("[thread %d] thread local value is %d %d .\n", pthread_self(), local_value->i1, local_value->i2);
    return NULL;
}


void* fun_thread2(void* arg)
{
    thread_value value = {1, 1 };
    int rt;

    /** 存放threadlocal变量*/
    if(rt = pthread_setspecific(key, (void*)&value))
    {
        fprintf(stderr, "[thread %d] set thread local value faile! error code is %d .\n", pthread_self(), rt);
        return NULL;
    }

    /** 获取threadlocal变量 */
    thread_value* local_value = (thread_value*) pthread_getspecific(key);

    printf("[thread %d] thread local value is %d %d .\n", pthread_self(), local_value->i1, local_value->i2);
    return NULL;
}

void thread_exit(void* arg)
{
    printf("[thread %d] exit. \n", pthread_self());
}

void thread_local_use()
{
    pthread_t ptd1, ptd2;
    int rt;

    /**
     * 创建一个 key
     * 参数1. 创建的 key 的值
     * 参数2. 线程退出时调用的函数,可以来做一些清理工作
     */
    if(rt = pthread_key_create(&key, thread_exit))
    {
        fprintf(stderr, "pthread_key_create error! error code is %d .\n", rt);
        return;
    }
    /** 创建第一个线程 */
    if(rt = pthread_create(&ptd1, NULL, fun_thread1, NULL))
    {
        fprintf(stderr, "the first thread create faild! error code is %d. \n", rt);
        return;
    }

    /** 创建第二个线程*/
    if(rt = pthread_create(&ptd2, NULL, fun_thread2, NULL))
    {
        fprintf(stderr, "the second thread create faild! error code is %d. \n", rt);
        return;
    }

    /** 阻塞主线程，等待第一线程执行完成*/
    if(rt = pthread_join(ptd1, NULL))
    {
        fprintf(stderr, "thread join faild! error code is %d. \n", rt);
        return;
    }

    /** 等待第二个线程执行完成*/
    if(rt = pthread_join(ptd2, NULL))
    {
        fprintf(stderr, "thread join faild! error code is %d. \n", rt);
        return;
    }

}
