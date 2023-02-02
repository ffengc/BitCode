#define _CRT_SECURE_NO_WARNINGS 1
#include"Date.h"

/// 运算符重载函数
///任何一个类，只需要写一个>和==即可，其它全部复用即可！
bool Date::operator==(const Date& x2) {
	return this->_year == x2._year
		&& this->_month == x2._month
		&& this->_day == x2._day;
}
bool Date::operator!=(const Date& d) {
	return !(*this == d);//复用就行
}
bool Date::operator<(const Date& d) {
	return !(*this >= d);//小于就是大于等于的否
}
bool Date::operator>(const Date& d) {
	if (_year > d._year)return true;
	else if (_year == d._year && _month > d._month)return true;
	else if (_year == d._year && _month == d._month && _day > d._day)return true;
	else return false;
}
bool Date::operator<=(const Date& d) {
	return !(*this > d);
}
bool Date::operator>=(const Date& d) {
	return (*this == d) || (*this > d);
}
Date& Date::operator+=(int day) {
	//先判断day是正的还是负的
	if (day < 0) {
		return *this -= -day;
	}

	//逻辑：先直接加再说，加完再判断日期的合法性 -- 当然，我们还需要知道每个月多少天，是不是闰年 
	//当然这些都很easy
	_day += day;
	//判断是否合法，当然，可以写一个is_Valid()去判断
	while (_day > GetMonthDay(_year, _month)) {
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13) {
			_month = 1;
			_year++;
		}
	}
	/// 现在的问题是？_year这些东西，是改了谁的？是this的，所以我们返回*this
	return *this;
	///能不能引用返回？ -- 出了函数，*this还在吗，还在，所以返回引用
}
Date Date::operator+(int day) {
	//自己是不改变的！ -- 创建一个局部对象即可
	Date ret(*this);
	//Date ret=*this 这里是拷贝构造，不是赋值，因为ret还没被初始化，如果ret=*this这里才是赋值
	ret += day;
	return ret;
	///出了这个函数，ret不在了，所以不能引用返回
}
Date& Date::operator++() {
	///前置
	*this += 1;
	return *this;//出了作用域还在 -- 引用返回
}
Date& Date::operator++(int) {
	///后置
	Date tmp(*this);
	*this += 1;
	return tmp;
}
Date Date::operator-(int day) {
	Date ret = *this;//拷贝构造
	ret -= day;
	return ret;
}
Date& Date::operator-=(int day) {
	if (day < 0) {
		return *this += -day;
	}
	_day -= day;
	while (_day <= 0) {
		--_month;
		if (_month == 0) {
			--_year;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
Date& Date::operator--() {//前置
	*this -= 1;
	return *this;
}
Date& Date::operator--(int) {//后置
	Date tmp(*this);
	*this -= 1;
	return tmp;
}
int Date::operator-(const Date& d) {
	///日期相减
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (*this < d) {
		max = d;
		min = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max) {
		++min;
		++n;
	}
	return n * flag;
}
//输入和输出：重要！
#if 0
void Date::operator<<(ostream& out) {
	out << _year << "/" << _month << "/" << _day << endl;
}
#endif