
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<map>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<vector>
#include<memory>
using namespace std;
#elif
#endif

//智能指针
//RAII是一种思想 -- 利用对象声明周期来控制程序资源


#if 0
template<class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}
	~SmartPtr() { delete _ptr; }
private:
	T* _ptr;
public:
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
};

//1.利用RAII控制资源
//2.拥有类指针的行为功能



struct A
{
public:
	int _a1 = 0;
	int _a2 = 0;
public:
	~A()
	{
		cout << "A::~A()" << endl;
	}
};



//auto_ptr -- C++98
int main()
{
	auto_ptr<A> ap1(new A);
	ap1->_a1++;


	return 0;
}
#endif

//1.利用RAII控制资源
//2.拥有类指针的行为功能
//3.拷贝问题

//list<int>lt;
//auto it = lt.begin();
//此时迭代器就是浅拷贝
//就是要指向同一块空间
//但是为什么迭代器浅拷贝没问题？因为迭代器不负责资源的释放！
//所以拷贝问题不是指我们做不到深拷贝
//而是需求就是浅拷贝
//所以我们要解决浅拷贝会释放两次的问题
struct A
{
public:
	int _a1 = 0;
	int _a2 = 0;
public:
	~A()
	{
		cout << "A::~A()" << endl;
	}
};
int main()
{
	//auto_ptr的处理方法 -- 资源转移
	auto_ptr<A> ap1(new A);
	auto_ptr<A>ap2(ap1);
	//我们调试可以发现 -- 拷贝之后-- 资源直接转给ap2了，ap1不管了
	//ap1->_a1++;//err
	//auto_ptr多年以来都被挂在了耻辱柱上 -- 很多公司明确要求不能使用它
	return 0;
}

//boost
//scoped_ptr
//shared_ptr
//weak_ptr

//C++11
//unique_ptr
//shared_ptr
//weak_ptr