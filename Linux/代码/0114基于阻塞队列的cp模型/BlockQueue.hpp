

#pragma once

#include <iostream>
#include <queue>
#include <pthread.h>
#include "lockGuard.hpp"

// std::queue是线程安全的吗？
// 不是

const int gDefaultCap = 5; // 默认容量

template <class T>
class BlockQueue
{
private:
    std::queue<T> __bq;
    size_t __capacity;      // 容量上限
    pthread_mutex_t __mtx;  // 通过互斥锁保证队列安全
    pthread_cond_t __Empty; // 用它来表示bq是否空的条件
    pthread_cond_t __Full;  // 用它来表示bq是否满的条件
private:
    bool __isQueueEmpty()
    {
        return this->__bq.size() == 0;
    }
    bool __isQueueFull()
    {
        return __bq.size() == this->__capacity;
    }

public:
    BlockQueue(size_t capacity = gDefaultCap)
        : __capacity(capacity)
    {
        pthread_mutex_init(&__mtx, nullptr);
        pthread_cond_init(&__Empty, nullptr);
        pthread_cond_init(&__Full, nullptr);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&__mtx);
        pthread_cond_destroy(&__Empty);
        pthread_cond_destroy(&__Full);
    }

public:
    void push(const T &in) // 生产者
    {
#if 0
        pthread_mutex_lock(&__mtx); // 加锁
        // 1. 先检测当前的临界资源是否能够访问条件
        // 注意!
        // 此时真的没有问题吗？
        // pthread_cond_wait(): 我们现在是在临界区中的！我们持有锁！如果我去等待了，锁怎么办？！
        // pthread_cond_wait第二个参数是一把锁，意义在于：
        // 当成功调用wait之后，传入的锁会被自动释放！
        // 这就是pthread_cond_wait第二个参数的意义！
        // 如果我被唤醒时：我从哪里醒来呢？？从哪里阻塞挂起，就从哪里唤醒（我们先保留，等等再解释）
        // 我们醒来的时候，是在临界资源中唤醒的！
        // 此时，pthread_cond_wait, 会自动帮助我们先层获取锁(这些动作都是原子的，不用我们操心)
        // 但是，谁来唤醒呢？生产者的唤醒是由消费者做的！消费者给bq腾出位置，生产者就能生产了！
        while(this->__isQueueFull())
        {
            // 此时满了！生产者应该等待！
            pthread_cond_wait(&__Full, &__mtx); //首先这里是一个函数，它有可能调用失败！
        }
        // 2. 访问临界资源
        __bq.push(in);
        if (__bq.size() >= __capacity / 2)
            pthread_cond_signal(&__Empty); // 唤醒消费者
        pthread_mutex_unlock(&__mtx);      // 解锁
#endif
        //我们用lockGuard改装一下代码
        lockGuard lockguard(&__mtx); // 自动调用构造
        while(this->__isQueueFull())
        {
            pthread_cond_wait(&__Full, &__mtx);
        }
        __bq.push(in);
        if (__bq.size() >= __capacity / 2)
            pthread_cond_signal(&__Empty);
        // pthread_mutex_unlock(&__mtx);  // 不再需要解锁！
        // 这里lockGuard的析构
    }
    void pop(T *out)
    {
        lockGuard lockguard(&__mtx);
        // pthread_mutex_lock(&__mtx);
        while (__isQueueEmpty())
        {
            pthread_cond_wait(&__Empty, &__mtx);
        }
        *out = __bq.front();
        __bq.pop();
        pthread_cond_signal(&__Full);
        // pthread_mutex_unlock(&__mtx); // 不用自己解锁了
    }
};
