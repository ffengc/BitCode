
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
using namespace std;

#if 0
int main()
{
	//cin和scanf
	//默认是用空格分开的
	int year = 0; int month = 0; int day = 0;
#if 0
	cin >> year >> month >> day;
	cout << year << " " << month << " " << day << endl;
	int ret = scanf("%d%d%d", &year, &month, &day);//不要加空格
	cout << year << " " << month << " " << day << endl;
#endif

	//如果是这样输入咋办？
	//20221128
	scanf("%4d%2d%2d", &year, &month, &day);
	cout << year << " " << month << " " << day << endl;

	string str;
	cin >> str;
	year = stoi(str.substr(0, 4));
	//...
	//这样就行了
	return 0;
}
#endif

//oj题IO型的一些多组输入怎么办？
#if 0
int main()
{
	int year = 0; int month = 0; int day = 0;
	string str;
	while (cin >> str) //ctrl+Z+enter就能结束，给终端发送一个结束标志
					   //ctrl+C也可以，ctrl+C相当于kill -9直接杀掉
	{
		year = stoi(str.substr(0, 4));
		month = stoi(str.substr(4, 2));
		day = stoi(str.substr(6, 2));
		cout << year << " " << month << " " << day << endl;
	}
	return 0;
}
#endif


//复习 -- 隐式类型转换
#if 0
class A
{
public:
	explicit A(int a)
		:_a(a) {}
	operator int()
	{
		return _a;
	}
protected:
	int _a;
};

int main()
{
	//内置类型转换成自定义类型：
	//A aa1 = 1;//这里其实是隐式类型转换，先用1构造+拷贝构造 -- 所以加explicit就跑不动了
			  //但是事实上编译器会优化成一个构造
	A aa1(1);

	//如果我们要支持一个自定义类型转换成内置类型
	//重载一个operator int -- 这样就支持了
	int i = aa1;
	return 0;
}
#endif

//所以事实上
//刚才while(cin>>str)里面其实是重载了一个operator bool
//所以可以被转换成bool类型


//C++的文件流

struct ServerInfo
{
	char _address[20];
	int _port;
};

#if 0
int main()
{
	ifstream ifs("test.cpp");
	char ch = ifs.get();
	while (ifs)
	{
		cout << ch;
		ch = ifs.get();
	}
	//不需要显式close，因为它是对象，可以自动调用析构
	return 0;
}
#endif


struct Date
{
	int year;
	int month;
	int day;
	friend istream& operator>>(istream& cin, Date& d)
	{
		cin >> d.year >> d.month >> d.day;
		return cin;
	}
	friend ostream& operator<<(ostream& cout, const Date& d)
	{
		cout << d.year << "年" << d.month << "月" << d.day << "日" << endl;
		return cout;
	}
};
int main()
{
	ifstream ifs("test.txt");
	int i;
	string s;
	double d;
	Date de;//这个就是C++的优势，自定义类型也可以
	ifs >> i >> s >> d >> de;
	cout << i << " " << s << " " << d << " " << de << endl;
	return 0;
}