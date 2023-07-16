

#ifndef __Yufc_Protocol_For_Cal
#define __Yufc_Protocol_For_Cal

#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Log.hpp"

/* 协议的本质 --> 约定! */

#define RECV_MAX_SIZE 1024

/* 请求协议是必须自带序列化功能的 一个结构体是很难发送的 需要序列化成string */
/* 上次0222定制的协议是不完善的！我们需要定制报文*/

// 协议
/* length\r\n__x __op __y\r\n*/
/* length这些就叫做协议报头 */

namespace yufc_ns_protocol
{
#define MYSELF true
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define SEP "\r\n"
#define SEP_LEN strlen(SEP)
    class Request
    {
    public:
        std::string Serialize()
        {
#if MYSELF
            std::string str;
            str = std::to_string(__x);
            str += SPACE;
            str += __op; // BUG
            str += SPACE;
            str += std::to_string(__y);
            return str;
#else
            /* 使用别人的序列化方案 */
            #include <jsoncpp/json/json.h>
            Json::Value root;
            root["x"] = __x;
            root["y"] = __y;
            root["op"] = __op;
            Json::FastWriter writer;
            return writer.write(root);
#endif
        }
        bool Deserialize(const std::string &str)
        {
#if MYSELF
            std::size_t left = str.find(SPACE);
            if (left == std::string::npos)
            {
                return false; // 反序列化失败
            }
            std::size_t right = str.rfind(SPACE);
            if (right == std::string::npos)
            {
                return false; // 反序列化失败
            }
            __x = atoi(str.substr(0, left).c_str()); // 拿到__x的字符串之后直接 atoi 就行
            __y = atoi(str.substr(right + SPACE_LEN).c_str());
            if (left + SPACE_LEN > str.size())
                return false;
            __op = str[left + SPACE_LEN];
            return true;
#else
            #include <jsoncpp/json/json.h>
            Json::Value root;
            Json::Reader reader;
            reader.parse(str, root);
            __x = root["x"].asInt();
            __y = root["y"].anInt();
            __op = root["op"].asInt();
            return true;
#endif
        }

    public:
        Request() {}
        Request(int x, int y, char op) : __x(x), __y(y), __op(op) {}
        ~Request() {}

    public:
        int __x;
        int __y;
        char __op; // '+' ...
    };

    class Response
    {
    public:
        /* "code result" */
        std::string Serialize()
        {
#if MYSELF
            std::string s;
            s = std::to_string(__code);
            s += SPACE;
            s += std::to_string(__result);
            return s;
#else
            #include <jsoncpp/json/json.h>
            Json::Value root;
            root["code"] = __code;
            root["result"] = __result;
            Json::FastWriter writer;
            return writer.write(root);
#endif
        }
        bool Deserialize(const std::string &s)
        {
#if MYSELF
            // std::cerr << "s: " << s << std::endl;
            std::size_t pos = s.find(SPACE);
            if (pos == std::string::npos)
                return false;
            __code = atoi(s.substr(0, pos).c_str());
            __result = atoi(s.substr(pos + SPACE_LEN).c_str());
            return true;
#else   
            Json::Value root;
            Json::Reader reader;
            reader.parse(s, root);
            __code = root["code"].asInt();
            __result = root["result"].asInt();
            return true;
#endif
        }

    public:
        Response() {}
        Response(int result, int code) : __result(result), __code(code) {}
        ~Response() {}

    public:
        int __result; // 计算结果
        int __code;   // 计算结果的状态码
        /* 0表示计算结果可信任 */
    };

    // 临时方案
    bool Recv(int sock, std::string *out)
    {
        char buffer[RECV_MAX_SIZE];
        memset(buffer, 0, sizeof buffer);
        ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (s > 0)
        {
            buffer[s] = 0;
            *out += buffer;
        }
        else if (s == 0)
        {
            logMessage(NORMAL, "client quit");
            return false;
        }
        else
        {
            std::cerr << "recv error" << std::endl;
            return false;
        }
        return true;
    }

    // 临时方案
    void Send(int sock, const std::string sendStr)
    {
        send(sock, sendStr.c_str(), sendStr.size(), 0);
    }

    // "length\r\n__x __op __y\r\n"
    std::string Decode(std::string &buffer)
    {
        std::size_t pos = buffer.find(SEP);
        if (pos == std::string::npos) // 没有找到 返回空串
            return "";
        int size = atoi(buffer.substr(0, pos).c_str());
        int surplus = buffer.size() - pos - SEP_LEN - SEP_LEN; // 如果这个surplus大于报文长度
        // 则说明 这个报文长度是可以保证我们整体解析出一个合法字符串的
        if (surplus >= size)
        {
            // 至少具有一个合法报文，可以动手提取了
            buffer.erase(0, pos + SEP_LEN); // 此时"__x __op __y\r\n"
            std::string s = buffer.substr(0, size);
            buffer.erase(0, size + SEP_LEN);
            // 此时我们就把合法的部分截取出来了 就是s
            return s;
        }
        else
        {
            return "";
        }
    }

    std::string Encode(std::string &s)
    {
        // 添加报头
        std::string length = std::to_string(s.size());
        std::string new_package = length;
        new_package += SEP;
        new_package += s;
        new_package += SEP;
        return new_package;
    }

}

#endif