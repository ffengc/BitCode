

#ifndef _SEM_HPP_
#define _SEM_HPP_

#include <iostream>
#include <semaphore.h>

class Sem
{
private:
    sem_t __sem;

public:
    Sem(int value)
    {
        sem_init(&__sem, 0, value); // value 表示信号量初始化的数值
    }
    ~Sem()
    {
        sem_destroy(&__sem);
    }
    void p()
    {
        //sem_wait/sem_trywait/sem_timedwait
        sem_wait(&__sem);
    }
    void v()
    {
        //post
        sem_post(&__sem);
    }
};

#endif
