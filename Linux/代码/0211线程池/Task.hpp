

#pragma once

#include <iostream>
#include <functional>

typedef std::function<int(int, int)> func_t;

class Task
{
public:
    int __x;
    int __y;
    func_t __func;
public:
    Task() {}
    Task(int x, int y, func_t func)
        : __x(x), __y(y), __func(func)
    {
    }
    void operator()(const std::string &name)
    {
        // std::cout << "thread: " << name << "处理完成, 结果是: " << __func(__x, __y) << std::endl;
        logMessage(NORMAL, "线程: %s,处理结果是: %d\n", name.c_str(), __func(__x, __y));
    }
};
