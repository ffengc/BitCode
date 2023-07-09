#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;

#elif
#endif


//上节课内容复习
//多态调用 -- 运行时决议
//运行时，到指向对象虚表中找调用虚函数地址  






//新内容

//析构函数加virtual
//建议在继承中析构函数定义成虚函数
#if 0
class Person {
public:
	virtual ~Person() {
		cout << "~Person()" << endl;
	}
};
class Student :public Person {
public:
	virtual ~Student() {
		cout << "~Student()" << endl;
	}
};
int main() {
	//这里会完成重写
	//析构函数名会被处理成destructor，所以这里完成了虚构函数完成虚函数重写
#if 0
	Person p;
	Student s;//普通场景和我们原来的理解是没有区别的，先析构子类，再父类
#endif

	Person* ptr1 = new Person;
	delete ptr1;

	Person* ptr2 = new Student;
	delete ptr2;
	/**
	 * 这里我们会发现，如果不加virtual 结果是两个Person的析构.
	 * 这个是不对的 -- 我创建的是一个子类对象，却调用了父类的析构
	 * 为什么？因为调用的时候是这样调用的
	 * ptr2->destructor()
	 * operator delete(ptr2) 
	 * 如果不加virtual 不符合多态条件 -- 按ptr2类型去调用析构 -- 所以调的是~Person()
	 * 但是我们想call的不是~Person()，我们想call的是~Student()
	 */
	//我们希望指针指向父类调父类的，指向子类调子类的，而不是取决于指针类型
	return 0;
}
#endif



//C++11的final和override
#if 0
class Car
{
public:
	virtual void Drive() final {}
};
class Benz :public Car
{
public:
	virtual void Drive() { cout << "Benz-舒适" << endl; } //err无法重写Drive
};
int main(){

	return 0;
}
#endif


//override: 检查派生类虚函数是否重写了基类某个虚函数，如果没有重写编译报错。
#if 0
class Car {
public:
	virtual void Drive() {}
};
class Benz :public Car {
public:
	virtual void Drive() override { cout << "Benz-舒适" << endl; }
};
int main() {
	return 0;
}
#endif


/** 重载、重写和隐藏的对比 */
//见课件


//抽象类
//包含纯虚函数的类叫做抽象类（接口类）
/*在虚函数的后面写上 =0 ，则这个函数为纯虚函数。包含纯虚函数的类叫做抽象类（也叫接口类），抽象类
不能实例化出对象。派生类继承后也不能实例化出对象，只有重写纯虚函数，派生类才能实例化出对象。
纯虚函数规范了派生类必须重写，另外纯虚函数更体现出了接口继承。*/
class Car
{
public:
	virtual void Drive() = 0; //不用写实现，写了也没人去调
};
class Benz :public Car
{
public:
	virtual void Drive()
	{
		cout << "Benz-舒适" << endl;
	}
};
class BMW :public Car
{
public:
	virtual void Drive()
	{
		cout << "BMW-操控" << endl;
	}
};
void Test()
{
	Car* pBenz = new Benz;
	pBenz->Drive();
	Car* pBMW = new BMW;
	pBMW->Drive();
}




//多态的原理
#if 0
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
	virtual void func1() {
		cout << "func1()" << endl;
	}
}; 
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
	virtual void func2() {
		cout << "func2()" << endl;
	}; //vs监视窗口很奇怪,虚表里面看不见这个函数 -- 其实是要进虚表的
};

typedef void(*VFPTR)();//typedef一下这个类型
void print_vfttable(VFPTR* table, int n) {
	//传进来的是函数指针数组
	//在vs下虚函数表最后一个元素后面会放一个空指针，Linux下不一定
	//所以Linux下这里只能写死，知道有几个虚函数就循环几次
	//vs下我们可以不写死
	//for (size_t i = 0; *(table + i) != nullptr; ++i) {
	for (size_t i = 0; i < n; ++i) {
		printf("vft[%d]:%p->", i, table[i]);//这样我们可以把地址都打印出来
		table[i]();//虚函数的地址加一个() -- 调用函数
	}
}//写好了这个函数之后 -- 还有最后一步 -- 如何得到虚函数表的地址
//虚函数表地址在对象地址的头4个/8个字节上


int main() {
	//同一个类型的对象共用一个虚表
	Person p1;
	Person p2;
	//p1,p2是共用虚表还是各用各的？ -- 肯定是共用的

	//Person和Student的肯定不是同一个 -- 内容都不一样
	Student s1;
	Student s2;

	//如果我没有完成重写，是同一个虚表吗？ -- 我们发现不是！
	//vs下 不管是否完成重写，子类虚表跟父类虚表都不是同一个

	//vs的监视有问题，我们在虚函数表里面看不见func(),那我们可以通过什么方法看呢？
	//1.内存可以看
	//2.我们写一个函数来打印虚函数表

	//这种访问方式，私有的也能访问，因为这已经不算是正常的访问方式了
	//现在要取虚函数表的地址
	//32位下现在取头四个字节 -- 强转成int -- 再解引用
#define __SIZEOF_POINTER__ 4
#if __SIZEOF_POINTER__ == 4
	print_vfttable((VFPTR*)*(int*)&s1, 3);
	cout << endl;
	print_vfttable((VFPTR*)*(int*)&p1, 2);
	//为什么强转成int* 之后还要解引用 -- 因为我们不是要对象头部的地址，而是要对象头部地址《所指向》的四个字节！
#elif __SIZEOF_POINTER__ == 8
	print_vfttable((VFPTR*)*(double*)&s1);
#endif
	//其实这种调用很bug
	//在print_vfttable()函数里面调用函数，调用类的函数，没用到this，也没用到对象的指针，这已经不是常规的调用方式了
	void(*ptr)();
	return 0;
}
#endif


//多继承
#if 0
class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1 = 1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2 = 2;
};
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; } //func2()没有重写
private:
	int d1;
};
typedef void(*VFPTR) ();
void PrintVTable(VFPTR vTable[])
{
	cout << " 虚表地址>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Derive d;
	//cout << sizeof(d) << endl; //20
	/**
	 * Base1的大小是8.
	 * Base2的大小也是8
	 * 再放个d1 -- 大小是4
	 * 所以最后是20
	 */
	/**
	 * 前面的没问题，d里面有两张虚表 -- 分别是Base1和Base2的
	 * 两个虚表指针指向的虚表里面都只有两个函数指针，
	 * 一个是fun1()的一个是func2()的.
	 * 
	 * 那d的func3()在哪呢？
	 * 放到Base1里面？Base2里面？还是别的地方？
	 * 我们打印出来看下
	 * \return 
	 */

	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
	PrintVTable(vTableb1);
	cout << endl;
	/** 方法1 */
	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));//这里找第二个虚表的地址的方法要注意
	/** 方法2 -- 切片*/
	Base2* ptr2 = &d;//切片的时候会自动偏移
	PrintVTable(vTableb2);//所以这里传ptr2和vTableb2也可以\

	//此时我们又有了新发现 -- 我们发现d继承了Base1和Base2的func1()并完成重写之后
	//在虚表里面Base1和Base2的func1()的地址却是不一样的
	//这个很奇怪，我只重写成了一个func1()，但地址在两个虚表里面不同 -- 为什么？

	//这涉及到指针偏移的问题 -- 虽然函数地址不同 -- 但是最后还是调用到了同一个函数 -- 调用到了func1()

	//这里是符合多态的 -- 会在虚表中找
	Base1* ptr1 = &d;
	ptr1->func1();
	Base2* ptr2 = &d;
	ptr2->func1();
	//在vs环境中 -- 不只是虚函数地址 -- 所有函数的地址其实都不是真正push栈帧的地址
	//而是包多了一层
	//通过汇编我们可以看到 -- vs下调用函数的时候，调用函数的地址其实是一个jmp指令的地址
	//jmp到真正的函数地址之后 -- 才开始push栈帧
	//至于vs为什么这样设计 -- 不知道？ gcc下是什么样的？可以研究一下

	//在ptr2->func1()中调用jmp的时候
	//并不是jmp过去就是函数地址了
	//它还多做了一件事情
	//ecx减了一个8               -----------------   这个就是关键！！！ --- 为什么减8 ---就是把ptr2弄回ptr1上的位置上
	//学过了与对象我们知道ecx存的是this指针
	return 0;
}
#endif




//多态收尾
//菱形继承
#if 0
class A{
public:
	int _a;
public:
	virtual void fun1() {
		cout << "A::func1()" << endl;
	}
};
//class B : public A {
class B :virtual public A {
public:
	int _b;
	virtual void fun1() {
		cout << "B::func1()" << endl;
	}
};
//class C : public A {
class C: virtual public A{
public:
	int _c;
	virtual void fun1() {
		cout << "C::func1()" << endl;
	}
};
class D :public B, public C {
public:
	int _d;
	virtual void fun1() {
		cout << "D::func1()" << endl;
	}
};
//我们给A加上一个虚函数func1()
//B,C都完成一次重写
//我们发现编译会报错
//	error C2250: “D”:“void A::fun1(void)”的不明确继承
//为什么？
//其实问题出现在D上，把D屏蔽掉就没事了
//如果不是虚继承 -- D中应该会有两个虚表
//但是现在是虚拟继承了 -- D中只有一个A的虚表
//所以语法要求 -- D必须重写
int main() {
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}
#endif

/** ======================================= 重点 ======================================= */
//要掌握这些
/**
 * 语法：
 * 1.重写的概念和条件
 * 2.多态的概念及条件
 * 
 * 原理：
 * 1.虚表是什么？
 * 2.多态的原理是什么？
 * 3.普通调用，编译时决议和堕胎调用，运行时决议的区别是什么.
 */





/** ================================== 选择题 ================================== */
//求输出结果
class A {
public:
	A(const char* s) { cout << s << endl; }
	~A() {}
};
class B :virtual public A
{
public:
	B(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
};
class C :virtual public A
{
public:
	C(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
};
class D :public B, public C
{
public:
	D(const char* s1, const char* s2, const char* s3, const char* s4) :B(s1, s2), C(s1, s3), A(s1)
	{
		cout << s4 << endl;
	}
};
//A的构造会不会重复调用？
//按声明顺序而不是初始化列表的顺序 -- 所以顺序是ABCD
int main() {
	D* p = new D("class A", "class B", "class C", "class D");
	delete p;
	return 0;
}


/** ============================================== 问答题 ============================================== */
//1.内联函数可不可以是虚函数？
	//inline只是一个建议型的关键字 -- 理论上不能 -- 因为内联函数没有地址，虚函数需要地址放到虚表
	//inline只是提建议 -- 所以编译是可以通过的 -- 实际上它没有内联 -- 多态调用中，inline失效
//2.static函数可以是虚函数吗？
	//不可以！static函数没有this指针 -- 可以A::Func()这样去调用
	//而虚函数是为了实现多态 -- 而静态成员函数是在编译时决议的
//3.构造函数可以是虚函数吗？
	//不可以！
	//虚表是什么时候初始化的？ -- 在初始化列表阶段初始化的
//4.析构函数可以是虚函数吗？
	//可以，建议基类的析构定义成虚的
//5.拷贝构造和赋值可以是虚函数吗？
	//拷贝构造不可以！ -- 拷贝构造也是构造
	//赋值可以！语法上可以。赋值搞成多态有没有意义，除了可以完成父类赋值给子类 -- 但是这样没意义
//6.虚函数快还是普通函数快
	//如果多态调用 -- 普通快，否则一样快
//7.虚表地址在哪个区
	//我们可以看虚表地址和哪些类型的变量挨得近 -- 就可判断了
	//编译阶段生成 -- 存在代码段（常量区）
//面试 -- 校招前 -- 这些都要复习！