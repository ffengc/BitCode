#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Person
{
public:
	void PrintPersonInfo();
private:
	char _name[20];//声明？定义？
	//对于变量的声明和定义取决于它是否有开空间
	char _gender[3];
	int _age;
};
//所以上面的成员变量其实就是声明

#if 0
int age;//这里是定义
#endif
//当然，这个age放在这里肯定是会发生链接冲突的，因为展开了两次
//所以
extern int age;//这个就是把定义变成声明了 -- 告诉编译器，这是个声明，我们再去.cpp里面定义即可
//这是解决问题的第一种方式，加一个static也行
//链接属性不同
//如果是static的话，只有当前文件可见，不会进符号表
//但是如果用static各个文件的就是不一样的了
//所以如果要在别的文件改age，用extern声明即可
