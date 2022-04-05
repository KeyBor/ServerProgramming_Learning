/*
    SIGCHLD信号产生的3个条件：
        1.子进程结束
        2.子进程暂停了
        3.子进程继续运行
        都会给父进程发送该信号，父进程默认忽略该信号。
    
    使用SIGCHLD信号解决僵尸进程的问题。
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void myFun(int num) {
    printf("捕捉到的信号 ：%d\n", num);
    // 回收子进程PCB的资源
    // while(1) {
    //     wait(NULL); 
    // }
    while(1) {
       int ret = waitpid(-1, NULL, WNOHANG);
       //当有任意的子进程死亡，waitpid捕获到，就会返回死亡的该进程的进程号
       //与此同时，有别的子进程存活，并无关系
       if(ret > 0) {
           printf("child die , pid = %d\n", ret);
        //当没有子进程的状态发生改变，都存活，那么返回0
        //其实根据官方文档的说明，这个地方应该是你指定的一个或多个进程的状态都没有发生改变，那么返回0
        //而-1代表的是任意子进程，当任意子进程的状态没有发生改变时，即存活，返回0；当有一个子进程死亡，别的还存活时，返回死亡的子进程的进程号
       } else if(ret == 0) {
           // 说明还有子进程或者
           break;
       } else if(ret == -1) {
           // 错误
           break;
       }
    }
}

int main() {

    // 提前设置好阻塞信号集，阻塞SIGCHLD，因为有可能子进程很快结束，父进程还没有注册完信号捕捉
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    // 创建一些子进程
    pid_t pid;
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程

        // 捕捉子进程死亡时发送的SIGCHLD信号
        struct sigaction act;
        act.sa_flags = SA_RESTART;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);

        // 注册完信号捕捉以后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1) {
            printf("parent process pid : %d\n", getpid());
            int ret = waitpid(-1, NULL, WNOHANG);
            printf("%d",ret);
            sleep(2);
        }
    } else if( pid == 0) {
        // 子进程
        printf("child process pid : %d\n", getpid());
        while(1);
    }

    return 0;
}