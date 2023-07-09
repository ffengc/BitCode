#pragma once

#include<iostream>
using namespace std;

class A
{
public:
	~A()
	{
		cout << "A::~A()" << endl;
	}
	int _a = 0;
	int _b = 0;
};

namespace yufc
{
	template<class T>
	class auto_ptr
	{
	private:
		T* _ptr;
	public:
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr) {}
		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}
		~auto_ptr()
		{
			if (_ptr)
			{
				cout << "Delete:" << _ptr << endl;
				delete _ptr;
			}
		}
		//ap1 = ap2;
		auto_ptr<T>& operator =(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
				{
					cout << "Delete:" << _ptr << endl;
					delete _ptr;
				}
				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	};

	//unique_ptr
	template<class T>
	class unique_ptr
	{
	private:
		T* _ptr;
	public:
		unique_ptr(T* ptr = nullptr)
			:_ptr(ptr) {}
		//仿拷贝
		unique_ptr(unique_ptr<T>& ap) = delete;
		unique_ptr<T>& operator=(unique_ptr<T>& ap) = delete;
		~unique_ptr()
		{
			if (_ptr)
			{
				cout << "Delete:" << _ptr << endl;
				delete _ptr;
			}
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	};

	//shared_ptr
	template<class T>
	class shared_ptr
	{
	protected:
		T* _ptr;
		//static int _count;
		int* _pCount;
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pCount(new int(1)) {}
		shared_ptr(shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			(*_pCount)++;
		}
		void release()
		{
			cout << "Delete:" << _ptr << endl;
			delete _ptr;
			delete _pCount;
		}
		shared_ptr<T>& operator=(shared_ptr<T>& sp)
		{
			if (_ptr == sp._ptr)
			{
				return *this; 
			}
			if (--(*_pCount) == 0)
			{
				release();
			}

			//共管新资源，++记数
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			(*_pCount)++;
			return *this;
		}
		~shared_ptr()
		{
			if (--(*_pCount) == 0)
			{
				release();
			}
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	};
	//template<class T>
	//int shared_ptr<T>::_count = 0;
}

void test_auto_ptr()
{
	std::auto_ptr<A>ap1(new A);
	ap1->_a++;
	std::auto_ptr<A>ap2(ap1);
	//ap1->_a++;//err
	//会出现拷贝对象的悬空问题
	//很多公司明确规定不能使用它
	std::auto_ptr<A>ap3(new A);
	//注意 -- 这里不是交换 -- 是把ap3的资源转移给ap2，然后把ap2的释放掉，ap3悬空
	ap2 = ap3;
	//ap3->_a++;
}

void test_unique_ptr()
{
	yufc::unique_ptr<A> up1(new A);
	//不准拷贝了
	//std::unique_ptr<A> up2(up1);
	up1->_a++;
	yufc::unique_ptr<A> up2;
	//up2 = up1;//err
}

void test_shared_ptr()
{
	yufc::shared_ptr<A> sp1(new A);
	yufc::shared_ptr<A> sp2(sp1);
	yufc::shared_ptr<A> sp3(sp1);
	yufc::shared_ptr<int> sp4(new int(1));
	yufc::shared_ptr<A>sp5(new A);
}
/**
 * 能否用静态变量来计数？
 * 我们期望是 针对不同空间，我们希望有多个记数，但是如果我们使用了静态变量来记数
 * 所有类型，所有空间的记数都堆在一起了.
 */


//weak_ptr
//循环引用
struct Node
{
	int _val;
	shared_ptr<Node> _next;
	shared_ptr<Node> _prev;
	~Node()
	{
		cout << "Node::~Node()" << endl;
	}
};
struct Node2
{
	int _val;
	weak_ptr<Node2> _next;
	weak_ptr<Node2> _prev;
	~Node2()
	{
		cout << "Node::~Node()" << endl;
	}
};

void test_weak_ptr()
{
	cout << "before use weak_ptr to construct the Node" << endl;
	std::shared_ptr<Node>n1(new Node);
	std::shared_ptr<Node>n2(new Node);
	//tips:shared_ptr的构造是加了explicit的 -- 不允许隐式类型转换，所以不能这样写
	//std::shared_ptr<Node>n2 = new Node; //err

	//我们看这种情况 -- 此时不能正确释放了 -- 为什么？
	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;
	n1->_next = n2;
	n2->_prev = n1;
	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;
	//这里就是循环引用的问题

	//shared_ptr是无法解决这个问题的
	//weak_ptr不是常规的智能指针，没有RAII，不支持直接管理资源
	//weak_ptr就是shared_ptr的小跟班 -- 专门帮忙处理shared_ptr的剩余问题
	//weak_ptr主要用shared_ptr构造 -- 处理循环引用问题

	//当我们把Node里面的_prev和_next改成weak_ptr之后，_prev和_next，就不增加记数
	//它不参与资源释放管理，可以访问和修改资源，不存在循环引用问题
	cout << "after use weak_ptr to construct the Node" << endl;
	std::shared_ptr<Node2>n11(new Node2);
	std::shared_ptr<Node2>n21(new Node2);
	cout << n11.use_count() << endl;
	cout << n21.use_count() << endl;
	n11->_next = n21;
	n21->_prev = n11;
	cout << n11.use_count() << endl;
	cout << n21.use_count() << endl;
}