#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//C++不是纯面向对象的，是基于面向对象的
//Java才是纯面向对象

//类
//C语言-关注过程的实现，就是那些操作接口
#if 0
struct Stack {
	int* a;
	int top;
	int capacity;
};
void StackInit(struct Stack* ps);
void StackPush(struct Stack* ps, int x);
void StackPop(struct Stack* ps);
#endif
//C++ struct兼容C的语法
//同时将struct升级成类 -- 成员变量+成员函数
#if 0
struct Stack {
	void Init() {
		//...
	}
	void Push(int x) {}
	void Pop() {}

	int* a;
	int top;
	int capacity;
};
int main() {
	struct Stack st1;
	Stack st2;
	//这两种定义都是可以的
	st1.Init();
	st1.Push(1);
	st1.Push(2);
	st1.Pop();
	return 0;
}
//C++中定义类更喜欢用class
class ClassName {

};
#endif
//类的访问限定符
//封装
#if 0
class Stack {
public:
	void Init() {
		//...
	}
	void Push(int x) {}
	void Pop() {}
private:
	int* a;
	int top;
	int capacity;
};
int main() {
	Stack st;
	st.Init();
	st.Push(1);
	st.Push(2);
	//st.a = nullptr;
	return 0;
}
#endif
//访问限定符只限定类外面的访问，类里面的访问不限制
//在学继承之前，protected和private的价值是一样的


//类的两种定义方式
/*
* 1.声明和定义全部放到类当中，需要注意：成员函数如果在类中定义，编译器可能会将其当成内联函数处理
* 2.声明放到.h，类的定义放到.cpp文件中
*/

//见队列的定义
#include"f.h"
int main() {
	Queue q;
	q.Init();
	q.Push(1);
	q.Push(2);
	q.Pop();
	return 0;
}
//类的定义：
//1.小函数，想成为内联，直接在类里面定义即可
//2.如果是大函数，声明和定义分离即可


//面向对象三大特性：封装、继承、多态
//封装本质其实是一种管理
//C -- 没办法封装 - 规范使用函数访问数据 - 也可以直接访问数据 - 不规范
//C++ -- 封装 - 必须规范使用函数访问数据 - 不可以直接访问数据 - 规范