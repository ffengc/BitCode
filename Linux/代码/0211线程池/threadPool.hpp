

/*
    0211 这部分的线程池代码对比 0208的版本 -- 改成了单例模式
    懒汉方式实现
*/

#pragma once
#include <vector>
#include "thread.hpp"
#include <string>
#include <queue>
#include "lockGuard.hpp"
#include "Log.hpp"

#define _DEBUG_MODE_ false
const int g_thread_num = 3; // 默认3个线程

// 线程池本质就是一个生产者消费者模型
template <class T>
class ThreadPool
{
private:
    std::vector<Thread *> __threads;
    int __num;
    std::queue<T> __task_queue;
    pthread_mutex_t __lock;
    pthread_cond_t __cond;
    static ThreadPool<T> *thread_ptr; // 单例模式
    static pthread_mutex_t __mutexForPool;
private:
    //构造放成私有的
    ThreadPool(int thread_num = g_thread_num)
        : __num(thread_num)
    {
        pthread_mutex_init(&__lock, nullptr);
        pthread_cond_init(&__cond, nullptr);
        for (int i = 1; i <= __num; i++)
        {
            __threads.push_back(new Thread(i, routine /*线程要去干的事情*/, this /*这里可以传this, 作为Thread的args*/));
        }
    }
    ThreadPool(const ThreadPool<T>& other) = delete;
    const ThreadPool<T>& operator=(const ThreadPool<T>& other) = delete;
public:
    ~ThreadPool()
    {
        for (auto &iter : __threads)
        {
            // iter->join(); // 这个线程把自己join()一下
            delete iter;
        }
        pthread_mutex_destroy(&__lock);
        pthread_cond_destroy(&__cond);
    }
public:
    //如果有多个线程去调用getThreadPool呢
    static ThreadPool<T>* getThreadPool(int num = g_thread_num)
    {
        if(nullptr == thread_ptr) // 拦截大量再已经创建好单例的时候，剩余线程请求单例而直接访问锁的行为
        {
            lockGuard lockguard_pool(&__mutexForPool);
            // 但是，未来任何一个线程想获取单例，都必须调用getThreadPool接口
            // 这样就会存在大量申请和释放锁的行为，这个是个无用且浪费资源的
            // 因为只有第一次跑的时候，这里是线程不安全的，从第二次开始，这里就是线程安全的了
            // 所以在这个代码块外，再套一层判断！虽然看起来很奇怪，但是是正确的！
            if(nullptr == thread_ptr) // 这里判断，new，是线程不安全的！所以，getThreadPool要加锁！
            {
                //说明对象没有创建，即现在没有线程池对象
                thread_ptr = new ThreadPool<T>(num);
            }
            //因为thread_ptr是一个静态指针，第二次进来的时候，thread_ptr肯定不是nullptr了
        }
        return thread_ptr;
    }
    void run()
    {
        for (auto &iter : __threads)
        {
            iter->start();
            logMessage(NORMAL, "%s %s", iter->name().c_str(), "启动信息");
        }
    }
// for debugs
#if _DEBUG_MODE_
    void joins()
    {
        for (auto &iter : __threads)
        {
            iter->join(); // 这个线程把自己join()一下
        }
    }
    void show()
    {
        std::cout << "可以传入this, 让使用静态方法的线程, 使用到线程池内部的方法" << std::endl;
    }
#endif
    void pushTask(const T &task)
    {
        lockGuard lockguard(&__lock); // 加锁
        // 向任务队列里面push
        __task_queue.push(task);
        // 在push的时候，我们必须保证安全，所以必须加锁
        pthread_cond_signal(&__cond);
    }
    static void *routine(void *args) // 如果不加static, 是会出问题了
    {
        // routine 本质就是消费过程
        /*以为这个函数要求是一个参数args, 如果不加static 就会有两个参数, 会有this指针
            就会可能出现类型不匹配的问题*/
        ThreadData *td = (ThreadData *)args;
        ThreadPool<T> *tp = (ThreadPool<T> *)td->__args;
        // 通过这种方式，就可以让static方法调用类内的一些非static属性了！
        while (true)
        {
            // 1. lock
            // 2. while看看条件变量是否符合（队列有没有任务）如果不符合，等着
            // 3. 拿到任务
            // 4. unlock
            // 5. 处理任务
            T task;
            {
                // 在这个代码块中，线程是安全的
                // 这里用个代码块，lockGuard直接就帮我们解锁了
                lockGuard lockguard(tp->getMutex());
                while (tp->isEmpty())
                    tp->waitCond();
                // 读取任务
                task = tp->getTask(); // 任务队列是共享的
                // 解锁了
            }
            task(td->__name); // 处理这个任务
        }
    }
public:
    // 需要一批，外部成员访问内部属性的接口提供给static的routine，不然routine里面没法加锁
    // 下面这些接口，都是没有加锁的，因为我们认为，这些函数被调用的时候，都是在安全的上下文中被调用的
    // 因为这些函数调用之前，已经加锁了，调用完，lockGuard自动解锁
    pthread_mutex_t *getMutex()
    {
        return &__lock;
    }
    void waitCond()
    {
        pthread_cond_wait(&__cond, &__lock); // 记得把锁也传过去
    }
    bool isEmpty()
    {
        return __task_queue.empty();
    }
    T getTask()
    {
        T t = __task_queue.front();
        __task_queue.pop();
        return t;
    }
};

template <typename T>
ThreadPool<T> *ThreadPool<T>::thread_ptr = nullptr;
template <typename T>
pthread_mutex_t ThreadPool<T>::__mutexForPool = PTHREAD_MUTEX_INITIALIZER;
//static/全局可以这样初始化，这把锁是用来保护getThreadPool的xs
