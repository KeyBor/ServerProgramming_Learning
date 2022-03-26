#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    //首先判断FIFO是否存在，若不存在直接爆出异常
    int ExistFlag = access("test",F_OK);
    if(ExistFlag == -1){
        perror("access");
        exit(0);
    }
    char buf[1024] = {0};
    int fd = open("test",O_RDONLY);
    while(1){
        int len = read(fd,buf,sizeof(buf));
        if( len == 0){
            printf("写端关闭，中断通信!\n");
            break;
            }
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
    }
    close(fd);
    return 0;
}