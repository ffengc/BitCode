

#include "threadPool.hpp"
#include <iostream>
#include "Task.hpp"
#include <time.h>
#include <stdlib.h>
#include "Log.hpp"

#define __LOG_TEST__ false
#define __Singleton_Mode true

#if __LOG_TEST__
int main()
{
    // 这种风格的log风格
    logMessage(NORMAL, "%s %d %c %f\n", "这是一条日志信息", 1234, 'c', 3.14);
    return 0;
}
#elif !__LOG_TEST__
int main()
{
    srand((uint64_t)time(nullptr) ^ getpid() ^ 1214);
    // std::cout << "hello thread pool" << std::endl;
    #if __Singleton_Mode
    //单例模式
    ThreadPool<Task> *tp = ThreadPool<Task>::getThreadPool();
    //那么如果单例本身也在被多线程申请使用呢？
    #else
    ThreadPool<Task> *tp = new ThreadPool<Task>();
    #endif
    tp->run();
    while (true)
    {
        // 生产的过程
        // 制作任务的时候是要花时间的
        int x = rand() % 100 + 1;
        usleep(1231);
        int y = rand() % 30 + 1;
        Task t(x, y, [](int x, int y) -> int
               { return x + y; });
        // std::cout << "制作任务完成: " << x << "+" << y << "=?" << std::endl;
        logMessage(NORMAL, "任务制作完成: %d + %d =? \n", x, y);
        // 推送任务到线程池中
        tp->pushTask(t);
        sleep(1);
    }
    return 0;
}
#endif
