

#ifndef _UDP_SERVER_HPP
#define _UDP_SERVER_HPP

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "Log.hpp"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <unordered_map>

#define SIZE 1024

class UdpServer
{
private:
    // 一个服务器必须需要ip地址和port(16位的证书)
    std::string _ip;
    uint16_t _port;
    int _sock = -1;
    std::unordered_map<std::string, struct sockaddr_in> _users;

public:
    UdpServer(uint16_t port, std::string ip = "")
        : _port(port), _ip(ip)
    {
    }
    ~UdpServer()
    {
        if (_sock >= 0)
            close(_sock);
    }

public:
    bool initServer()
    {
        // 从这里开始就是新的系统调用，来完成网络功能
        //  1. 创建套接字
        this->_sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sock < 0)
        {
            // 创建套接字失败, 是个致命的错误
            logMessage(FATAL, "%d: %s", errno, strerror(errno));
            exit(2);
        }
        // 2. bind绑定：将用户设置的ip和port在内核中和当前的进程强关联
        // '192.168.1.1' -> 点分十进制风格的ip地址 其实每一个区间都是[0,255]的
        // 所以存储这个理论上4字节就够了
        // 这个点分十进制是给用户看的
        // 所以内部必定存在：点分十进制风格的ip地址 <-> 4字节 的一个转化
        struct sockaddr_in local;
        // 把这个结构体清零一下 -- 用一些新的接口
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET; // 一般就是填socket接口的第一个参数
        // 服务器的ip和端口未来也是要发送对方主机的 -> 先要将数据发送到网络！
        // 所以要考虑大小端问题！所以要调用一下 【主机序列转网络序列】 的接口！
        local.sin_port = htons(_port);
        // 这里也要将字符串风格的
        // 1. ip地址 转化成 4字节的ip地址  2. 主机序列 -> 网络序列
        // 有一套接口可以一次帮我们做完这些事情
        local.sin_addr.s_addr = _ip.empty() ? INADDR_ANY : inet_addr(_ip.c_str());
        // 采用这种方法之后，启动服务器只需要传端口号就行了
        if (bind(_sock, (struct sockaddr *)&local, sizeof local) < 0)
        {
            logMessage(FATAL, "%d: %s", errno, strerror(errno));
            exit(2);
        }
        logMessage(NORMAL, "init udp server done ... %s", strerror(errno));
        // done
        fflush(stdout);
        return true;
    }
    void start()
    {
        // echo server: client给我们发消息，我们原封不动返回就行
        // 作为一款网络服务器，是永远不退出的！ -> 常驻进程，除非挂了
        for (;;)
        {
            // start. 读取数据
            // 分析数据和处理数据
            // end. 写回数据

            // 读取数据
            char buffer[SIZE];
            // 这个len既是输入型参数也是输出型参数
            // 输入: 表示peer缓冲区的大小
            // 输出: 实际读到的peer的大小
            // 注意
            struct sockaddr_in peer; // peer 表示远端
            socklen_t len = sizeof(peer);
            // 注意传入的时候要强转
            bzero(&peer, sizeof(peer));
            memset(buffer, 0, sizeof(buffer));
            ssize_t s = recvfrom(_sock, buffer, sizeof(buffer) - 1,
                                 0, (struct sockaddr *)&peer, &len);
            /* These calls return the number of bytes received, or -1 if an error occurred. */
            // 返回的s是读到的字节数
            char result[256];
            std::string cmd_echo;
            char key[64];
            if (s > 0)
            {
#if 0
                buffer[s] = 0; // 把我们当前数据当作字符串
                if (strcasestr(buffer, "rm") != nullptr || strcasestr(buffer, "rmdir") != nullptr)
                {
                    std::cout << "危险命令, 不予执行" << std::endl;
                    continue;
                }
                FILE *fp = popen(buffer, "r");
                if (nullptr == fp)
                {
                    logMessage(ERROR, "popen: %d: %s", errno, strerror(errno));
                    continue;
                }
                while (fgets(result, sizeof(result), fp) != nullptr)
                {
                    cmd_echo += result;
                }
                fclose(fp);
#endif
                memset(key, 0, sizeof(key));
                uint16_t cli_port = ntohs(peer.sin_port);
                std::string cli_ip = inet_ntoa(peer.sin_addr);
                snprintf(key, sizeof key, "%s-%u", cli_ip.c_str(), cli_port);
                auto it = _users.find(key);
                if (it == _users.end())
                {
                    // 说明这个人不存在
                    logMessage(NORMAL, "add new user: %s", key);
                    _users.insert({key, peer});
                }
                //
            }
            for (auto &iter : _users)
            {
                std::string sendMessage = key;
                sendMessage += " # ";
                sendMessage += buffer;
                logMessage(NORMAL, "push message to %s", iter.first.c_str());
                sendto(_sock, sendMessage.c_str(), sendMessage.size(), 0, (struct sockaddr *)&(iter.second), sizeof(iter.second));
                // 把消息发过来之后，把消息广播给所有人
            } // sendto(_sock, cmd_echo.c_str(), cmd_echo.size(), 0, (struct sockaddr *)&peer, len);
            fflush(stdout);
        }
    }
};

#endif
