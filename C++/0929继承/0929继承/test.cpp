#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

//学校人员管理系统
//不同类有很多重复的东西
//重复的东西可以提取出来，放到一个公共的类里面去
//这个类叫做父类，或者基类
//相对应的，子类/派生类
// -- 体现的是类设计定义层次的复用！
#if 0
class Person {
public:
	void Print() {
		cout << "name " << _name << endl;
		cout << "age " << _age << endl;
	}
protected:
	string _name = "peter";
	int _age = 18;
	//....
};
class Student :public Person {
protected:
	int _stuid;
};
class Teacher :public Person {
protected:
	int _jobid;
};
int main() {
	Student s;
	s.Print();
	return 0;
}
#endif

//C++ 继承方式和访问限定符
/*
* 继承方式
* 1.public继承
* 2.protected继承
* 3.private继承
*/
/*
* 访问限定符
* 1.public访问
* 2.protected访问
* 3.private访问
*/


//protected/private 类外面不能访问，类里面可以访问
//不可见   隐身 -- 外面里面都不可见

//私有成员的意义：不想被子类继承的成员，可以设计成私有

//在实际运用中一般都是使用public继承，几乎很少使用保护/私有继承
//而且private成员很少用，基本上没有什么不想让被继承的成员
//基类中想要给子类复用，但是又不想暴露直接访问的成员，就应该定义成保护

//class 默认是私有继承
//struct 默认是公有继承
//使用的时候最好显示写出来


//继承中的作用域
//父类中和子类中能不能定义同名变量？
//可以 -- 因为不在同一个类
//此时子类对象会有两个同名变量
//那访问子类的 -- 访问的是子类的
#if 0
class Person {
protected:
	string _name = "小李子";
	int _num = 111;
};
class Student :public Person {
public:
	void Print() {
		cout << "姓名:" << _name << endl;
		cout << "学号:" << _num << endl;
		cout << "学号:" << Person::_num << endl; //当然我可以指定类域
	}
protected:
	int _num = 999;
};
int main() {
	Student d1;
	d1.Print();
	return 0;
}
#endif
/*
* 子类和父类中有同名成员，子类成员将屏蔽父类对同名成员的直接访问，
* 这种情况叫隐藏，也叫重定义
*/
//建议不要定义重名成员


//以下程序两个func的关系是什么
//1.两个fun构成函数重载？ -- 不对，函数重载要求在同一作用域
//这两个func构成隐藏关系 -- 只需要函数名相同就构成隐藏

class A {
public:
	void fun() {
		cout << "func()" << endl;
	}
};
class B :public A {
public:
	void fun(int i) {
		cout << "func(int i)->" << i << endl;
	}
};
int main() {
	B b;
	b.fun(10);
	//b.fun();//err -- 隐藏了，调不动
	b.A::fun();//指定就行
	return 0;
}
//父类的不是拷贝到子类中的，是智能生成的