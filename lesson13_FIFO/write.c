#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    //首先判断FIFO是否存在，若不存在则创建
    int ExistFlag = access("test",F_OK);
    if(ExistFlag == -1){
        int ret  = mkfifo("test",0664);
        //fifo创建失败
        if(ret == -1){
            perror("mkfifo");
            exit(0);
            }
    }
    //存在则打开FIFO,设置只写
    int fd = open("test",O_WRONLY);
    //打开失败
    if(fd == -1){
        perror("open");
        exit(0);
    }
    char buf[1024] = {0};
    for(int i=0; i < 5 ; i++){
        sprintf(buf,"Hello,FIFO %d",i);
        int len = write(fd,buf,sizeof(buf));
        bzero(buf,sizeof(buf));
        sleep(1);   
    }

    //关闭文件描述符
    close(fd);
    return 0;
}