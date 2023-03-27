
#ifndef _Ring_Queue_HPP_
#define _Ring_Queue_HPP_

#include <iostream>
#include <vector>
#include <pthread.h>
#include "sem.hpp"

const int g_default_num = 5;

template <class T>
class RingQueue
{
private:
    std::vector<T> __ring_queue;
    size_t __size;
    int __c_step;    // 消费者下标
    int __p_step;    // 生产者下标
    Sem __space_sem; // 空间资源信号量
    Sem __data_sem;  // 数据资源信号量
    pthread_mutex_t __c_lock; // 其实我们也可以对锁进行封装，这里就不弄了
    pthread_mutex_t __p_lock; 
public:
    RingQueue(int default_num = g_default_num)
        : __ring_queue(default_num), __size(default_num)
        , __c_step(0), __p_step(0), __space_sem(default_num), __data_sem(0)
    {
        pthread_mutex_init(&__c_lock, nullptr);
        pthread_mutex_init(&__p_lock, nullptr);
    }
    ~RingQueue()
    {
        pthread_mutex_destroy(&__c_lock);
        pthread_mutex_destroy(&__p_lock);
    }
    void push(const T &in)
    {
        // 生产者
        // 关心的是空间资源
        // 必须先预定空间
        __space_sem.p(); // 空间资源少一个
        pthread_mutex_lock(&__p_lock); // ?
        // 走到这里的一定是竞争锁成功的生产者线程
        __ring_queue[__p_step++] = in;
        __p_step %= __size;
        pthread_mutex_unlock(&__p_lock);
        __data_sem.v(); // 数据资源多一个
    }
    void pop(T *out)
    {
        // 消费者
        // 关心的是数据资源
        __data_sem.p();
        pthread_mutex_lock(&__c_lock);
        *out = __ring_queue[__c_step++];
        __c_step %= __size;
        pthread_mutex_unlock(&__c_lock);
        __space_sem.v();
    }
    void debug()
    {
        std::cerr << "queue size: " << __ring_queue.size() << "  "
                  << "size: " << __size << std::endl;
    }
};



#endif
