#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    //打开一个文件
    int fd = open("create.txt",O_RDWR | O_CREAT ,0777);
    if(fd == -1){
        perror("open");
    }

    //close the file descriptor
    close(fd);
    
    return 0;
}
