#include "work_thread.h"

static void async_cb(EV_P_ ev_async* watcher, int revents)
{
  work_thread* wthread = (work_thread*)watcher->data;
  wthread->handle_request(loop, watcher, revents);
}

static void* start_loop(void* arg)
{
  struct ev_loop* loop = (struct ev_loop*) arg;
  ev_loop(loop, 0);  
}

static void async_handle_data(struct ev_loop* loop, struct ev_io* watcher, int revents)
{
  work_thread* wthread = (work_thread*)watcher->data;
  wthread->handle_data(loop, watcher, revents);
}

work_thread::work_thread()
{
  int err;
  loop = ev_loop_new(0);
  if(!loop)
  {
    fprintf(stderr, "allocate loop fail.\n");
    exit(0);
  }
  /** 初始化事件监听 */
  async_watcher.data = this;
  ev_async_init(&async_watcher, async_cb);
  ev_async_start(loop, &async_watcher);

  /** 开启监听线程 */
  if((err = pthread_create(&th_id, NULL, start_loop, (void*)loop)) < 0)
  {
    fprintf(stderr, "pthread create fail.\n");
    exit(0);
  }
}

/** 处理数据  */
void work_thread::handle_data(struct ev_loop* loop, struct ev_io* watcher, int& revents)
{
  char buff[1024];
  int ret;
  if((ret = recv(watcher->fd, buff, 1024, 0)) < 0)
  {
    fprintf(stderr, "thread[%d] receive data error. ret: %d\n", pthread_self(), ret);
    close(watcher->fd);
    ev_io_stop(loop, watcher);
  }
  else
  {
    if(ret > 0)
    {
      printf("receive data is [%s]\n", buff);
    }
    else
    {
      close(watcher->fd);
      ev_io_stop(loop, watcher);
    } 
  } 
}

/** 工作线程接收到分发线程的信号后调用的函数 */
void work_thread::handle_request(EV_P_ ev_async* watcher, int& revents)
{
  /** 获取到一个请求 */
  conn_item* conn = que.pop();
  /** 另外起一个watcher用来接收和处理数据*/
  ev_io* recv_watcher = (ev_io*)malloc(sizeof(ev_io));
  recv_watcher->data = this;
  ev_io_init(recv_watcher, async_handle_data, conn->fd, EV_READ);
  ev_io_start(this->loop, recv_watcher); 
  free(conn);
}

void work_thread::start_work(conn_item* item)
{
  /** 先将请求入队 */
  que.push(item);
  /** 发送信号通知工作线程接收请求*/
  ev_async_send(loop, &async_watcher);
}
