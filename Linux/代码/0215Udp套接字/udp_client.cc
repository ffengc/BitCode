
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <memory>
#include "thread.hpp"

#define READ_SEND_MAX_SIZE 1024

static void usage(std::string proc)
{
    std::cout << "\nUsage: " << proc << "serverIP serverPort\n"
              << std::endl;
}

uint16_t serverPort = 0;
std::string serverIp;

static void *udpSend(void *args)
{
    int sock = *(int *)((ThreadData *)args)->__args;
    std::string name = ((ThreadData *)args)->__name;

    std::string message;
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(serverIp.c_str());

    // 收信息+发送
    while (true)
    {
        std::cerr << "please echo the command # ";
        std::getline(std::cin, message);
        if (message == "quit")
            break;
        // 当client首次发送消息给服务器的时候，OS会自动给client bind它的IP和port
        sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr *)&server, sizeof(server));
    }
    return nullptr;
}

static void *udpRecv(void *args)
{
    int sock = *(int *)((ThreadData *)args)->__args;
    std::string name = ((ThreadData *)args)->__name;

    char buffer[READ_SEND_MAX_SIZE];
    while (true)
    {
        // 现在要读数据
        memset(buffer, 0, sizeof(buffer));
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        ssize_t s = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&temp, &len);
        if (s > 0)
        {
            buffer[s] = 0;
            std::cout << buffer << std::endl;
        }
    }
}

// 客户端我们就不封装了
// ./udp_client 127.0.0.1 8080
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        usage(argv[0]);
        exit(1);
    }
    int sock = socket(AF_INET, SOCK_DGRAM, 0); // 这里和服务端一样
    if (sock < 0)
    {
        std::cerr << "socket error" << std::endl;
        exit(2);
    }
    serverPort = atoi(argv[2]);
    serverIp = argv[1];
    // client 要不要绑定？
    // 要，但是一般client不会显式bind，程序猿不回自己bind
    // client是一个客户端 -> 普通人下载安装使用的 -> 如果程序员自己bind了 ->
    // client一定bind了一个固定的ip和port，玩意，其他客户端提前占用了这个port呢？
    // client一般不需要显式的bind指定的port，而是让OS自动随机选择（什么时候做的呢？）

    // 多线程
    std::unique_ptr<Thread> sender(new Thread(1, udpSend, (void *)&sock)); // send线程
    std::unique_ptr<Thread> recver(new Thread(1, udpRecv, (void *)&sock)); // recv线程

    sender->start(); // 把线程运行起来
    recver->start();

    sender->join();
    recver->join();
    close(sock);
    return 0;
}
