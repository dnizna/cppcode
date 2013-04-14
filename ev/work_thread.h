#ifndef WORK_THREAD_H
#define WORK_THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "ev.h"
#include "conn_queue.h"

class work_thread
{
  private:
    /** 分发到该线程的请求队列*/
    conn_queue         que;
    /** 线程id */
    pthread_t          th_id;
    /** 事件循环 */
    struct ev_loop*    loop;
    /** 异步事件watcher */
    struct ev_async    async_watcher;

  public:
    work_thread();
    /** 开始工作线程 */
    void start_work(conn_item* item);
    /** 处理请求 */
    void handle_request(EV_P_ ev_async* watcher, int& revents);
    /** 处理数据 */
    void handle_data(struct ev_loop* loop, struct ev_io* watcher, int& revents);
};

#endif
