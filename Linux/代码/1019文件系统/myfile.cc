

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

#if fasle
int main()
{
    close(1);
    int fd = open("log.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(fd<0)
    {
        perror("open");
        return 0;
    }

    printf("hello world: %d\n", fd); //stdout -> 1 -> log.txt -> 缓冲区

    // const char* msg = "hello world\n";
    // write(fd, msg, strlen(msg));

    close(fd);
    return 0;
}
#endif


//标准错误演示
int main()
{
    //C
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    perror("hello perror");//stderr
    //系统调用
    const char* s1 = "hello write 1\n";
    write(1,s1,strlen(s1));
    const char* s2 = "hello write 2\n";
    write(2,s2,strlen(s2));
    //C++
    std::cout<<"hello cout"<<std::endl;
    std::cerr<<"hello cerr"<<std::endl;
    return 0;
}
