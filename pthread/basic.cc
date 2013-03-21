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
    thread_args* arg = (thread_args*) args;
    printf("[thread %d]  output is : %s\n", arg->thread_id, arg->str);
}

void basic_use()
{
    thread_args args;
    strcpy(args.str, "hahahaha");

    /** 创建线程*/
    if(pthread_create(&args.thread_id, NULL, basic_thread, &args))
    {
        printf("create thread error!\n");
        return;
    }
    usleep(1000);
}
