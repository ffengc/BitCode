#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<string>
#include<queue>
using namespace std;

//模板进阶


#if 0
template<class T, size_t N>
class array {
private:
	T _a[N];
};
#if 0
template<class T,string s>
template<class T, double d>
class A {};
#endif
//一般这些不能做非类型模板参数，一般是整型，char这些
int main() {
	array<int, 100>a1;
	array<double, 1000>a2;
	//现在我要求a1数组大小是100
	//a2是1000
	//怎么办？
	//非类型模板参数 -- 常量
	//我们知道，模板参数和函数参数是非常像的 -- 可以给缺省值
	return 0;
}
#endif

#include<array> //非类型模板参数是常量！
#if 0
//std::array
//固定大小的顺序容器 -- 静态数组
//我们具体的可以查文档 -- 很简单
//标准库的array的意义在哪?
int main() {
	array<int, 10>arr; //C++11希望用它
	int arr2[10];  //C
	//哪个好？
	cout << sizeof(arr) << endl;
	cout << sizeof(arr2) << endl;
	//两个都没有初始化


	//真正的区别在这 -- 越界检查
	//C数组的越界是不检查的，越界写才检查
	//而且越界写检查也是很有局限性的 -- 越多点就检查不到了
	//它是抽查机制

	arr[10];//它无论怎么样都会被查到！ 它里面应该assert了
	arr[10];
	arr2[15] = 1;

	//std::array的越界检查更严格
	return 0;
}
#endif


#if 0
//模板的特化 -- 模板特殊化处理
struct Date {
	Date(int year, int month, int day)
		:_year(year), _month(month), _day(day)
	{}
	bool operator>(const Date& d)const {
		if ((_year > d._year) || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day)) {
			return true;
		}
		else return false;
	}
	bool operator<(const Date& d)const {
		if ((_year < d._year) || (_year == d._year && _month < d._month) || (_year == d._year && _month == d._month && _day < d._day)) {
			return true;
		}
		else return false;
	}
private:
	int _year;
	int _month;
	int _day;
};
//函数模板 -- 参数匹配
template<class T>
bool Greater(T left, T right) {
	return left > right;
}
//特化 -- 针对某些类型进行特殊化处理
//首先，C++不能比较类型 不能 T == Date* 这样类型
//typeid不靠谱 -- 有平台问题，有时候整型返回的是int，有的时候返回的是i
//需要特化： -- 注意这里的语法！！！！
template<>
bool Greater<Date*>(Date* left, Date* right) {
	return *left > *right;
}
//注意语法！！！
// // ============================================================
//函数模板可以特化 -- 类模板也可以
namespace yufc {
	template<class T>
	struct less {
		bool operator()(const T& x1, const T& x2) const { 
			return x1 < x2;
		}
	};
	//特化
	template<>
	struct less<Date*> {
		bool operator()(Date*& x1, Date*& x2) const {
			return *x1 < *x2;
		}
	};
}

int main() {
	cout << Greater(1, 2) << endl;//可以比较，结果正确
	Date d1(2022, 7, 7);
	Date d2(2022, 7, 8);
	cout << Greater(d1, d2) << endl;//可以比较，结果正确
	Date* p1 = &d1;
	Date* p2 = &d2;
	cout << Greater(p1, p2) << endl;//可以比较，结果错误

	yufc::less<Date>lessFunc1;
	cout << lessFunc1(d1, d2) << endl;
	yufc::less<Date*>lessFunc2; //这里也面临着一样的问题
	cout << lessFunc2(p1, p2) << endl;

	//这个东西哪里有用呢
	priority_queue<Date, vector<Date>, less<Date>>dq1;
	priority_queue<Date*, vector<Date*>, less<Date*>>dq2;//这个如果不特化就会出问题

	//需要特化了
	dq2.push(new Date(2022, 9, 27));
	dq2.push(new Date(2022, 9, 25));
	dq2.push(new Date(2022, 9, 28));

	return 0;
}
#endif


//模板可以像缺省参数那样用
#if 0
template<class T1,class T2>
class Data {
public:
	Data() { cout << "Data<T1,T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
//全特化
template<>
class Data<int, char> {//全特化
public:
	Data() { cout << "Data<int,char>" << endl; }
private:
	int _d1;
	char _d2;
};
//偏特化
//任何针对模板参数进一步进行条件限制设计的特化版本
template<class T1>
class Data<T1, int> {
public:
	Data() { cout << "Data<T1, int>" << endl; }
};
//这种模板参数都有，但是也叫偏特化
template<class T1,class T2>
class Data<T1*, T2*> { //只要是指针 -- 都走这个偏特化
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
};
//模板参数是引用 -- 就会匹配它
template<class T1, class T2>
class Data<T1&, T2&> { //只要是指针 -- 都走这个偏特化
public:
	Data() { cout << "Data<T1&, T2&>" << endl; }
};
int main() {
	Data<int, int>d1;
	Data<int, char>d2;
	Data<int*, int*>d3;
	Data<double*, void*>d33;
	Data<int*, double>d4;

	Data<int&, int&>d5;
	Data<int&, char&>d6;

	return 0;
}
#endif
//其实这里模板的特化就是一个类型匹配的事情 -- 找最匹配的，不是最匹配的将就一下的也行，实在不对就报错
//就是这个思想


//模板的分离编译
//模板是不支持分离编译的
//问题1：因为分离编译之后，编译器很多地方搞不清楚这个东西到底是类型还是变量

//比如
template<class T>
void PrintContainer(const list<T>& lt) {
	typename list<T>::const_iterator it = lt.begin();
	//此时编译器是搞不清楚const_iterator到底是类型还是变量的 -- 加上一个typename前缀才行
	while (it != lt.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
int main() {
	list<int>lt = { 1,2,3,4 };
	PrintContainer(lt);
	return 0;
}

//问题2：重点 -- 一些接口会出现链接错误
//比如我们分离声明和定义 -- 调用push_back()这些就会报链接错误
//报链接错误 -- 找到了声明 -- 找不到定义
//调用函数的时候其实就是 call一个地址
//不是因为push_back()没有实现，而是没有被实例化
//构造函数，size()，operator[]这些函数需要链接吗 -- 不需要
//因为它们在vector.h中有定义 -- 所以vector<int>实例化的时候 -- 它们已经实例化了
//即，size()，vector(),operator[]这些函数在编译阶段已经确定地址了
//push_back(),insert()中在vector.h中只有声明，没有定义
//那么地址就只能在链接阶段去找 -- 报错说明找不到！
//编译器在遇到模板的时候是不会去跑的 -- T都不知道 -- 不知道我怎么确定heap里面开多少空间？

//怎么解决？
//1.模板声明和定义不要分开放到.h和.cpp中
//2.显示实例化 -- 写死了 -- 相当于没有模板了


//模板优缺点
/*
* 优点：
* 1.模板复用了代码，节省资源，更快的迭代开发，C++的STL因此而产生
* 2.增强了代码的灵活性（重复的工作交给编译做 -- 这就是进步）
* 缺点：
* 1.模板那会导致代码膨胀问题，也会导致编译时间变长
* 2.出现模板编译错误时，错误信息非常凌乱，不易定位错误
*/