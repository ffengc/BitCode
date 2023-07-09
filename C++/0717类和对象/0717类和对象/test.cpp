#define _CRT_SECURE_NO_WARNINGS 1
#include"person.h"

//类和对象
//域这个概念很重要
//生命周期和存储位置有关系

//类的实例化


// 这里需要指定PrintPersonInfo是属于Person这个类域
#if 0
int main() {
	cout << sizeof(Person) << endl;//没开空间怎么算大小？
	Person p1;//此时才开空间 -- 这才是类的实例化
	return 0;
}
#endif


//类的大小计算
#if 0
class A {
public:
	void PrintA() {
		cout << _a << endl;
	}
	void func() {
		cout << "void A::func()" << endl;
	}
	char _a;
};
int main() {
#if 0
	cout << sizeof(A) << endl;
	A aa1;
	A aa2;
	//这两个_a是不一样的_a
	aa1._a = 1;
	aa2._a = 2;
	//但是 -- 这两个函数是同一个
	aa1.PrintA();
	aa2.PrintA();
#endif
	//看一个题目
	A* ptr = nullptr;
	ptr->func();
	//崩溃？编译报错？正常运行？
	//正常运行，因为并没有解引用，成员函数并没有在类里面
	return 0;
}
#endif
//对象存储方式设计二：
//类函数表地址+类成员变量
//对象存储方式设计三：
//成员变量放到类里面，成员函数放到公共代码区
//编译链接时就根据函数名区公共代码区找到函数的地址，call函数的地址

//类的内存对齐规则和结构体一样
#if 0
class A2 {
public:
	void f2() {}
};
class A3{};
int main() {
	cout << sizeof(A2) << endl;
	cout << sizeof(A3) << endl;
	return 0;
}
#endif
//为什么不是0呢？
//没有成员变量的类对象，给1byte，占位，标识对象存在，不存储实际数据


//this指针
#if 0
class Date {
public:
	void Init(int year, int month, int day) {
		_year = year;
		_month = month;
		_day = day;//这就是为什么要加_
	}
	void Print() {
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main() {
	Date d1;
	d1.Init(2022, 7, 17);
	Date d2;
	d2.Init(2022, 7, 18);
	d1.Print();
	d2.Print();
	//问题来了，我们怎么区分打印的时候是d1还是d2呢
	//成员函数是公共区域的
	//引出一个概念this指针
	return 0;
}
#endif
//命名规范
//1.单词和单词之间首字母大写间隔 --驼峰法 GetYear
//2.单词全部小写，单词之间用_分割  get_year
// 
//课堂：驼峰法
//1.函数名、类名等所有单词首字母大写
//2.变量首字母小写，后面单词首字母大写
//3.成员变量首单词前面加_

//其实上面不是那样的，其实Init()有四个参数，Print()有一个，就是this指针
//当然这是编译器的处理方式，我们不能自己这样弄
//main()里面也会做相关的处理
#if 0
class Date {
public:
	//
	void Init(int year, int month, int day) {//
		cout << this << endl;
		this->_year = year;
		this->_month = month;
		this->_day = day;//这就是为什么要加_
	}
	void Print() {
		cout << this->_year << "-" << this->_month << "-" << this->_day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
/// <summary>
/// 其实被编译器处理过后是这个样子的 -- 而且自己写的时候不能自己加上（函数的括号里不能加上，内部是可以自己用的）
/// //但是我们类里面可以自己使用这个this
/// </summary>
/// <returns></returns>
/// 实参和形参那个位置不能显示传递和接受this指针
/// 但是可以在成员函数内内部使用
int main() {
	Date d1;
	d1.Init(2022, 7, 17);
	Date d2;
	d2.Init(2022, 7, 18);
	d1.Print();
	d2.Print();
	return 0;
}
#endif



//this指针的一些问题
// 1.下面程序能编译通过吗？
// 2.下面程序会崩溃吗？在哪里崩溃
#if 0
class A {
public:
	void PrintA()
	{
		cout << _a << endl;
		//没有这一句编译是可以通过的，但是如果要找_a就不行了，因为nullptr空指针并没有给_a开空间
		//_a是需要this指针解引用的，因为this是空，所以运行崩溃
	}
	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};
int main() {
	A* p = nullptr;
	p->PrintA();
	p->Show();
	return 0;
}
#endif
//this指针是存在哪的？
//堆 栈 静态区 常量区？
//一般是在栈里面 -- 因为它是一个形参
//但是也不一定，有些地方会进行优化，比如vs下面 -- 放到寄存器里了
//Linux可以把汇编调试出来看看




//成员函数
//类的6给默认成员函数
//一个类里面什么都没有，简称为空类
//其实编译器会自动生成6个默认成员函数
/*
* 1.构造函数：初始化工作
* 2.析构函数：清理工作
* 3.拷贝构造：是使用同类对象初始化创建对象
* 4.赋值重载：把一个对象赋值给另一个对象
* 5.6，取地址重载（了解一下，不重要）
*/


//构造函数
#if 0
class Date {
public:
	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
//调用类的时候，如果忘记初始化怎么办
//调用Init初始化，我们可能会忘记 -- 导致崩溃或者出现随机值
//能不能保证对象一定被初始化 -- 构造函数
int main()
{
	Date d1, d2;
	d1.SetDate(2018, 5, 1);
	d1.Display();

	Date d2;
	d2.SetDate(2018, 7, 1);
	d2.Display();
	return 0;
}
#endif
//构造函数特性：
/*构造函数不是用来定义对象的，是用来初始化函数的
1.函数名和类名相同
2.无返回值
3.对象实例化时编译自动调用对应的构造函数
4.构造函数可以重载*/
#if 0
class Date {
public:
	// 1.无参构造函数
	Date()
	{
		//...里面可以继续写东西，不写也可以
	}

	// 2.带参构造函数
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};
void TestDate()
{
	Date d1; // 调用无参构造函数
	Date d2(2015, 1, 1); // 调用带参的构造函数
	//这个也相当于创建一个Date类的同时，也把函数调了一下，但是注意，无参的时候不用()！！！！

	// 注意：如果通过无参构造函数创建对象时，对象后面不用跟括号，否则就成了函数声明
	// 以下代码的函数：声明了d3函数，该函数无参，返回一个日期类型的对象
	Date d3();
}
int main() {
	TestDate();
	return 0;
}
#endif
//构造函数不能以普通函数的定义和调用规则去理解
//也可以用全缺省去弄


//栈的构造函数
#if 0
typedef int Datatype;
class Stack {
public:
	Stack(int capacity = 4) {
		_array = (Datatype*)malloc(sizeof(Datatype) * capacity);
		if (nullptr == _array) {
			perror("malloc");
			exit(-1);
		}
		_size = 0;
		_capacity = capacity;
	}
	void Push(Datatype data) {

	}
	void Pop() {

	}
private:
	Datatype* _array;
	int _size;
	int _capacity;
};
int main() {
	Stack st;
	st.Push(0);
	st.Push(1);
	return 0;
}
#endif


//构造函数特性
//5.如果类中没有显式定义构造函数，则C++编译器会自动生成一个无参
//  构造函数，一旦用户显式定义，编译器将不再自动生成

//但是我们调试发现，默认生成的构造函数啥事没干
// 
// 
// 
//C++类型分类：
//1.内置类型：int/doulbe/char/pointer等
//2.自定义类型：struct/class
// 
// 
// 
//默认生成的构造函数
//a.内置类型成员不做处理
//b.自定义类型成员回去调用他的默认构造函数
typedef int Datatype;
class Stack {
public:
	//Stack() {}
	Stack(int capacity = 4) {//这里如果不写 =4 下面MyQueue就调不动这里的函数了，或者再弄一个重载Stack
		_array = (Datatype*)malloc(sizeof(Datatype) * capacity);
		if (nullptr == _array) {
			perror("malloc");
			exit(-1);
		}
		_size = 0;
		_capacity = capacity;
	}
	void Push(Datatype data) {

	}
	void Pop() {

	}
private:
	Datatype* _array;
	int _size;
	int _capacity;
};
class MyQueue {
private:
	Stack _st1;
	Stack _st2;
};
int main() {
	MyQueue q;
	//我们的MyQueue虽然没有写构造函数，但是因为Stack是自定义类型，所以还是会被初始化，因为会去调用Stack的构造函数了
	//这其实是C++设计时候的一个缺陷，这个默认构造函数本来应该把内置类型也一起处理的
	return 0;
}

//默认构造函数
//1.我们不写，编译器自动生成那个
//2.我们自己写的，全缺省构造函数
//3.我们自己写的，无参构造函数
//这三个都叫默认构造