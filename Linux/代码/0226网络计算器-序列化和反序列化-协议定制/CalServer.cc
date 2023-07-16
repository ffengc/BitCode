
#include "Protocol.hpp"
#include "TcpServer.hpp"
#include <memory>
#include <signal.h>
#include "Daemon.hpp"

static void Usage(const std::string &proc)
{
    std::cout << "\nUsage: " << proc << " port\n"
              << std::endl;
}

void debug(int sock)
{
    std::cout << "service for debug, sock: " << sock << std::endl;
}

static yufc_ns_protocol::Response calHelper(const yufc_ns_protocol::Request &req)
{
    yufc_ns_protocol::Response resp(0, 0);
    switch (req.__op)
    {
    case '+':
        resp.__result = req.__x + req.__y;
        break;
    case '-':
        resp.__result = req.__x - req.__y;
        break;
    case '*':
        resp.__result = req.__x * req.__y;
        break;
    case '/':
        if (0 == req.__y)
            resp.__code = 1;
        else
            resp.__result = req.__x / req.__y;
        break;
    case '%':
        if (0 == req.__y)
            resp.__code = 2;
        else
            resp.__result = req.__x % req.__y;
        break;
    default:
        resp.__code = 3;
        break;
    }
    return resp;
}

void Calculator(int sock)
{
    /* 此处我们就要去定制协议 */
    std::string inbuffer;
    while (true)
    {
        // 1. 读取数据
        bool res = yufc_ns_protocol::Recv(sock, &inbuffer); // 在这里我们读到了一个请求
        // 2. 协议解析 -- 需要保证得到一个完整的报文
        if (!res)
            break;                                                // 读取失败
        std::string package = yufc_ns_protocol::Decode(inbuffer); // 这里Decode保证返回的是一个完整的字节流，是正确的，是可以序列化反序列化的！
        // 如果这个package是空 表示Decode没有给我们返回完整报文
        if (package.empty())
            continue;
        // 3. 保证该报文是一个完整的报文
        yufc_ns_protocol::Request req;
        // 4. 反序列化
        req.Deserialize(package);
        // 5. 业务逻辑
        yufc_ns_protocol::Response resp = calHelper(req);
        // 6. 序列化
        std::string respString = resp.Serialize(); // 序列化

        // 7. 在发送之前，添加报头
        // "length\r\ncode result\r\n"
        respString = yufc_ns_protocol::Encode(respString);
        // 8. 发送（暂时这样写，高级IO的时候，我们再来谈发送的逻辑）
        yufc_ns_protocol::Send(sock, respString); // 发送
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(1);
    }

    signal(SIGPIPE, SIG_IGN);
    /*
    一般经验: server 在编写的时候都要有严谨的判断逻辑
    一般的服务器，都是要忽略SIGPIPE信号的！防止运行中出现非法写入的问题
    */

    std::unique_ptr<yufc_tcpServer::TcpServer> server(new yufc_tcpServer::TcpServer(atoi(argv[1])));
    server->BindService(Calculator);
    MyDaemon();
    server->Start();
    return 0;
}