
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<functional>
#include<unordered_map>
using namespace std;

#elif
#endif

//throw try catch

#if 0
double Division(int a, int b)
{
	//当b == 0的时候抛异常
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	else
	{
		return ((double)a / (double)b);
	}
}
void Func()
{
	int len = 0;
	int time = 0;
	cin >> len >> time;
	cout << Division(len, time) << endl;
}
int main()
{
	try
	{
		Func();
	}
	catch (int err) //如果类型不匹配也捕获不了
	{
		cout << err << endl;
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	//catch (const char* errmsg)
	//{
	//	cout << errmsg << endl;
	//}//同一个地方不能有两个一样的catch

	//万一最后的异常不知道什么类型，前面抛了很多个异常 -- 最后可以加一道保险杠
	catch (...) //可以捕获任意类型的异常 -- 防止程序出现未捕获异常时程序崩溃
	{
		cout << "未知异常" << endl;
	}
	return 0;
}
#endif

//虽然我们可以抛任意类型的异常 -- 但是库里面一般是很规范的
//一般跑一个类 -- exception
//这里我们用一个自己写的
//一般都带有这些信息
#if 0
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg), _errid(id) {}
	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _errid;
};
double Division(int a, int b)
{
	//当b == 0的时候抛异常
	if (b == 0)
	{
		Exception e("除0错误", 1);
		throw e;
	}
	else
	{
		return ((double)a / (double)b);
	}
}
//1.抛异常可以抛任意类型
//2.捕获时要求类型匹配
void Func1()
{
	int len = 0;
	int time = 0;
	cin >> len >> time;
	cout << Division(len, time) << endl;
}
void Func2()
{
	//如果对象太大 -- 怎么办
	//解决方法 -- 抛派生类
}
int main()
{
	while (true)
	{
		try
		{
			Func1();
		}
		catch (const Exception& e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}
#endif


//服务器开发中通常使用的异常继承体系
#if 0
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg), _id(id) {}
	virtual string what() const
	{
		return _errmsg;
	}
	virtual int getid() const
	{
		return this->_id;
	}
protected:
	string _errmsg;
	int _id;
};

//数据库的异常 -- 我们就要写一个专门的数据库异常类
class SqlException :public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id), _sql(sql) {}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
	virtual int getid() const
	{
		return this->_id;
	}
protected:
	const string _sql;
};


//缓存异常
class CacheException :public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}
	virtual string what() const
	{
		string str = "CacheException";
		str += _errmsg;
		return str;
	}
	virtual int getid() const
	{
		return this->_id;
	}
};

//http协议
#include<time.h>
class HttpServerException :public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id), _type(type) {}
	virtual string what() const
	{
		string str = "HttpServerException";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
	virtual int getid() const 
	{
		return this->_id;
	}
protected:
	const string _type;
};
void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}
	cout << "请求成功" << endl;
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 200);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 201);
	}
	SQLMgr();
}
#if 0
void HttpServer()
{
	//...
	srand(time(0));
	if (rand() % 3 == 0)
	{
#if 0
		throw HttpServerException("请求资源不存在", 100, "get");
#endif
		throw HttpServerException("网络错误", 102, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}
	CacheMgr();
}
#endif
void SendMsg(const string& s)
{
	//现在想要实现 -- 出现网络错误的时候 -- 重试三次
	// --> 在外面包一层try-catch把这个错误截胡
	srand(time(0));
	try
	{
		if (rand() % 3 == 0)
		{
			throw HttpServerException("网络错误", 102, "get");
		}
		else if (rand() % 4 == 0)
		{
			throw HttpServerException("权限不足", 101, "post");
		}
		cout << "发送成功:" << s << endl;
	}
	catch (const std::exception&)
	{

	}
	CacheMgr();
}
void HttpServer()
{
	string str = "今晚一起去散步吗？";
	//cin >> str;
	int n = 3;//最多尝试三次
	while (n--)
	{
		try
		{
			SendMsg(str);
			//没有发生异常
			break;
		}
		catch (const Exception& e)
		{
			//网络错误
			if (e.getid() == 100 && n > 0)
			{
				continue;
			}
			else
			{
				throw e;//这里就是异常的重新抛出
			}
		}
	}
}
#include<thread>
int main()
{
	while(1)
	{
		this_thread::sleep_for(chrono::seconds(1));
		try
		{
			HttpServer();
		}
		catch (const Exception & e) //这里捕获父类对象就可以
		{
			//多态
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}


//异常的重新抛出
//有可能单个catch不能完全处理一个异常，在进行一些校正处理以后，
//希望再交给更外层的调用链函数来处理
//catch则可以通过重新抛出将异常传递贵更上层的函数进行处理
#endif


//上面是异常重新抛出的第一种场景

//下面是异常重新抛出的第二种场景

double Division(int a, int b)
{
	if (b == 0)
	{
		throw "Division by zero condition!";
	}
	else
		return ((double)a / (double)b);
}
//一般来说 -- 我们如果没有异常捕获机制的时候
//我们可以正常的delete[]数组（delete[]或报错终止程序）
//但是现在有异常捕获了 -- 除零错误发生之后
//直接跳到catch的地方了 -- delete[]还没来得及执行 -- 内存泄漏
void Func()
{
	int* array = new int[10];
	try
	{
		int len; int time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << " " << array << endl;
		delete[]array;
		throw;
	}
	//...
	cout << "delete[]" << " " << array << endl;
	delete[]array;
}
int main()
{
	try
	{
		Func();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	catch (...)
	{
		cout << "unknown exception" << endl;
	}
	return 0;
}

/*
异常安全：
1.构造函数完成对象的构造和初始化，最好不要再构造函数中抛出异常
	否则可能导致对象不完整或没有完全初始化
2.析构函数主要完成资源的清理，最好不要在析构函数中抛出异常，否则
	可能导致资源泄露（内存泄漏，句柄未关闭等）
3.C++中异常经常会导致资源泄露问题，比如new和delete中抛出了异常，导致没有delete
	在lock和unlock中抛出了异常导致死锁，C++经常使用RAII来解决以上问题
	关于RAII我们在智能指针这节进行讲解
*/