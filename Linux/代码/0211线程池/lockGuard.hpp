
#pragma once

#include <iostream>
#include <pthread.h>


//封装一个锁
class Mutex
{
private:
    pthread_mutex_t *__pmtx;
public:
    Mutex(pthread_mutex_t *mtx)
        :__pmtx(mtx){}
    ~Mutex()
    {}
public:
    void lock()
    {
        pthread_mutex_lock(__pmtx);
    }
    void unlock()
    {
        pthread_mutex_unlock(__pmtx);
    }
};

class lockGuard
{
public:
    lockGuard(pthread_mutex_t *mtx)
        :__mtx(mtx)
    {
        __mtx.lock();
    }
    ~lockGuard()
    {
        __mtx.unlock();
    }
private:
    Mutex __mtx;
};
