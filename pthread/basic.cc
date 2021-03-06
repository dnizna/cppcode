#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

typedef struct
{
    pthread_t thread_id;
    char str[100];
} thread_args;

void* basic_thread(void* args)
{
    int rt;
    if((rt = pthread_detach(pthread_self())))
    {
        fprintf(stderr, "[thread %d] call pthread_detach fail! error code is %d .", pthread_self(), rt);
        return NULL;
    }
    // 该函数用于指明用于线程thread的存储空间可以在该线程终止后再利用
    // 如果thread未停止，pthread_detach()不会导致它终止
    // 对同一个线程多次调用pthread_detach()的行为未定义
    thread_args* arg = (thread_args*) args;
    printf("[thread %d]  output is : %s\n", arg->thread_id, arg->str);

    return (void*)"finish";
}

void basic_use()
{
    thread_args args;
    strcpy(args.str, "hahahaha");
    int rt;

    /** 创建线程
     *  参数1. 线程ID
     *  参数2. 线程属性配置，如优先级
     *  参数3. 执行函数
     *  参数4. 执行函数的参数
     */
    if((rt = pthread_create(&args.thread_id, NULL, basic_thread, &args)))
    {
        fprintf(stderr, "create thread error! error code is %d .\n", rt);
        return;
    }

    void* value;
    // 主线程等待新创建的线程结束
    if((rt = pthread_join(args.thread_id, &value)))
    {
        fprintf(stderr, "thread_join fail. error code is %d .\n", rt);
    }
    else
    {
        printf("the return value of created thread is [%s] .\n", (char*) value);
    }
}
