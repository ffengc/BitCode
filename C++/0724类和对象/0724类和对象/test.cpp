#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
#include"Date.h"
//理解构造和析构
#if 0
class A {
public:
	A(int a = 0) {
		_a = a;
		cout << "A()" << a << endl;
	}
	~A() {
		cout << "~A()" << _a << endl;
	}
private:
	int _a;
};
A aa3(3);
//顺序考察1
#if 0
int main() {
	///问题来了，谁先析构
	///先定义的后析构，后定义的先析构！！！
	/// 是因为的栈的性质决定的
	static A aa0(0);
	A aa1(1);
	A aa2(2);
	static A aa4(4);
	///现在有1，2，3，4 四个A类被创建，它们创建和销毁的顺序是什么样的呢

	/// 析构顺序：
	/// 2，1，4，0，3
	/// 1，2是在清理栈帧的时候被清理的 -- 先2后1的原因是栈的性质
	/// 局部静态的也是符合先定义后析构
	return 0;
}
#endif
//顺序考察2
void f() {
	static A aa0(0);
	A aa1(1);
	A aa2(2);
	static A aa4(4);
}
int main() {
	f();
	f();
	//顺序
	//3，0，1，2，4，~2，~1，1，2，~2，~1，~4，~0，~3 
	///这个顺序好好好复习
	return 0;
}
#endif


//理解拷贝构造
#if 0
class A {
public:
	A(int a = 0) {
		_a = a;
		cout << "构造函数调用" << a << endl;
	}
	A(const A& aa) {
		_a = aa._a;
		cout << "拷贝构造调用" << aa._a << endl;
	}
	~A() {
		cout << "析构函数调用" << _a << endl;
	}
private:
	int _a;
};
void func1(A aa) {

}
void func2(A& aa) {

}
A func3() {
	static A aa(3);
	///这里要注意，传值返回其实是需要拷贝一份的，所以拷贝构造会被调用
	return aa;
}
A& func4() {
	static A aa(4);///这里一定要是static才传引用返回
	//这里是不需要拷贝的
	return aa;
}
int main() {
	//A aa1(1);
	//A aa2(aa1);
	//func1(aa1);
	func3();
	cout << endl;
	func4();
	return 0;
}
#endif

void TestDate1() {
	Date d1(2022, 7, 24);
	Date d2(d1);//拷贝构造

	Date d3(2022, 8, 24);
	//d1 = d3;///赋值
	//d1.Print();
	///但是现在这个赋值是有问题的，不支持连续赋值，所以不能返回void，要返回Date类型才能连续调用
	///相当于链式访问
	d2 = d1 = d3;
	cout << endl;
	d2.Print();
	d3.Print();
	d1.Print();
	///其实我们可以自己试一下，把那个赋值重载改成传值返回，我们会发现调用了很多次拷贝构造
	///所以我们的传引用返回，能用就用！
	///问题来了，有没有人会去写这样的代码？d2=d2
	///这样写语法是通过的，但是我们在重载函数里面识别一下吧，这种情况不折腾了，直接跳出来
}
void TestDate2() {
	///测试比较重载
	Date d1(2022, 7, 24);
	Date d2(2023, 7, 24);
	cout << (d2 > d1) << endl;
}
void TestDate3() {
	Date d1(2022, 7, 24);
	d1 += 100;
	d1.Print();
	Date d2 = d1 + 100;
	d1.Print();
	d2.Print();
}
void TestDate4() {
	Date d1(2022, 7, 24);
	Date ans1 = d1++;//d1.operator++(&d1)
	Date ans2 = ++d1;//d1.operator++(&d1,0)
	ans1.Print();
	ans2.Print();
}
int main() {
	//TestDate1();
	//TestDate2();
	//TestDate3();
	TestDate4();
	return 0;
}
///关于赋值重载函数
///这个函数和别的重载有一个差别，这个赋值重载只能写在类里面
///因为如果这个函数不显式写，编译器会自动生成
///如果写在外面，这两个就冲突了
///但其实，我们发现，日期类其实没有必要自己写赋值重载，用编译器自动生成的就行
///那么什么类需要自己写赋值重载呢？
///这个和拷贝构造的特性是一样的
///像Stack那些类，是需要写的 -- 因为编译器默认生成的是浅拷贝！
///st1，st2指向同一块空间，析构的时候会被析构两次 -- 要实现深拷贝才行
///MyQueue类也是不用写的，它里面的Stack类写好就行！
/// 
/// 
/// 
/// 一些类需要显式写拷贝和赋值：比如Stack，Queue
/// 一些类不需要自己写拷贝和赋值 a.Date这样的类，默认生成就会完成值拷贝/浅拷贝
///                              b.MyQueue这样的类，默认生成的回去调用他自定义类型成员Stack的拷贝和赋值