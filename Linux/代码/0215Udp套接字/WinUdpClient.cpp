
#pragma warning(disable:4996)

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib") // 固定用法

uint16_t serverPort = 8080;
std::string serverIp = "43.136.113.128"; // 服务器的ip

#define RECVSIZE 1024

int main()
{
	//window独有的打开方式
	WSADATA WSADATA;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &WSADATA) != 0)
	{
		return 1;
	}
	//中间这部分和linux的没有区别
	SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == clientSocket)
	{
		std::cout << "socket error!" << std::endl; //创建套接字失败
		return 2;
	}
	sockaddr_in dstAddr;
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_port = htons(serverPort);
	dstAddr.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());

	char buffer[RECVSIZE];
	while (true)
	{
		std::string message;
		std::cout << "please input # ";
		std::getline(std::cin, message);
		sendto(clientSocket, message.c_str(), (int)message.size(), 0, (sockaddr*)&dstAddr, (int)sizeof(dstAddr));

		struct sockaddr_in temp;
		int len = sizeof(temp);
		int s = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr*) & temp, &len);
		if (s > 0)
		{
			buffer[s] = 0;
			std::cout << "server echo # " << buffer << std::endl;
		}
	}


	//windows独有的
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}
