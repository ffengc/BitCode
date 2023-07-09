#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<list>

using namespace std;

#elif
#endif

//列表初始化
#if 0
int main()
{
	// 内置类型变量
	int x1 = { 10 };
	int x2{ 10 };
	int x3 = 1 + 2;
	int x4 = { 1 + 2 };
	int x5{ 1 + 2 };
	// 数组
	int arr1[5]{ 1,2,3,4,5 };
	int arr2[]{ 1,2,3,4,5 };
	// 动态数组，在C++98中不支持
	int* arr3 = new int[5]{ 1,2,3,4,5 };
	// 标准容器
	vector<int> v{ 1,2,3,4,5 };
	map<int, int> m{ {1,1}, {2,2,},{3,3},{4,4} };
	return 0;
}
#endif

#if 0
class Point
{
public:
	Point(int x = 0, int y = 0) : _x(x), _y(y)
	{}
private:
	int _x;
	int _y;
};
int main()
{
	Point p{ 1, 2 };
	return 0;
}
#endif

//结合容器用比较多
#if 0
int main()
{
	vector<int>arr = { 1,2,3,4 };
	vector<int>arr2{ 1,2,3,4 };
	list<int>arr3{ 1,2,3,4 };
	//{}是运算符吗？ -- 不是
	//是C++11新增的一个类型，叫做
	auto x = { 1,2,3,4 };
	cout << typeid(x).name() << endl;
	//class std::initializer_list<int>
	initializer_list<int>array1 = { 1,2,3 };
	for (auto& e : array1)
	{
		cout << e << " ";
	}
	cout << endl;
	return 0;
}
#endif

//自己写的vector支持{}吗
//需要补充{}的构造函数


#if 0
class Point
{
public:
	Point(int x = 0, int y = 0) : _x(x), _y(y)
	{}
private:
	int _x;
	int _y;
};
int main()
{
	//现在可以这样支持了
	vector<Point>parr = { {1,2},{2,3} };
	map<string, string>m = { {"A","a"},{"B","b" } };
	m = { {"C","c"},{"D","d" } };//这里是赋值
	return 0;
}
#endif



//auto
#if 0
#include<string.h>
int main()
{
	auto funciton = strcpy;
	cout << typeid(funciton).name() << endl;
	return 0;
}
#endif


//decltype
#if 0
int main()
{
	//可以用来推导类型
	//typeid拿到的类型只是类型的字符串，不能用这个再去定义对象什么的
	int x = 10;
	decltype(x) y = 20;
	cout << typeid(y).name() << endl;

	//和auto的意义是不一样的
	decltype(x) y1 = 20.22;
	auto y2 = 20.22;
	cout << y1 << " " << y2 << endl;
	return 0;
}
#endif



//新容器
#include<array>
#include<forward_list>
int main()
{
	//array 和 forward_list 
	//被很多人吐槽 -- 很鸡肋
	//array -- 希望替代a[]
	//array越界检查严格
	array<int, 10>arr;
	
	//forward_list
	forward_list<int>a = { 1,2,3,4 };
	forward_list<int>::iterator it = a.begin();
	while (it != a.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//和list就是差一个指针的位置，而且forward_list的功能还不全
	return 0;
}