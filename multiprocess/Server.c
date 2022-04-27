//TCP通信的服务器端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

void recyleChild(int arg){
    while(1){
        int ret = waitpid(-1,NULL,WNOHANG);
        if(ret == -1){
            //所有子进程都被回收了
            break;
        }else if(ret == 0){
            //还有子进程存活
            break;
        }else if(ret >0){
            //被回收了
            printf("子进程%d被回收了\n", ret);
        }
    }
}

int main(){

    struct sigaction act;
    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    //注册信号捕捉
    sigaction(SIGCHLD,&act,NULL);


    //1、创建socket 用于监听的套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd == -1){
        perror("socket");
        exit(-1);
    }
    //2、绑定端口和ip
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;

    // inet_pton(AF_INET,"0.0.0.0",saddr.sin_addr.s_addr);
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    int ret = bind(listenfd,(struct sockaddr *)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }
    printf("start listen!\n");
    //3、监听端口
    ret = listen(listenfd,8);
    printf("listen!\n");
    if(ret == -1){
        perror("listen");
        exit(-1);
    }
    
    while(1){
        //4、建立连接
        struct sockaddr_in caddr;
        socklen_t len =sizeof(caddr);
        int acceptfd = accept(listenfd,(struct sockaddr *)&caddr,&len);
        if(acceptfd == -1){
            perror("accept");
            exit(-1);
        }
        printf("accept!\n");

        pid_t pid = fork();
        if(pid == 0){
            //子进程
             //输出客户端的信息
            char clientIP [16];
            inet_ntop(AF_INET,&caddr.sin_addr.s_addr,clientIP,sizeof(clientIP));
            unsigned short clientPort = ntohs(caddr.sin_port);
            printf("client ip is %s,port is %d\n",clientIP,clientPort);

            //5.通信
            //获取客户端的数据
            char recvBuf[1024] ={0};
            while(1){
                int clen = read(acceptfd,recvBuf,sizeof(recvBuf));
                if(clen == -1){
                    perror("read");
                    exit(-1);
                }else if(len > 0){
                    printf("recv client data:%s\n",recvBuf);
                }else{
                    printf("client closed...");
                    break;
                }
                //给客户端发送数据
                char* data = "hello, i am server!";
                write(acceptfd,data,strlen(data)+1);
            }
            close(acceptfd);
            exit(0);
        }

    }
    //关闭文件描述
    close(listenfd);
    
   
   
    

}