
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
#include<list>
using namespace std;
#elif
#endif


//类的默认成员函数 -- 以前是6个1怕
// 
//现在是8个 -- 移动构造/移动赋值

//所以深拷贝的时候，我们需要自己写移动构造和移动赋值
#if 0
int main()
{
	return 0;
}
#endif

/** 移动构造和移动赋值的一些注意的点 */
/*
* 如果我们没有自己实现移动构造，而且！
* 而且没有实现析构函数、拷贝构造、拷贝赋值重载中的任意一个。
* 那么编译器会自动生成。
* 自动生成的：
* 对内置类型会执行逐字节拷贝，自定义类型，则需要看这个成员
* 是否实现移动构造，如果实现了就调用移动构造，如果没有实现就效用拷贝构造。
*/
/*
* 如果没有实现移动赋值，而且没有析构、拷贝构造、拷贝赋值中的任意一个
* 那么编译器会自动生成一个默认移动构造。
* 默认生成的移动构造，对于内置类型成员会逐行逐成员按字节拷贝
* 自定义类型会看这个成员是否实现了移动赋值，如果实现了就调用，
* 没实现就调用拷贝复制 
*/

#if 0
struct Person
{
public:
	Person(Person&& p) = default;//强制生成
	Person() = delete;//强制不允许生成 -- 这里是不允许Person被构造
};
int main()
{
	//Person p; -- err
	return 0;
}
#endif


//面试题 -- 要求用delete关键字创建一个类 -- 只能在堆上生成
//1.构造函数私有 -- 但是用不到delete关键字
#if 0
class HeapOnly
{
public:
	~HeapOnly() = delete;
	void destructor()
	{
		delete[] _str;
		//operator delete(this);
		//或者在外面operator delete(ptr)
	}
private:
	char* _str;
};
int main()
{
	//HeapOnly hp1; err
	//static HeapOnly hp2; err
	HeapOnly* ptr = new HeapOnly;
	//这样我们可以构造了 -- 但是我们怎么析构呢？
	//没办法析构了
	//delete ptr;//err
	//我们自己写一个析构不就行了？
	ptr->destructor();
	operator delete(ptr);
	//free也可以，operator delete和free类似
	// //为了匹配一点我们还是用operator delete好点
	//free(ptr);
	return 0;
}
#endif



//可变参数模板
//Args... args代表N个参数包(N>=0)
#if 0
void ShowList()
{
	cout << endl;//可以理解成递归的终止条件
}
template <class T, class ...Args>
void ShowList(const T& val, Args... args)
{
	//cout << sizeof...(args) << endl; //可以算出参数的个数
	//1.
	cout << val << " ";
	ShowList(args...);//但是在0个参数的时候，就不适合调用自己了，所以我们重载一个0个参数的
	//但是这个递归不是运行时调用的 -- 是编译时调用的
}
int main()
{
	string str = "hello";
	/*ShowList();
	ShowList(1, 'A');
	ShowList(1, 'A', str);
	ShowList("aa");*/
	ShowList(1, 'A', str);
	return 0;
}
#endif


//如果只给一个Args呢
#if 0
template <class T>
void PrintArg(const T& x)
{
	cout << x << " ";
}
template <class ...Args>
void ShowList(Args... args)
{
	int a[] = { (PrintArg(args),0)... }; cout << endl;
	//利用列表初始化去推
}
int main()
{
	ShowList('a', 1, 2.22);
	return 0;
}
#endif



//emplace
#if 0
int main()
{
	vector<int>v;
	//这两种操作没有区别
	v.emplace_back(1);
	v.push_back(2);

	vector<pair<string, int>>v2;
	v2.push_back({ "sort",1 });//构造+拷贝构造/构造+移动构造
	v2.emplace_back("sort", 1);//构造
	v2.emplace(v2.begin(), "my", 2);
	for (auto& e : v2)
	{
		cout << e.first << " " << e.second << endl;
	}
	return 0;
}
#endif



#if 0
class Date
{
protected:
	int _year;
	int _month;
	int _day;
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year), _month(month), _day(day)
	{
		cout << "Date::Date()" << endl;
	}
	Date(const Date& d)
		:_year(d._year), _month(d._month), _day(d._day) 
	{
		cout << "Date::Date(const Date&)" << endl;
	}
	Date& operator=(const Date& d)
	{
		cout << "Date& Date::operator=(const Date& d)" << endl;
	}
};
int main()
{
	//验证发现对vector没有区别，对list还是有区别的
	//按道理来讲emplace不用拷贝构造 ， 至于vector为什么没有验证出来要去看源码
	//但没啥必要去看
	cout << "----------------- vector -----------------" << endl;
	vector<Date>v3;
	v3.push_back(Date(2022, 11, 16));
	cout << "---------------" << endl;
	v3.emplace_back(2022, 11, 16);
	cout << "----------------- list -----------------" << endl;
	list<Date>l;
	l.push_back(Date(2022, 11, 16));
	cout << "---------------" << endl;
	l.emplace_back(2022, 11, 16);
	return 0;
}
#endif



//像函数使用的对象/类型
//1.函数指针
//2.仿函数 -- 类重载了() -- 也叫函数对象
//3.lambda

#if 0
struct Goods
{
	string _name;
	double _price;
	int _evaluate;
	//...
	Goods(const char* str, double price, int evaluate)
		:_name(str), _price(price), _evaluate(evaluate) {}
};
#endif
//如果我们想对_name,_price,_evaluate这些对象进行排序
//我们要提供三个仿函数

//lambda书写格式：
//[capture - list](parameters)mutable->return-type{ statement };
#if 0
int main()
{
#if 0
	//两个数相加
	auto add1 = [](int a, int b)->int {return a + b; };
	cout << typeid(add1).name() << endl;
	cout << add1(1, 2) << endl;

	//省略返回值
	auto add2 = [](int a, int b) {return a + b; };
	cout << add2(1, 2) << endl;

	//交换
	int x = 0; int y = 1;
	auto swap1 = [](int& a, int& b) {int tmp = a; a = b; b = tmp; };
	swap1(x, y);
	cout << x << " " << y << endl;
	//
	auto swap2 = [](int& a, int& b)
	{
		int tmp = a; a = b; b = tmp;
	};

	//要求不传参数交换x,y
	int x = 0; int y = 1;
	auto swap3 = [x, y]()mutable// 捕捉列表
	{
		int tmp = x; x = y; y = tmp;
	};
	swap3();
	//默认捕捉过来的变量不能修改 -- 所以加一个mutable
	cout << x << " " << y << endl;
	//发现改不了 -- 这种捕捉只是拷贝捕捉
#endif
	int x = 0; int y = 1;
	auto swap4 = [&x, &y]()
	{
		int tmp = x; x = y; y = tmp;
	};
	swap4();
	cout << x << " " << y << endl;
	return 0;
}
#endif


struct Goods
{
	string _name;
	double _price;
	int _evaluate;
	//...
	Goods(const char* str, double price, int evaluate)
		:_name(str), _price(price), _evaluate(evaluate) {}
};
ostream& operator<<(ostream& out, const Goods& g)
{
	cout << g._name << " " << g._price << " " << g._evaluate << endl;
	return out;
}
int main()
{
	vector<Goods> v = { {"苹果",2.1,5},{"香蕉",3,4},{"橙子",2.2,3},{"菠萝",1.5,4} };
	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._name < g2._name;
		});
	for (auto e : v)
	{
		cout << e << endl;
	}
	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._evaluate < g2._evaluate;
		});
	for (auto e : v)
	{
		cout << e << endl;
	}
	return 0;
}