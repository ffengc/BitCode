
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<functional>
#include<map>
#include<unordered_map>
using namespace std;
#elif
#endif

#include"SmartPtr.h"

//循环引用问题
//weak_ptr
//weak_ptr不增加引用计数，不参与内存资源的管理
//现在把yufc命名空间里面的weak_ptr也实现一下
#if 0
int main()
{
	test7();
	return 0;
}
#endif


//内存泄露
int main()
{
	//申请一个1G内存
	char* p1 = new char[1024 * 1024 * 1024];
	//内存泄露
	//进程正常结束，内存都会自动释放

	//危害
	// 1. 僵尸进程 -- 进程没有正常结束 -- 资源没有释放
		//僵尸多了，计算机就会变卡
		//所以一般都有一个监控程序 -- 如果这个程序出现问题 -- 会自动重启
	// 2. 长期运行的程序 -- 比如微信，QQ客户端这些，后台服务器这些、


	//课件上有给了一些链接 -- 一些内存泄露检测的工具
	//一些公司内部规范都规定使用自己公司内部实现的内存管理库
	return 0;
}