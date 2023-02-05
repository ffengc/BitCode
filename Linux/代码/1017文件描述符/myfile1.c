

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


//缓冲区在哪？
int main()
{
    //C语言
    printf("hello printf\n");
    fprintf(stdout,"hello fprintf\n");
    const char* s = "hello fputs\n";
    fputs(s,stdout);

    //系统
    const char *ss = "hello write\n";
    write(1,ss,strlen(ss));

    //在最后调用的fork -- 上面的函数已经被执行完了
    fork(); //创建子进程

    return 0;
}
