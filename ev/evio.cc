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
#include "dispatch_thread.h"

#define LISTENQ 10

int init_server(char* server, int port)
{
  int listenfd, err;
  struct sockaddr_in serveraddr;

  /** 创建套接字 */  
  if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
    fprintf(stderr, "init socket fail. errno [%d]\n", listenfd);
    exit(0);
  }

  /** 初始化服务器地址和端口*/
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port);
  if((err = inet_pton( AF_INET,  server, &serveraddr.sin_addr )) < 0)
  {
    fprintf(stderr, "server address format error. errno [%d]\n", err);
    exit(0);
  }
 
  /** 绑定套接字与本地地址 */ 
  if((err = bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))) < 0 )
  {
    fprintf(stderr, "bind fail. errno [%d]\n", err);
    exit(0);
  }

  /** 监听端口 */
  if((err = listen(listenfd, LISTENQ)) < 0)
  {
    fprintf(stderr, "listen fail. error [%d]\n", err);
    exit(0);
  }

  return listenfd;
}

int main()
{
  int listenfd = init_server("127.0.0.1",  6666);
  dispatch_thread dispatch;
  dispatch.start(listenfd);

  return 0;
}
