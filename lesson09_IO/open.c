/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//打开一个已经存在的文件
int open(const char *pathname,int flags);
    参数：
        pathname：要打开的文件路径
        flags：对文件的操作权限设置，还有一些其他的设置 
        O_RDONLY,O_WRONLY,O_RDWR,这三个设置是互斥的
    返回值：返回一个新的文件描述符，如果调用失败，返回-1


// errno:属于Linux系统函数库的一个全局变量，记录的是最近的错误号

#inlcude <stdio.h>
void perror(const char *s);
作用：打印errno的错误描述
参数： s：用户描述，对于错误的具体描述

//创建一个新的文件
int open(const char *pathname,int flags,mode_t mode);
    参数：
        pathname：要打开的文件路径
        必选项：O_RDONLY,O_WRONLY,O_RDWR,这三个设置是互斥的
        可选项：O_CREATE 文件不存在，创建新的文件
        mode：八进制的数，表示创建出的新的文件的操作权限，如：0775，rwx，每个用0，1表示，三位全为1时，值为7，三组代表不同的用户组
        最终的权限是： mode & ~umask 
                               mode = 0777 = 111111111
        umask = 0002 = 000000010 -> ~umask = 111111101
        mode & ~umask = 111111101
        ~umask其实就是为了抹去某些用户组的权限，毕竟也是12位二进制，代表3个组的3个权限
    返回值：返回一个新的文件描述符，如果调用失败，返回-1
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    //打开一个文件
    int fd = open("a.txt",O_RDONLY);
    if(fd == -1){
        perror("open");
    }

    //close the file descriptor
    close(fd);
    
    return 0;
}
