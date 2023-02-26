
#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <ctime>

#define Debug 0
#define Notice 1
#define Warning 2
#define Error 3

const std::string msg[] =
    {
        "Debug", "Notice", "Warning", "Error"};

std::ostream &Log(std::string message, int level)
{
    std::cout << " | " << (unsigned)time(nullptr) << " | " << msg[level] << " | " << message;
    return std::cout;
}

#endif
