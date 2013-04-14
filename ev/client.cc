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

int port = 6666;
char* server = "127.0.0.1";

void* send_data(void* args)
{
    int                          ret;      /* 临时变量  */  
    int                          sockfd;    /* socket 描述符 */  
    struct sockaddr_in           servaddr;  /* 套接字  */  
  
    /* 获得 socket 描述符 */  
    sockfd= socket( AF_INET, SOCK_STREAM, 0 );  
    if(sockfd== -1){  
        return 0;  
    }  
    /* 初始化 socket 为零 */  
    bzero( &servaddr, sizeof(servaddr) );  
    /* 设置协议 */  
    servaddr.sin_family = AF_INET;  
    /* 设置端口 */  
    servaddr.sin_port =  htons( port );  
  
    /* 设置服务端 IP */  
    ret = inet_pton(AF_INET, server, &servaddr.sin_addr);  
    if(ret== -1){  
        return 0;  
    }  
    /* 连接服务端 */  
    if((ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1)
    {
        fprintf(stderr, "error");
        return 0;
    }
    char data[1024];
    sprintf(data, "data in clientthread[%d]", pthread_self());
    /** 写入数据 */
    while( (ret= write(sockfd, data, strlen(data))) < 0);
}

#define N 20 

int main(int argc, char** argv)
{
    pthread_t thid[N];
    for(int i = 0; i < N; ++i)
    {
        pthread_create(thid + i, NULL, send_data, NULL);
    }
    for(int i = 0; i < N; ++i)
    {
        pthread_join(thid[i], NULL);
    }
    return 0;
}
