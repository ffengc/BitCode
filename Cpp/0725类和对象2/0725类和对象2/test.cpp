#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cassert>
using namespace std;

//const成员
//将const修饰的类成员函数称之为const成员函数，const修饰类成员函数，实际修饰该成员函数隐含的this
//指针，表明在该成员函数中不能对类的任何成员进行修改。
//一开始d2编不过的原因其实就是权限的放大
#if 0
class Date
{
public:
	Date() {}
	void Display()
	{
		cout << "Display ()" << endl;
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl << endl;
	}
	void Display()const
	{
		cout << "Display () const" << endl;
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl << endl;
	}
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};
void Test()
{
	Date d1;
	d1.Display();
	
	const Date d2;
	d2.Display();//不能权限的放大
}
int main() {
	Test();
	return 0;
}
#endif
//不用改变自己的函数都可以用const修饰
//记住 -- const修饰的是this指针 指向的内容 保证函数不会修改成员内部的变量
//另外 -- const对象和非const对象都可以调用这个成员函数



//取地址及const取地址操作符重载
#if 0
class A {
public:
	A* operator&() { //一个有const 一个没有 是可以重载的 -- 编译器会去找最匹配的那个
		return this;
	}
	const A* operator&()const {
		return this;
	}
private:
	int _year;
	int _month;
	int _day;
};
#endif
//但是有些时候，有const和没const的我们都要写，要构成重载才行
//比如取地址的重载，有const和没const的返回的东西是不一样的
//它们是默认成员函数，我们不写编译器会自动生成，自动生成就够用了，所以一般不用写
//特殊场景：不想让别人取到这个类型的地址 -- 那我们就自己写，返回空指针或者啥的就行，不返回this就行


//习题：求1+2+3+.....n
#if 0
class Sum {
public:
	Sum() {
		sum += i;
		i++;
	}
};
static int i = 0;
static int sum = 0;
class Solution {
public:
	int Sum_Solution(const int n) {
		Sum a[n];//调用n次Sum的构造函数
		return sum;
	}
};
#endif