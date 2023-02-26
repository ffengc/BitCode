
#include "comm.hpp"

// 为了让key更好看，和命令行输出的对应起来
// 写一个转换成16进制的函数
std::string TransToHex(key_t k)
{
    char buffer[32];
    snprintf(buffer, sizeof buffer, "0x%x", k);
    return buffer;
}

int main()
{
    // 1.创建公共的key值
    key_t k = ftok(PATH_NAME, PROJ_ID);
    assert(k != -1);
    Log("create key done", Debug) << " server key: " << TransToHex(k) << std::endl;

    // 2.创建共享内存 -- 建议创建一个全新的共享内存 -- Server是通信的发起者
    int shmid = shmget(k, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1)
    {
        // 创建失败
        perror("shmget");
        exit(1);
    }
    Log("create shm done", Debug) << " shmid: " << shmid << std::endl;

    //3.将制定的共享内存，挂接到自己的地址空间
    sleep(3);
    char* shmaddr = (char*)shmat(shmid,nullptr,0);
    Log("attach shm done", Debug) << " shmid: " << shmid << std::endl;
    sleep(3);
    //我们会看到 挂接数会从0变成1！

    // ================= 这里面就是通信的逻辑了！================= //
    //...

    // ================= 这里面就是通信的逻辑了！================= //

    //4.解除挂接
    //  将制定的共享内存，从自己的地址空间中去关联
    int n = shmdt(shmaddr);
    assert(n!=-1);
    (void)n;
    Log("detach shm done", Debug) << " shmid: " << shmid << std::endl;
    sleep(3);


    // last. 删除共享内存
    //IPC_RMID表示，即便是有进程和当下的shm挂接，依旧删除共享内存
    int n = shmctl(shmid, IPC_RMID, nullptr);
    assert(n != -1);
    (void)n;
    Log("delete shm done", Debug) << " shmid: " << shmid << std::endl;
    return 0;
}
