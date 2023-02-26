
#include "comm.hpp"

int main()
{
    key_t k = ftok(PATH_NAME, PROJ_ID);
    if(k<0)
    {
        Log("create key failed", Error) << " client key: " << k << std::endl;
        exit(1);
    }
    Log("create key done", Debug) << " client key: " << k << std::endl;
    //获取共享内存
    int shmid = shmget(k,SHM_SIZE,IPC_CREAT);
    if(shmid<0)
    {
        Log("create shm success", Error) << " client key: " << k << std::endl;
        exit(2);
    }
    Log("create shm failed", Debug) << " client key: " << k << std::endl;
    sleep(5);
    //
    char* shmaddr = (char*)shmat(shmid,nullptr,0);
    if(shmaddr ==nullptr)
    {
        Log("attach shm failed", Error) << " client key: " << k << std::endl;
        exit(3);
    }
    Log("attach shm success", Debug) << " client key: " << k << std::endl;
    sleep(5);


    //使用


    //去关联
    int n = shmdt(shmaddr);
    assert(n!=-1);
    Log("detach shm success", Debug) << " client key: " << k << std::endl;
    sleep(5);

    //client要不要chmctl删除呢？不需要！！！
    
    return 0;
}
