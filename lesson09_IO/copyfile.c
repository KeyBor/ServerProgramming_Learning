/*
#include <unistd.h>

//读文件
ssize_t read(int fd, void *buf, size_t count);
    参数:
        fd: 文件描述符,open得到的,通过这个文件描述符操作某个文件
        buf: 要存放数据的地方,数组的首地址
        count: 指定的数组的大小
    返回值:
        成功: 
            >0:返回实际的读取到的字节数
            =0:文件已经读取完了
        失败:
            返回-1,并且设置errno

//写文件
ssize_t write(int fd, const void *buf, size_t count);
    参数:
        fd: 文件描述符,open得到的,通过这个文件描述符操作某个文件
        buf: 要写入的数据,数组的首地址
        count: 要写的数据的实际大小
    返回值:
        成功: 
            >0:返回实际的要写入的字节数
        失败:
            返回-1,并且设置errno
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    //1、通过open函数打开需要拷贝的文件
    int srcfd = open("./copy.txt",O_RDONLY);
    if(srcfd == -1){
        perror("open");
        return -1;
    }
    //2、创建一个新的文件
    int dstfd = open("./cpy.txt",O_WRONLY | O_CREAT,0664);
    if(dstfd == -1){
        perror("open");
        return -1;
    }
    //3、将需要拷贝的文件内容读出写入新的文件中
    char buf[1024] = {0};
    int readlen =0;
    do
    {   
        readlen = read(srcfd,buf,sizeof(buf));
        write(dstfd,buf,readlen);
    } while (readlen > 0);
    
    

    //4、关闭文件
    close(srcfd);
    close(dstfd);


    return 0;
}