#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cassert>
using namespace std;



/// <summary>
/// 一个类到底可以重载多少运算符呢？ -- 看哪些运算符对这个类型有意义
/// </summary>
class Date
{
	//友元函数 -- 这个函数内部可以使用Date对象访问私有保护成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in,Date& d);
public:
	//判断闰年
	bool IsLeapYear(int year) {
		//懒得写了
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))return true;
		return false;
	}
	//获得每个月的天数
	int GetMonthDay(int year, int month) {
		static int days[] = { NULL, 31,28,31,30,31,30,31,31,30,31,30,31 };
		//最好写一个static吧，因为这个days[]可能会被频繁的调用，不需要每次都开一个days[]出来，开一个重复用就行
		if (month == 2 && IsLeapYear(year))return 29;
		return days[month];
	}
	bool is_DateValid() {
		if (_year >= 1 && _month > 0 && _month < 13 && _day>0 && _day <= GetMonthDay(_year, _month))return true;
		return false;
	}
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		assert(is_DateValid());
	}
#if 0
	Date(const Date& d)///其实是不需要自己写的
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		cout << "调用了拷贝构造" << endl;
	}
#endif
	/// 为了后面方便看结果 -- 写一个Print()
	void Print() {
		cout << "日期为:" << this->_year << "/" << this->_month << "/" << this->_day << endl;
	}
	/// 运算符重载函数
	bool operator==(const Date& x2);
	bool operator!=(const Date& x2);
	bool operator<(const Date& x2);
	bool operator>(const Date& x2);
	bool operator<=(const Date& x2);
	bool operator>=(const Date& x2);
	//赋值（不需要自己写）
	//Date& operator=(const Date& d);
	//日期加天数
	Date& operator+=(int day);
	Date operator+(int day);
	//++ 面临的问题 -- 区分前置和后置
	//直接按特性重载，无法区分
	//特殊处理，使用重载区分，后置++重载增加一个参数int参数跟前置构成函数重载进行区分
	Date& operator++();///前置
	Date& operator++(int);///后置

	Date operator-(int day);
	Date& operator-=(int day);
	Date& operator--();
	Date& operator--(int);

	///还需要一个日期减日期
	int operator-(const Date& d);

	//输入和输出
#if 0
	void operator<<(ostream& out);
#endif
private:
	int _year;
	int _month;
	int _day;
};
//IO重载
#if 0
ostream& operator<<(ostream& out, const Date& d);
#endif
//因为这个函数会频繁的调用，所以弄成内联比较好
//同时内联不允许定义声明分离，所以直接全都写到.h里面比较好
inline ostream& operator<<(ostream& out, const Date& d) {
	out << d._year << "/" << d._month << "/" << d._day << endl;
	//但是放出来了 -- 访问不了私有的
	//1.写GetMonth()等函数
	//2.弄成公有
	//3.友元（可以让这个函数访问类的私有属性）
	return out;
	//返回值还是要带上，否则就不能用连续的同一行的<<了
}
//顺便把流提取也写了
inline istream& operator>>(istream& in,Date& d) {//不能加const，不然改不了了
	in >> d._year >> d._month >> d._day;
	assert(d.is_DateValid());
	return in;
}
//如果还需要给日期，算今天是周几的功能，也可以实现！
//先给定一个标准，然后有了日期减日期的功能之后，减一下，看看过了几个星期即可

/*
注意：
1.不能通过连接其他符号来创建新的操作符：比如operator@
2.重载操作符必须有一个类类型或者枚举类型的操作数
3.用于内置类型的操作符，其含义不能改变，例如：内置的整型+，不 能改变其含义
4.作为类成员的重载函数时，其形参看起来比操作数数目少1成员函数的（this指针的原因）
5.操作符有一个默认的形参this，限定为第一个形参
.* 、:: 、sizeof 、?: 、. 注意以上5个运算符不能重载。这个经常在笔试选择题中出现。 
*/