
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<functional>
using namespace std;


//设计一个只能在堆上面创建的类

//方法1：
#if 0
class HeapOnly
{
protected:
	//析构函数私有
	~HeapOnly() {}
protected:
	int _a;
public:
	//静态非静态都没关系
	//不传p也可以 -- delete this就行
	static void Delete(HeapOnly* p) 
	{
		cout << "HeapOnly::Delete()" << endl;
		delete p; 
	}
};
int main()
{
	//HeapOnly hp1;//栈
	//static HeapOnly hp2;//静态区
	HeapOnly* ptr = new HeapOnly;//堆
	//delete ptr; //delete释放不了 -- 我们自己写一个释放
	HeapOnly::Delete(ptr);
	return 0;
}
#endif



//方法2：
#if 0
class HeapOnly2
{
protected:
	//构造函数私有化
	HeapOnly2()
		:_a(0) {}
protected:
	int _a;
public:
	static HeapOnly2* CreatObj()
	{
		return new HeapOnly2;
	}
	//防止拷贝
	HeapOnly2(const HeapOnly2& hp) = delete;
	HeapOnly2& operator=(const HeapOnly2& hp) = delete;
};
int main()
{
	//HeapOnly2 hp1;//栈
	//static HeapOnly2 hp2;//静态区
	//HeapOnly2* ptr = new HeapOnly2;//堆
	//构造函数都私有了 -- new也new不了了 -- 提供一个公有的创建对象的接口
	HeapOnly2* ptr = HeapOnly2::CreatObj();
	//bug:
	//HeapOnly2 copy(*ptr);//拷贝构造的还在栈上，所以要把拷贝构造禁用
	return 0;
}
#endif



//设计一个类只能在栈上创建对象
//构造函数私有，然后自己重新写一个CreatObj()这种方式肯定是可以的
//这里不重复了
//当然，同样需要注意拷贝构造的问题
//但是不能删掉拷贝构造，因为我们的CreatObj()只能传值返回，如果禁了，就传不回来了
//我们可以禁用operator new，但是static然后copy的情况还是解决不了
//所以这个方案还是有一个小缺陷的
#if 0
class StackOnly
{
protected:
public:
};
int main()
{
	StackOnly st1;
	static StackOnly st2;
	StackOnly* ptr = new StackOnly;
	return 0;
}
#endif


//不能被继承的类
//C++98 -- 禁用父类构造函数
//C++11 -- final关键字


//设计只能创建一个对象的类（单例模式）
//有两种设计方案
//饿汉模式 -- 一开始(main())之前就创建出对象了
#if 0
class MemoryPool //假设要求设计一个内存池 -- 要求是单例的 ，当然只是名字而已，我们不是真的实现内存池
{
public:
	static MemoryPool* GetInstance()
	{
		return _pinst;
	}
	void* Alloc(size_t n)
	{
		void* ptr = nullptr;
		//...
		//里面啥东西我们不管
		return ptr;
	}
	void Dealloc(void* ptr)
	{
		//...
	}
protected:
	char* _ptr = nullptr;
protected:
	//构造函数私有
	MemoryPool() {}
	//两种写法，这里只写了一种，写成指针也可以，不写成指针也可以
	static MemoryPool* _pinst;//声明
};
MemoryPool* MemoryPool::_pinst = new MemoryPool;


#define MemoryPoolObject MemoryPool::GetInstance()
int main()
{
	//一般是这样调用的，直接调就行
	void* ptr1 = MemoryPool::GetInstance()->Alloc(10);
	MemoryPool::GetInstance()->Dealloc(ptr1);
	//单例模式一般就是通过这个 MemoryPool::GetInstance() 去找到这个已经创建好的对象，去调它里面的东西
	void* ptr2 = MemoryPoolObject->Alloc(29);
	MemoryPoolObject->Dealloc(ptr2);
	return 0;
}
#endif

//饿汉模式
//优点:
//简单、没有线程安全问题
//缺点:
//1.当一个程序中有多个单例，并且有先后初始化顺序的要求的时候，饿汉无法控制
//2.饿汉单例类创建得多的时候，初始化任务多的时候，会影响程序的启动速度


//饿汉模式
//对象第一次使用的时候再创建
class MemoryPool //假设要求设计一个内存池 -- 要求是单例的 ，当然只是名字而已，我们不是真的实现内存池
{
public:
	static MemoryPool* GetInstance()
	{
		//如果发现指针是nullptr的时候，说明我们是第一次使用这个类
		if (_pinst == nullptr)
		{
			//第一次创建
			cout << "第一次创建对象" << endl;
			_pinst = new MemoryPool;
		}
		return _pinst;
	}
	void* Alloc(size_t n)
	{
		void* ptr = nullptr;
		//...
		//里面啥东西我们不管
		return ptr;
	}
	void Dealloc(void* ptr)
	{
		//...
	}
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (_pinst)delete _pinst;
		}
	};
protected:
	char* _ptr = nullptr;
protected:
	//构造函数私有
	MemoryPool() {}
	//两种写法，这里只写了一种，写成指针也可以，不写成指针也可以
	static MemoryPool* _pinst;//声明
};
MemoryPool* MemoryPool::_pinst = nullptr;
//回收对象
//在main结束之后，它会调用析构函数，就会释放单例对象
static MemoryPool::CGarbo gc;
#define MemoryPoolObject MemoryPool::GetInstance()
int main()
{
	//一般是这样调用的，直接调就行
	cout << " -------- 第一次使用 -------- " << endl;
	void* ptr1 = MemoryPool::GetInstance()->Alloc(10);
	MemoryPool::GetInstance()->Dealloc(ptr1);
	//单例模式一般就是通过这个 MemoryPool::GetInstance() 去找到这个已经创建好的对象，去调它里面的东西
	cout << " -------- 第二次使用 -------- " << endl;
	void* ptr2 = MemoryPoolObject->Alloc(29);
	MemoryPoolObject->Dealloc(ptr2);
	return 0;
}

//懒汉模式
//优点：
//1.可以控制顺序
//2.不影响启动速度
//缺点：
//1.相对复杂
//2.线程安全问题要处理好

//单例对象释放问题
//1.一般情况下，单例对象不需要释放 -- 一般来说整个程序运行期间都会用它
//	单例对象再进程正常结束之后，也会资源释放
//2.有些特殊场景需要释放，比如单例对象析构时候，需要进行一些持久化操作（往文件、数据库里面去写）
//	大思路：定义一个内部的垃圾回收类