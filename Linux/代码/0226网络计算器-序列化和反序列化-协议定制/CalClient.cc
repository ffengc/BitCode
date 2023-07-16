

#include <iostream>
#include "Sock.hpp"
#include "Protocol.hpp"
#include <unistd.h>

static void Usage(const std::string &proc)
{
    std::cout << "\nUsage: " << proc << " ip port\n"
              << std::endl;
}

// ./client ip port
int main(int argc, char **argv)
{
#if 1
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);
    Sock sock;
    int sockfd = sock.Socket();
    bool connectStat = sock.Connect(sockfd, server_ip, server_port);
    if (!connectStat)
    {
        std::cerr << "Connect error" << std::endl;
        exit(2);
    }
    while (true)
    {

        yufc_ns_protocol::Request req;
        // 1. 获取需求
        std::cout << "Please Enter x > ";
        std::cin >> req.__x;
        std::cout << "Please Enter y > ";
        std::cin >> req.__y;
        std::cout << "Please Enter op > ";
        std::cin >> req.__op;
        // 2. 序列化
        std::string s = req.Serialize();
        // 3. 添加报头
        s = yufc_ns_protocol::Encode(s);
        // 4. 发送给服务端
        yufc_ns_protocol::Send(sockfd, s);
        // 5. 正常读取
        std::string package;
        bool quit = false;
        std::string buffer;
        while (!quit)
        {
            bool res = yufc_ns_protocol::Recv(sockfd, &buffer);
            if (!res)
            {
                quit = false;
                break;
            }
            package = yufc_ns_protocol::Decode(buffer);
            if (package.empty())
                continue;
            yufc_ns_protocol::Response resp(0, 0);
            resp.Deserialize(package);
            std::cout << "code: " << resp.__code << std::endl; /* 当然这里还能优化，把code和描述用kv存起来 */
            std::cout << "result: " << resp.__result << std::endl;
            break; //一次处理一个报文，如果处理成功了就break
        }
    }
#endif
    close(sockfd);
    return 0;
}