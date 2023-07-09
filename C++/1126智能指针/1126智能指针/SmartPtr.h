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
	//我们还是提供一个默认的删除器，不然删啥都得传
	template<class T>
	struct DefaultDeleter
	{
		void operator()(T* ptr)
		{
			delete ptr;//默认是delete
		}
	};

	template<class T, class D = DefaultDeleter<T>> //传多一个定制删除器
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
			D()(_ptr);//用定制删除器释放
			//delete _ptr;
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

		int use_count()
		{
			return *_pCount;
		}
		T* get() const
		{
			return _ptr;
		}
	};
	//template<class T>
	//int shared_ptr<T>::_count = 0;

	//weak_ptr不是一个功能型的智能指针，是辅助型的
	//它的发明是为了解决shared_ptr的循环引用问题
	//STL的实现比我们这个复杂很多，他还处理了很多其他的问题
	//STL的weak_ptr其实保存了引用计数，用于处理过期的问题，具体看杭哥解释
	//STL中的它不增加引用计数，但是它要保存一下
	template<class T>
	class weak_ptr
	{
	protected:
		T* _ptr;
	public:
		weak_ptr()
			:_ptr(nullptr) {}
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr) {}
		weak_ptr(const weak_ptr<T>& wp)
			:_ptr(wp._ptr) {}
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
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
		//库里面其实还提供get，提供原生指针
		T* get() const
		{
			return _ptr;
		}
	};
}

//想要实现库里面那一套，还得复杂不少
//其实shared_ptr还涉及到线程安全问题，要加锁的


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

#if 1
void test_shared_ptr()
{
	yufc::shared_ptr<A> sp1(new A);
	yufc::shared_ptr<A> sp2(sp1);
	yufc::shared_ptr<A> sp3(sp1);
	yufc::shared_ptr<int> sp4(new int(1));
	yufc::shared_ptr<A>sp5(new A);
}
#endif
/**
 * 能否用静态变量来计数？
 * 我们期望是 针对不同空间，我们希望有多个记数，但是如果我们使用了静态变量来记数
 * 所有类型，所有空间的记数都堆在一起了.
 */


//weak_ptr
//循环引用
#if 0
struct Node
{
	int _val;
	yufc::shared_ptr<Node> _next;
	yufc::shared_ptr<Node> _prev;
	~Node()
	{
		cout << "Node::~Node()" << endl;
	}
};
struct Node2
{
	int _val;
	yufc::weak_ptr<Node2> _next;
	yufc::weak_ptr<Node2> _prev;
	~Node2()
	{
		cout << "Node::~Node()" << endl;
	}
};
#endif
#if 0 //stl的weak_ptr测试
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



//yufc的weak_ptr测试
void test_weak_ptr2()
{
	cout << " ----- before use weak_ptr to construct the Node ----- " << endl;
	yufc::shared_ptr<Node>n1(new Node);
	yufc::shared_ptr<Node>n2(new Node);
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

	cout << endl << endl;

	//shared_ptr是无法解决这个问题的
	//weak_ptr不是常规的智能指针，没有RAII，不支持直接管理资源
	//weak_ptr就是shared_ptr的小跟班 -- 专门帮忙处理shared_ptr的剩余问题
	//weak_ptr主要用shared_ptr构造 -- 处理循环引用问题

	//当我们把Node里面的_prev和_next改成weak_ptr之后，_prev和_next，就不增加记数
	//它不参与资源释放管理，可以访问和修改资源，不存在循环引用问题
	cout << " ----- after use weak_ptr to construct the Node ----- " << endl;
	yufc::shared_ptr<Node2>n11(new Node2);
	yufc::shared_ptr<Node2>n21(new Node2);
	cout << n11.use_count() << endl;
	cout << n21.use_count() << endl;
	n11->_next = n21;
	n21->_prev = n11;
	cout << n11.use_count() << endl;
	cout << n21.use_count() << endl;
}
#endif




//定制删除器
struct Node
{
	int _val;
	std::shared_ptr<Node> _next;
	std::shared_ptr<Node> _prev;
	~Node()
	{
		cout << "Node::~Node()" << endl;
	}
};
void test5()
{
	std::shared_ptr<Node> n1(new Node[5]); //这里报错，因为delete[]没有匹配上
	std::shared_ptr<Node> n2(new Node);
	//这其实和new的底层实现是有关系的
	//new[]但是delete没有[] -- 会不会报错？为什么会报错？其实这和平台有关系
	//new Node[5] 这里涉及到Node的构造和析构
	//此时 new Node[5]   -->  5次malloc和5次构造函数
	//如果是delete --> 1次析构函数+free
	//delete[] --> 5次析构函数+free
	//此时如果编译器发现我们的析构函数没写 -- 他会认为这个Node不需要析构 -- 直接free就行
	//他会做优化 -- 因此如果析构函数不写  -- 有时候上面的情况不报错

	//假设Node大小是12，现在new Node[5]
	//在VS下，其实开的不是60字节，而是64字节 -- 4个字节放在头部，用来存个数
	//因为delete[]其实规定不传个数 -- 所以new Node[]的时候会偷偷记录
	//所以调用delete[] 就知道到底要调用多少次析构了
	//所以new []返回来的指针其实比真实malloc出来的地址向后偏移了4个字节
	//delete[]的时候，其实指针就会往前偏移四个字节，先找到个数
	//所以delete[] 其实是free((char*)ptr - 4)这个位置的指针
	//如果直接delete 首先5个Node只析构一个，其次头上的4个字节没人管了

	//所以我们delete的时候要匹配

	//我们用这个智能指针的时候的场景会非常复杂
	std::shared_ptr<Node> n3(new Node[6]); 
	std::shared_ptr<int> n4((int*)malloc(sizeof(int) * 12));
	//所以我们需要定制删除器
	//一般是传一个仿函数或匿名参数
}
template<class T>
struct DeleteArray
{
	void operator()(T* ptr)
	{
		cout << "delete[] " << ptr << endl;
		delete[] ptr;
	}
};
template<class T>
struct Free
{
	void operator()(T* ptr)
	{
		cout << "free() " << ptr << endl;
		free(ptr);
	}
};
void test6()
{
	//这里要看清楚文档 -- shared_ptr的定制删除器是在构造函数里面传的
	//unique_ptr的地址删除器是现在模板参数里面传的
	std::shared_ptr<Node> n1(new Node[5], DeleteArray<Node>());
	std::shared_ptr<int> n4((int*)malloc(sizeof(int) * 12), Free<int>());
	//这样就不会出问题了
	std::shared_ptr<Node> n3(new Node[5], [](Node* ptr) {delete[] ptr; });//这里用匿名函数也是很好用的
	std::shared_ptr<int> n2((int*)malloc(sizeof(int) * 12), [](int* ptr) {free(ptr); });
	//还可以这么玩
	std::shared_ptr<FILE> n5(fopen("test.txt", "w"), [](FILE* ptr) {fclose(ptr); });


	//unique_ptr不能用匿名函数了，因为要在模板参数里面传对象
	std::unique_ptr<Node, DeleteArray<Node>>up(new Node[5]);
}
void test7()
{
	//测试我们自己定义的shared_ptr的删除器
	yufc::shared_ptr<Node, DeleteArray<Node>>up(new Node[5]);
}



//如果我们要像库里面一样，可以从构造函数传，我们目前实现的架构是做不到的
//因为STL里面的计数器其实是封装成了一个类的
//我们传定制删除器的时候其实还往下传了一层
//现在我们如果要通过构造函数传，这个删除器就只能在构造函数里面用了，外面用不了。
//所以我们写一个从模板参数里面传的

//定制删除器在开始里面很少
//不过平时使用还是地用到的