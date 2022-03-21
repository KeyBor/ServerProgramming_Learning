/*

#include <unistd.h>
int pipe(int pipefd[2]);
    功能：创建一个匿名管道，用来进行进程间通讯
    参数：int pipefd[2] 这个数组是一个传出参数
            pipefd[0]:对应管道的读端
            pipefd[1]:对应管道的写端
    返回值:
        成功 0 ,失败 -1(设置errno)

    注意:匿名管道只能用于具有关系的进程之间的通信(父子进程,兄弟进程)
        因为当父进程创建子进程时,其内核区的文件描述符表都是共享的,复制的

    管道默认是阻塞的:如果管道中没有数据,read阻塞,如果管道满了,write阻塞
*/


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

//子进程发送数据给父进程,父进程读取到数据输出
int main(){
    //在fork之间创建管道

    int count =0;
    int pipefd[2];
    //创建管道
    int ret = pipe(pipefd);
    if(ret == -1){
        perror("pipe");
        exit(0);
    }

    //创建子进程
    pid_t pid = fork();
    if(pid > 0){
        //对应的父进程,从管道的读端读取数据
        printf("i am parent process,pid :%d\n",getpid());
        char buf[1024] = {0};
        char sendBuf[100] = "Hello,i am parent";
        while(1){
            int len = read(pipefd[0],buf,sizeof(buf));
            printf("parent recv: %s, pid : %d\n",buf,getpid());

            write(pipefd[1],sendBuf,sizeof(sendBuf));
            sleep(1);
        }


    }else if(pid == 0){
        printf("i am child process,pid :%d\n",getpid());
        char resBuf[1024] = {0};
        char writeBuf[1024] = "Hello,i am child";
        char numWord[10];
        char Buf[100] = {0};
        while(1){
            //对应子进程是0
            //为每一次循环的不同,拼接字符串,传送给父进程
            sprintf(numWord,"%d",count);
            sprintf(resBuf,"%s %s",writeBuf,numWord);
            write(pipefd[1],resBuf,sizeof(resBuf));
            count++;
            sleep(1);
            int len = read(pipefd[0],Buf,sizeof(Buf));
            printf("child recv: %s, pid : %d\n",Buf,getpid());
            bzero(Buf,1024);
            
        }
        
    }

return 0;

}