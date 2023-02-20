
#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

// typedef std::function<void()> func; //定义函数对象
using func = std::function<void()>;

std::vector<func> callbacks;               // 定义一个容器去存储这些函数对象
std::unordered_map<int, std::string> desc; // 定义这些函数的描述，比如，0代表readMySQL，里面的string就是"访问数据库"

void readMySQL()
{
    std::cout << "process[ " << getpid() << " ] 访问数据库的任务" << std::endl << std::endl;
}

void execuleUrl()
{
    std::cout << "process[ " << getpid() << " ] 执行Url解析" << std::endl << std::endl;
}

void cal()
{
    std::cout << "process[ " << getpid() << " ] 执行加密任务" << std::endl << std::endl;
}

void save()
{
    std::cout << "process[ " << getpid() << " ] 执行数据持久化任务" << std::endl << std::endl;
}

void load()
{
    desc.insert({callbacks.size(), "readMySQL: 访问数据库的任务"});
    callbacks.push_back(readMySQL);

    desc.insert({callbacks.size(), "execuleUrl: 执行Url解析"});
    callbacks.push_back(execuleUrl);

    desc.insert({callbacks.size(), "cal: 执行加密任务"});
    callbacks.push_back(cal);

    desc.insert({callbacks.size(), "save: 执行数据持久化任务"});
    callbacks.push_back(save);
}

void showHandler()
{
    for (const auto &iter : desc)
    {
        std::cout << iter.first << "\t" << iter.second << std::endl;
    }
}

int handlerSize()
{
    return callbacks.size();
}
