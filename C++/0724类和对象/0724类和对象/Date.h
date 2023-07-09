#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;



/// <summary>
/// 一个类到底可以重载多少运算符呢？ -- 看哪些运算符对这个类型有意义
/// </summary>
class Date
{
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
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
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
	
private:
	int _year;
	int _month;
	int _day;
};