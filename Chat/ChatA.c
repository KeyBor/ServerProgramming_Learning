#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
   //首先创建两个fifo,分别用于读和写
   //首先判断FIFO是否存在，若不存在则创建
    int ExistFlag = access("fifo1",F_OK);
    if(ExistFlag == -1){
        int ret  = mkfifo("fifo1",0664);
        //fifo1创建失败
        if(ret == -1){
            perror("mkfifo");
            exit(0);
            }
    }
    ExistFlag = access("fifo2",F_OK);
    if(ExistFlag == -1){
        int ret = mkfifo("fifo2",0664);
        //fifo2创建失败
        if(ret == -1){
            perror("mkfifo");
            exit(0);
            }
    }

    //创建父子进程,分别控制读和写,防止阻塞
    pid_t pid = 0 ;
    pid = fork();
    //父进程代码逻辑,负责写
    if(pid > 0 ){
        //存在则打开FIFO,设置只写
        int fdw = open("fifo1",O_WRONLY);
        //打开失败
        if(fdw == -1){
            perror("open");
            exit(0);
        }
        char buf[1024] = {0};
        //使用fgets获取stdin的输入,保存进buf写入fifo的写端
        while(1){
            fgets(buf,1024,stdin);
            int len = write(fdw,buf,sizeof(buf));
            if(len == -1){
                perror("write");
                exit(0);
            }
            bzero(buf,sizeof(buf));
        }
    }
    //子进程代码逻辑,负责读
    else if(pid == 0){
         //存在则打开FIFO,设置只读
        int fdr = open("fifo2",O_RDONLY);
        //打开失败
        if(fdr == -1){
            perror("open");
            exit(0);
        }
        char buf[1024] = {0};
        while(1){
            int len = read(fdr,buf,sizeof(buf));
            if(len <= 0){
                perror("read");
                exit(0);
            }
            printf("child_pid recv: %s\n",buf);
        }
    }
    perror("fork");
    exit(0);
   
    return 0;
}