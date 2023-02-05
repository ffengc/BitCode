

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


//我们自己设计一下用户层缓冲区
#define NUM 1024

struct MyFILE_
{
    int fd;
    char buffer[NUM];
    int end; //当前缓冲区的结尾
};

typedef struct MyFILE_ MyFILE;

MyFILE* fopen_(const char *pathname, const char* mode)
{
    assert(pathname);
    assert(mode);
    MyFILE* fp = NULL;//如果传入的mode有问题 -- 返回NULL

    if(strcmp(mode,"r") == 0){}
    else if(strcmp(mode,"r+") == 0){}
    else if(strcmp(mode,"w") == 0)
    {

        int fd = open(pathname,O_WRONLY|O_TRUNC|O_CREAT,0666); //封装系统调用
        if(fd >= 0) //成功打开
        {
            fp = (MyFILE*)malloc(sizeof(MyFILE));
            memset(fp,0,sizeof(MyFILE));
            fp->fd = fd;
        }
    }
    else if(strcmp(mode,"w+") == 0){}
    else if(strcmp(mode,"a") == 0){}
    else if(strcmp(mode,"a+") == 0){}
    else
    {
        //什么都不做
        ;
    }
    return fp;
}

void fputs_(const char* message, MyFILE*fp)
{
    assert(message);
    assert(fp);

    //向缓冲区中写入
    strcpy(fp->buffer+fp->end,message);
    fp->end += strlen(message);//把end往后移

    printf("%s\n",fp->buffer);//for debug
    
    //现在暂时没有刷新
    //现在要定义一下刷新策略
    //此时就要分类一下了
    if(fp->fd == 0)
    {
        //标准输入
    }
    else if(fp->fd == 1)
    {
        //标准输出
        if(fp->buffer[fp->end-1] == '\n')//如果有回车 -- 直接刷新
        {
            write(fp->fd, fp->buffer, fp->end);
        }
    }
    else if(fp->fd == 2)
    {
        //标准错误
    }
    else
    {
        //其他文件
    }
}



void fflush_(MyFILE* fp)
{
    assert(fp);
    if(fp->end!=0)
    {
        //暂且认为刷新了 -- 其实是把数据写到内核里面了
        write(fp->fd,fp->buffer,fp->end);
        syncfs(fp->fd); //讲数据写入到文件中（磁盘...）
        fp->end = 0;
    }
}

void fclose_(MyFILE* fp)
{
    assert(fp);
    fflush_(fp);
    close(fp->fd);
    free(fp);
}

int main()
{
    MyFILE* fp = fopen_("./log.txt","w");
    if(fp == NULL)
    {
        printf("fopen_ error");
        return 1;
    }
    //进行一些操作
    fputs_("one: hello world",fp);
    fputs_("    two: hello world",fp);
    fputs_("    three: hello world",fp);
    fputs_("    four: hello world",fp);
    fclose_(fp);
    return 0;
}
