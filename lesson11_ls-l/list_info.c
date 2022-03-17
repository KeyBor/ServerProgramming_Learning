/*
模拟ls -l 命令

-rw-rw-r-- 1 kusola kusola 1481 3月  17 14:05 lseek.c
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

//需要获取命令行参数,所以main函数要设置接受的参数
int main(int args ,char *argv[]){

    //判断命令函接受的参数的个数,小于两个就给出提示
    if(args < 2){
        printf("Error:%s filename\n",argv[0]);
        return -1;
    }

    //通过stat函数获取文件的各种信息
    struct stat filestat;
    //判断是否成功
    int statnum = stat(argv[1],&filestat);
    if(statnum == -1){
        perror("stat");
        return -1;
    }

    //成功之后就从stat结构体中获取我们需要的数据
    //获取文件的类型,获取文件类型需要用st_mode与掩码S_IFMT进行与运算后和文件类型宏进行比较
    char perms[11] = {0}; //用于保存文件权限
    switch (filestat.st_mode & S_IFMT)
    {
        case S_IFREG:
            perms[0] = '-';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFIFO:
            perms[0] = 'p';
            break;
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFSOCK:
            perms[0] = 'p';
            break;
        default:
            perms[0] = '?';
            break;
    }
    //获取当前用户的权限
    perms[1] = (filestat.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (filestat.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (filestat.st_mode & S_IXUSR) ? 'x' : '-';

    // 文件所在组
    perms[4] = (filestat.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (filestat.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (filestat.st_mode & S_IXGRP) ? 'x' : '-';

    // 其他人
    perms[7] = (filestat.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (filestat.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (filestat.st_mode & S_IXOTH) ? 'x' : '-';

    //获取硬链接数
    int linkNum = filestat.st_nlink;
    //获取文件所有者,需要包含pwd.h，使用方法获得结构体指针
    int uid = filestat.st_uid;
    char* fileUser = getpwuid(uid)->pw_name;

    //获取文件所在组
    char* fileGrp = getgrgid(filestat.st_gid) ->gr_name;

    //获取文件大小
    long int fileSize = filestat.st_size;

    //获取修改时间
    long int modiTime = filestat.st_mtim.tv_sec;
    char * time = ctime(&modiTime);
    //默认格式化事件后会有换行符,所以需要进行复制
    char mtime[512] = {0};
    //strcpy和strncpy,strcpy用来复制字符串,strncpy用于复制前n个字符,并且会将剩下的空间全部插入"\0"
    strncpy(mtime, time, strlen(time) - 1);

    //输出,将所有的字符串复制到一个新的buf中输出
    char buf[1024]={0};
    sprintf(buf,"%s %d %s %s %ld %s %s",perms,linkNum,fileUser,fileGrp,fileSize,mtime,argv[1]);

    printf("%s\n",buf);


    return 0;


}