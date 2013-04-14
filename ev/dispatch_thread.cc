#include "dispatch_thread.h"


/** 有请求时的回调 */
static void accept_callback(struct ev_loop* loop, ev_io* watcher, int revents)
{
  dispatch_thread* dthread = (dispatch_thread*) watcher->data;
  dthread->call_back(loop, watcher, revents);
}

/** 构造函数 */
dispatch_thread::dispatch_thread()
{
  loop = ev_default_loop(0);
  current_thread = 0;
}

void dispatch_thread::start(int listenfd)
{
  watcher.data = this;
  /** 监听服务端IO读事件 */
  ev_io_init(&watcher, accept_callback, listenfd, EV_READ);
  /** 启动watcher */
  ev_io_start(loop, &watcher);
  ev_loop(loop, 0);
}


/** 将请求分发到工作线程 */
void dispatch_thread::call_back(struct ev_loop* loop, ev_io* w, int revents)
{
  int accept_fd, err;
  struct sockaddr_in sin;
  socklen_t addrlen = sizeof(struct sockaddr);
  /** 有客户端连接*/
  while((accept_fd = accept(w->fd, (struct sockaddr*)&sin, &addrlen)) < 0)
  {
    if(errno == EAGAIN || errno == EWOULDBLOCK)
    {
      continue;
    }
    else
    {
      fprintf(stderr, "accept fd[%d] fail.\n", w->fd);
    }
  }
  /** 选择一个工作线程分发*/
  int index = ++current_thread % NUM_OF_WORK_THREAD;
  conn_item* item = (conn_item*)malloc(sizeof(conn_item));
  item->fd = accept_fd;
  wthread[index].start_work(item);
}
