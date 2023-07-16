
#ifndef __Yufc__TcpServer
#define __Yufc__TcpServer

#include "Sock.hpp"
#include <functional>
#include <pthread.h>
#include <vector>

namespace yufc_tcpServer
{

    using func_t = std::function<void(int)>;

    class TcpServer;

    /* ThreadData 当结构体用就行了 */
    class ThreadData
    {
    public:
        ThreadData(int sock, TcpServer *server)
            : __sock(sock), __this_server(server)
        {
        }
        ~ThreadData() {}

    public:
        int __sock;
        TcpServer *__this_server;
    };

    class TcpServer
    {
    private:
        Sock __sock;
        std::vector<func_t> __func;
        /* 可以改进的地方, 可以用哈希把要执行任务的名字也存一存 */
        int __listen_sock;

    private:
        static void *ThreadRoutine(void *args)
        {
            pthread_detach(pthread_self()); // 因为后面主线程不再管新线程，所以分离
            ThreadData *td = static_cast<ThreadData *>(args);
            td->__this_server->Excute(td->__sock);
            close(td->__sock);
            delete td;
            return nullptr;
        }

    public:
        TcpServer(const uint16_t &port, const std::string &ip = "0.0.0.0")
        {
            __listen_sock = __sock.Socket();
            __sock.Bind(__listen_sock, port, ip);
            __sock.Listen(__listen_sock);
        }
        ~TcpServer()
        {
            if (__listen_sock >= 0)
                close(__listen_sock);
        }
        /* BindService 给TCP服务器绑定一个服务 */
        void BindService(func_t func) { __func.push_back(func); }
        /* Excute 让线程去执行了指定的任务 */
        void Excute(int sock)
        {
            //执行所有的任务
            for(const auto& f :__func)
            {
                f(sock);
            }
        }
        void Start()
        {
            for (;;)
            {
                std::string client_ip;
                uint16_t client_port;
                int sock = __sock.Accept(__listen_sock, &client_ip, &client_port);
                if (sock == -1)
                    continue;
                logMessage(NORMAL, "create new link success, sock: %d", sock);
                pthread_t tid;
                ThreadData *td = new ThreadData(sock, this);
                pthread_create(&tid, nullptr, ThreadRoutine, td);
            }
        }
    };
}
#endif