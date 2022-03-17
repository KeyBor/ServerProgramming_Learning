/*

#include <sys/types.h>
#include <unistd.h>


off_t lseek(int fd, off_t offset, int whence);
参数:
    fd:文件描述符
    offset: 偏移量
    whence:
    SEEK_SET: The file offset is set to offset bytes.
                设置文件指针的偏移量

    SEEK_CUR: The file offset is set to its current location plus offset bytes.
                设置偏移量: 当前位置 + 第二个参数offset的值

    SEEK_END: The file offset is set to the size of the file plus offset bytes.
                设置偏移量: 文件大小 + 第二个参数offset的值
返回值:
    返回文件指针的位置
作用:
    1.移动文件指针到文件头
    lseek(fd,0,SEEK_SET)

    2.获取当前文件指针的位置
    lseek(fd,0,SEEK_CUR)

    3.获取文件长度
    lseek(fd,0,SEEK_END)

    4.拓展文件的长度,当前文件10B - > 110B ,增加100个字节
    lseek(fd,100,SEEK_END)
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    //1、通过open函数打开需要文件
    int srcfd = open("./hello.txt",O_RDWR);
    if(srcfd == -1){
        perror("open");
        return -1;
    }


    //2、扩展文件长度
    int ret = lseek(srcfd,100,SEEK_END);
    if(ret == -1){
        perror("lseek");
        return -1;
    }

    //3、写入空数据
    int writeres = write(srcfd," ", 1);
    printf("%d",writeres);

    //4、关闭文件
    close(srcfd);

    return 0;
}