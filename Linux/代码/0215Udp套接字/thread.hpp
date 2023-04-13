
#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <unistd.h>

// typedef std::function<void* (void *)> func_t;
typedef void*(*func_t_)(void*); // 函数指针


class ThreadData
{
public:
    void* __args;
    std::string __name;
};

class Thread
{
private:
    std::string __name; // 线程名字
    pthread_t __tid;    // 线程tid
    func_t_ __func;      // 线程要调用的函数
    ThreadData __tdata; // 线程数据
public:
    Thread(int num, func_t_ callback, void* args)
        :__func(callback)
    {
        char nameBuffer[64] = {0};
        snprintf(nameBuffer, sizeof nameBuffer, "Thread-%d", num);
        __name = nameBuffer;

        __tdata.__args = args;
        __tdata.__name = __name;
    }
    ~Thread()
    {}
    void start()
    {
        //线程启动
        pthread_create(&__tid, nullptr, __func, &__tdata);
    }
    void join()
    {
        pthread_join(__tid, nullptr);
    }
    std::string name()
    {
        //返回线程的名字
        return __name;
    }
};
