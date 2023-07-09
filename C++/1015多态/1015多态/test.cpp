#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

#elif
#endif

//多态
//多态的条件是虚函数


#if 0
class Person {
public:
	virtual void BuyTicket() { //只用成员函数才能加virtual
		cout << "买票 - 全价" << endl;
	}
};
class Student : public Person {
public:
	//虚函数的重写的条件 -- 要求三同 + 虚函数
	//要求：函数名参数返回值都要相同
	//不符合重写才叫隐藏
	virtual void BuyTicket() { cout << "买票 - 半价" << endl; }
};
class Soldier : public Person {
public:
	virtual void BuyTicket() {
		cout << "买票 - 优先买票" << endl;
	}
};

//多态的两个条件
//1.虚函数的重写
//2.父类指针或者引用去调用虚函数

void Func(Person& p) {
	p.BuyTicket();
	//如果按照以前学的知识 -- 这里肯定是去调用Person的函数
	//但是这里构成了多态 -- 这个时候就和p的类型就没有关系了
	//如果破坏多态的条件呢？
	//1.Peson& p --> Person p -- 构不成多态
	//2.父类的virtual去掉 -- 构不成多态
	//这里有个特例 -- C++的坑：把子类的virtual去掉，也还可以构成多态
	//因为cpp子类把父类的函数继承下来重写的是接口继承，重写实现，还是认为它是virtual -- 接口继承（往下看）
	//特例1：子类虚函数不加virtual依旧构成重写（依旧构成重写）
	//特例2：重写的协变
	//	返回值可以不同，要求必须是父子关系的指针或者引用
	//  见下面例子
}
int main() {
	Person ps;
	Student st;
	Soldier sd;
	Func(ps);
	Func(st);
	Func(sd);
	return 0;
}
#endif


//特例2：构成协变
#if 0
class A {};
class B : public A {};
class Person {
public:
	virtual A* BuyTicket() { //当然构成父子关系的指针或者引用不一定是自己的，是别人的也可以
		cout << "买票 - 全价" << endl;
		return nullptr;
	}
};
class Student : public Person {
public:
	virtual B* BuyTicket() { //这里的返回值的辈分要比上面的低才行，一样就不用说了，返回值一样就不是协变了，满足原始的重写条件
		//只能上面返回A* 下面B* 不能反过来
		cout << "买票 - 半价" << endl; 
		return nullptr;
	}
};
void Func(Person& p) {
	p.BuyTicket();
}
int main() {
	Person ps;
	Student st;
	Func(ps);
	Func(st);
	return 0;
}
#endif



// ===================================== 经典题目 ===================================== //

//题目：一下程序输出结果是什么
#if 0
class A{
public:
	virtual void func(int val = 1) {
		cout << "A->" << val << endl;
	}
	virtual void test() { func(); }
};
class B :public A {
public:
	void func(int val = 0) {
		cout << "B->" << val << endl;
	}
};
int main() {
	B* p = new B;
	p->test();
	return 0;
}
#endif
// 这道题可以号称“杀手题”
//首先调用test() -- 肯定是没有多态的，虚函数如果没有满足重写条件当作普通函数处理
//首先调用test() -- 需要传p的指针 -- 类型为A* 
//即 this->func(); -- 符合多态的条件
//首先这题容易看错的地方：
//1.B里面的func不加virtual依旧可以构成重写！ -- 所以B的func是虚函数
//2.虚函数重写是接口继承
//  普通函数继承是实现继承
//也就是说，在B中func是把A的整个架子拿下来，而不是只拿实现
//所以B中的函数其实用的是这个架子 virtual void func(int val = 1) 而不是 void func(int val = 0)
// 
//					接口继承！ +  重写实现！
//所以打印的val是1
//在公司里面千万不要写出这样的代码，写这样的代码就是找打


// ===================================== 经典题目 ===================================== //
// 如果这样写呢？ A->1? or B->1?
#if 0
class A {
public:
	virtual void func(int val) {
		cout << "A->" << val << endl;
	}
	void test() { func(1); } //这里加不加virtual没有区别，因为根本就没有重写func
	//		this->func(1)  this是A* 可以触发多态
	//		调A的func还是B的func -- 和this的类型有关系吗？ -- 没有关系
	//		this指向谁就调谁，A*p = new B;  指向的是B -- 所有调用B的
};
class B :public A {
public:
	void func(int val) {
		cout << "B->" << val << endl;
	}
};
int main() {
	A* p = new B;
	p->test();
	return 0;
}
#endif


// ====================================== 多态的原理 ======================================
//sizeof的结果是什么
#if 0
class Base{
public:
	virtual void Func1() {
		cout << "Func1()" << endl;
	}
private:
	int _b = 1;
	//char _ch = 'A';//加上这个这个题更有迷惑性
};
int main(){
	cout << sizeof(Base) << endl;
	//这里考察不是内存对齐 -- 考察的是多态
	Base b;
	//多态这里会多一个虚表指针！
	//虚函数会进入虚表 -- 如果我们增加几个函数看看会怎么样
	return 0;
}
#endif

///虚函数会进入虚表 -- 如果我们增加几个函数看看会怎么样
///virtual function table
#if 0
class Base {
public:
	virtual void Func1() {
		cout << "Func1()" << endl;
	}
	virtual void Func2() {
		cout << "Func1()" << endl;
	}
	virtual void Func3() {
		cout << "Func1()" << endl;
	}
private:
	int _b = 1;
};
int main() {
	cout << sizeof(Base) << endl;
	//这里考察不是内存对齐 -- 考察的是多态
	Base b;
	return 0;
}
#endif


//多态的原理
class Person {
public:
	virtual void BuyTicket() { //只用成员函数才能加virtual
		cout << "买票 - 全价" << endl;
	}
	virtual void test() {} //有两个虚函数 -- 只有一个完成了重写
	int _a = 10;
};
class Student :public Person {
public:
	virtual void BuyTicket() {
		cout << "买票 - 半价" << endl;
	}
	int _b = 20;
};
void Func(Person& p) {
	//构成多态之后
	//到底怎么知道去找哪一个函数调用
	//虚表里面已经有函数指针了！

	//即使我们切了片
	//我们看到的只有父类对象
	//但是我们在子类里面看到的父类部分里面的虚表地址，已经被覆盖过了！，所以切了片，多态一样能够被触发！
	p.BuyTicket();
}
int main(){
	Person Mike;
	Func(Mike);
	Student Johnson;
	Func(Johnson);
	return 0;
}
//多态：
//虚函数会存进虚表！
//对象里面有没有虚表？ -- 没有，只有虚表的指针！
//虚表的本质是一个函数指针的数组

//打断点运行我们可以发现
//Mike里面的虚表和Johnson里面的虚表不完全一样！ -- 但是它们的地址挨得很近
//我们可以发现 BuyTicket()的地址是不同的
//test()的地址是相同的
//为什么？
//因为BuyTicket()完成了重写
//相当于把Mike里面指向的虚表拷贝一份下来，然后把重写的函数的函数指针覆盖上去

//加了virtual如果不构成多态，虽然虚表里面有，但是在汇编代码上体现和普通函数没有区别，不会去虚表里面找地址
//只有触发了多态 -- 程序运行的时候才会去找地址


// ======================================== 总结 ======================================== //

//总结：多态的本质原理，符合多态的两个条件
//那么调用时，会到指向对象的虚表中找到相对应的虚函数的地址，进行调用

//多态的调用：<程序运行时>去指向对象的虚表中找到函数的地址，进行调用
//普通函数的调用：<编译链接时>确定函数的地址（在符号表里面找），运行时直接调用