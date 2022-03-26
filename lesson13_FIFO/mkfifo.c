/*

    创建fifo文件
    1. 通过命令 mkfifo 名字
    2、通过函数 
        #include <sys/types.h>
        #include <sys/stat.h>
        int mkfifo(const char *pathname, mode_t mode);
        参数：
            pathname：有名管道文件的路径
            mode： 文件的权限
        返回值：
            成功返回0，失败返回-1，并设置错误号


*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    //判断文件是否存在，使用access的系统调用
    int existsFlag = access("fifo1",F_OK);
    if (existsFlag == 0){
        printf("管道已经存在,不需要重复创建!\n");
        return 0;
    }
    printf("管道不存在,正在创建管道!\n");
    int ret = mkfifo("fifo1",0664);
    if(ret == -1){
        perror("mkfifo");
        exit(0);
    }
    printf("创建成功!\n");


}