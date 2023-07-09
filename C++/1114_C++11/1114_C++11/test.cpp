#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<functional>
#include<iostream>
#include<assert.h>
using namespace std;
#elif
#endif

//右值引用

//什么是左值？
#if 0
int main()
{
	int a = 10;
	const int b = 20;
	int* p = &a;
	//左值的特点是：可以取地址
	//右值不能取地址
	double x = 1.1;
	double y = 2.2;
	//以下几个都是常见的右值
	10;
	x + y;
	fmin(x, y);
	//右值的特点：不能去地址
	//给右值取别名
	int&& rr1 = 10;
	double&& rr2 = x + y;
	double&& rr3 = fmin(x, y);
	return 0;
}
#endif



//如果传值(T x) -- 传什么都可以 -- 拷贝
//我们为了减少拷贝 -- 喜欢传引用 -- (T& x)
//但是这种情况 -- 我们就只能传左值了 -- 所以建议用(const T& x)
//此时x既能接受左值也能接受右值
#if 0
template<class T>
void func(T& x)
{}
int main()
{
	//左值引用能不能给右值取别名？
	double x = 1.1;
	double y = 2.2;
	//double& ret = x + y;//err
	const double& ret = x + y; //加个const就行了
	//右值引用能不能给左值取别名？
	int num = 20;
	//int&& rr = num;	//err
	int&& rr5 = move(num);
	//不能直接引用，但是可以引用move之后的左值
	return 0;
}
#endif

/** 一个神奇的现象 */
/*
* 右值是不能取地址的
* 但是给右值取别名后，会导致右值被存储到特定的位置，且可以取地址
*/
#if 0
int main()
{
	double x = 1.1;
	double y = 2.2;
	int&& rr1 = 10;
	double&& rr2 = x + y;
	rr1 = 10;
	rr2 = 5.5;
	//有地址的
	printf("%p\n", &rr1);
	printf("%p\n", &rr2);
	return 0;
}
#endif

//右值引用的应用
//首先 -- 引用是干嘛的？
/** 引用的价值 -- 减少拷贝*/

//左值引用：
//1.做参数 -- a.减少拷贝，提高效率  b.做输出型参数
//2.做返回值 -- a.减少拷贝，提高效率  b.引用返回，可以修改返回对象，比如operator[]
//当左值引用做返回值的时候 -- 其实只解决了70%的问题
//比如	to_string() -- 传值返回
//因为 to_string(){}里面的string是局部对象
//我们传值返回，要做很多拷贝
//比如返回一个vector<vector<int>>
//怎么办？
//全局？ -- 全局在多线程下会出问题
//如果一定要优化 -- 放到参数上，做返回型参数 -- 问题：不符合写程序的习惯

//右值引用的一个重要功能 -- 就是解决上面返回时拷贝的问题
#if 1
namespace bit
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造(深拷贝)" << endl;

			//string tmp(s._str);
			//swap(s);

			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		// 移动构造
		string(string&& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			//此时我们发现s是一个右值 -- 一个将亡值 -- 我们还有必要进行深拷贝吗？
			//已经没有必要了 -- 我们直接swap -- 进行一下资源转移就行
			cout << "string(string&& s) -- 资源转移" << endl;
			swap(s);
		}
		// 拷贝赋值
		string& operator=(const string& s)
		{
			cout << "string& operator=(string s) -- 拷贝赋值(深拷贝)" << endl;
			string tmp(s);
			swap(tmp);

			return *this;
		}
		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string s) -- 移动赋值(资源移动)" << endl;
			swap(s);

			return *this;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;

				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}

bit::string to_string(int value)
{
	bool flag = true;
	if (value < 0)
	{
		flag = false;
		value = 0 - value;
	}

	bit::string str;
	while (value > 0)
	{
		int x = value % 10;
		value /= 10;

		str += ('0' + x);
	}

	if (flag == false)
	{
		str += '-';
	}

	std::reverse(str.begin(), str.end());
	return str;
}
#endif

// 拷贝构造和移动构造
#if 0
int main()
{
	bit::string ret = to_string(-3456);

	bit::string s1("1111111");
	bit::string s2(s1);

	return 0;
}
#endif
//拷贝构造：
//string to_string(char*str){return ans}
//string ret = to_string("1234");
//原来ans有一块空间
//ret有一块空间
//没有优化过的拷贝构造：
	//ans 拷贝到临时空间 tmp，tmp拷贝到ret，释放tmp和ans
//优化后的拷贝构造
	//ans 拷贝到ret上，释放ans
//移动构造
//ret的指针不指向原来的空间了 -- 直接指到ans上去
//ans的指针销毁
//此时移动构造没有发生拷贝

//右值引用的价值 -- 体现在移动构造和移动赋值上！

#if 0
int main()
{
	string s1("hello world");
	string s2(s1);//拷贝构造
	string s3 = s1 + s2; //移动构造
	return 0;
}
#endif

//stl里面所有的插入接口 -- 都增加了右值版本
//push_back()这些接口里面都有
#if 0
int main()
{
	vector<bit::string>v;
	return 0;
}
#endif
//还有emplace_back()这些接口



//完美转发
void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }

//万能引用：t既能引用左值，也能引用右值
template<typename T>
void PerfectForward(T&& t)
{
	//Fun(t);
	//完美转发
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10); //右值
	int a = 20;
	PerfectForward(a);//左值
	PerfectForward(std::move(a));//右值
	const int b = 8;
	PerfectForward(b);//const 左值
	PerfectForward(std::move(b));//const 右值
	return 0;
	/*
	左值引用
	左值引用
	左值引用
	const 左值引用
	const 左值引用
	*/
	///如果我们不用完美转发，我们发现t通通变成了左值
	///如果使用完美转发 -- t的属性就可以被保留
	//此时
	//右值引用
	//左值引用
	//右值引用
	//const 左值引用
	//const 右值引用
}

//完美转发 -- 什么时候有用
//比如stl
//void func(T&& x)
/// 因为要使用模板 -- 此时如果不用完美转发 
/// x会被引用折叠 -- 全部变成左值了 
/// 变成左值 -- 该拷贝的拷贝了
/// 所以完美转发一下！保持原来的引用属性 -- 不该拷贝的别拷贝了！
/// 如果我们要改代码的时候 -- 每一层都要完美转发
/// 不然这一层转了 -- 传过去没转 -- 最后还是深拷贝了
/// 可以看看list.h是如何改的