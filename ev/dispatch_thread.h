#ifndef DISPATCH_THREAD_H
#define DISPATCH_THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

#include "ev.h"
#include "conn_queue.h"
#include "work_thread.h"

/** 工作线程数量 */
#define NUM_OF_WORK_THREAD 10

/** 分发请求的线程 */
class dispatch_thread
{
  private:
    struct ev_loop*  loop;
    /** 事件watcher */
    struct ev_io     watcher;
    /** 工作线程数量  */
    work_thread      wthread[NUM_OF_WORK_THREAD];
    int      current_thread;

  private:
   void dispatch_conn();

  public:
    dispatch_thread();
      /** 线程初始化 */
    void start(int listenfd);
      /** 回调函数，分发请求到工作线程 */
    void call_back(struct ev_loop* loop, ev_io* w, int revents); 
};

#endif
