
#pragma once

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void MyDaemon()
{
    // 1. 忽略信号, SIGPIPE, SIGCHLD
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    // 2. 不要让自己成为组长
    if (fork() > 0)
        exit(0);
    // 3. 调用setsid
    setsid();
    // 4. 标准输入，标准输出，标准错误的重定向
    // 守护进程不能向显示器打印消息，一旦打印，进程会被暂停/终止
    int devnull = open("/dev/null", O_RDONLY | O_WRONLY);
    if (devnull > 0)
    {
        dup2(0, devnull); // 重定向
        dup2(1, devnull);
        dup2(2, devnull);
        close(devnull);
    }
}