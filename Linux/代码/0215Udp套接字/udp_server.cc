

#include <memory>
#include <stdlib.h>
#include "udp_server.hpp"

// ./udp_server ip port //关于云服务器的问题
static void usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port\n"
              << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
    // std::string ip = argv[1];
    uint16_t port = atoi(argv[1]);
    std::unique_ptr<UdpServer> svr(new UdpServer(port /*,ip*/));
    svr->initServer();
    // std::cout << "init sucess" << std::endl;
    svr->start();
    return 0;
}
