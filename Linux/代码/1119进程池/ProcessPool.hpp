

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cassert>
#include <vector>
#include <unordered_map>
#include "Task.hpp"


/*
    现在我们写的这个进程池处理的任务是自己定义好的
    如果任务是从网络里面来的呢？

    代码中关于fd的处理，有一个小小的问题，不影响我们的使用，能找到吗？
*/

#define PROCESS_NUM 5 // 我们要创建五个进程

using namespace std;

class ProcessPool
{
public:
    ProcessPool() = default;
    ProcessPool(const ProcessPool&) = delete;
    ProcessPool& operator=(const ProcessPool&) = delete;
    ~ProcessPool() = default;
protected:
    void __showUserOperMenu()
    {
        cout << "-------------------------------" << endl;
        cout << "-   1. show funcitons     -----" << endl;
        cout << "-   2. send funcitons(auto)  --" << endl; // 为了方便调试，让系统自己派发任务
        cout << "-------------------------------" << endl;
        cout << "please select>: " << endl;
    }
    int __waitCommand(int waitFd, bool &quit)
    {
        // 规定这个命令只能是4个字节！
        uint32_t command = 0;
        ssize_t s = read(waitFd, &command, sizeof(command));
        if (s == 0)
        {
            quit = true;
            return -1;
        }
        assert(s == sizeof(uint32_t)); // 如果命令不是4个字节说明发命令发错了
        // 读成功了
        return command;
    }
    void __sendAndWakeUp(pid_t who, int fd, uint32_t command)
    {
        // who: 给哪个子进程发送命令
        // fd: 给这个子进程发送命令的管道的文件描述符
        // command: 发送什么命令
        write(fd, &command, sizeof(command));
        // 可以简单写一写日志
        cout << "call process: " << who << " execute: " << desc[command] << " through: " << fd << endl;
    }
public:
    void StartThePool()
    {
        load();
        // 因为我们要在进程池子里面去选择一个进程去帮我们完成任务
        // 因此我们需要一张表
        vector<pair<pid_t, int>> slots;

        // 创建多个进程
        for (int i = 0; i < PROCESS_NUM; i++)
        {
            // creat pipe
            int pipefd[2] = {0};
            int n = pipe(pipefd);
            assert(n == 0);

            (void)n;
            pid_t id = fork();
            assert(id != -1);
            if (id == 0)
            {
                // child
                // 子进程我们要进行读取
                // 关闭写端
                close(pipefd[1]);
                while (true)
                {
                    // pipefd[0];
                    // 现在子进程就要等待父进程的命令
                    bool quit = false;
                    int command = __waitCommand(pipefd[0], quit); // 如果对方不发命令，我们就阻塞
                    // 如果quit是true --- 直接break
                    if (quit == true)
                        break;
                    // 执行对应的命令
                    if (command >= 0 && command < handlerSize()) // 说明这个命令合法 --- 对应了方法表中的方法
                    {
                        callbacks[command](); // 执行对应的方法
                    }
                    else
                    {
                        cout << "非法command: " << command << endl;
                    }
                }
                exit(1);
            }
            // father,write 关闭读端
            close(pipefd[0]);
            slots.push_back(pair<pid_t, int>(id, pipefd[1]));
        }
        // 通过上面这个循环之后
        // 一个进程池已经创建好了
        // 开始任务
        // 父进程派发任务
        /*
            首先，我们在派发任务的时候，要均衡地给每一个子进程派发任务
            这个叫做单机版的负载均衡 -- 实现它的算法很多，比如rr，随机等
        */

        // 创建一个随机数种子
        srand((unsigned long)time(nullptr) ^ getpid() ^ 2324232); // 这样写只是为了让数据源更随机
        while (true)
        {
            int command = 0;
            int select = 0;
            __showUserOperMenu();
            cin >> select;
            cout << endl;
            if (select == 1)
                showHandler();
            else if (select == 2)
            {
                // 用户要选择任务执行了
                // cout << "Enter Your Command> ";
                // 选择任务
                // cin >> command;
                while (true)
                {
                    // 选择任务（自动）
                    int command = rand() % handlerSize();
                    // 选择进程
                    int choice = rand() % slots.size();
                    // 布置任务，把任务给指定的进程
                    __sendAndWakeUp(slots[choice].first, slots[choice].second, command); // 发送命令，同时把子进程唤醒，让它去干活了
                    sleep(1);
                }
            }
        }

        // 关闭fd，结束所有的进程
        for (const auto &slot : slots)
        {
            close(slot.second); // 我们只需要关闭所有写的fd，所有的子进程都会退出
        }
        // 回收所有的子进程信息
        for (const auto &slot : slots)
        {
            waitpid(slot.first, nullptr, 0); // 等待所有的子进程
        }
    }
};
