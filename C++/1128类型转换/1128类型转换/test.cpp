
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif
#include<algorithm>
#include<unordered_map>
#include<set>
#include<vector>
#include<iostream>
using namespace std;


//C++类型转换分成两种
//隐式类型转换和显式类型转换
#if 0
void Test()
{
	int i = 1;
	//隐式类型转换
	double d = i;
	printf("%d, %.2f\n", i, d);
	int* p = &i;
	// 显示的强制类型转换
	int address = (int)p;
	printf("%x, %d\n", p, address);
}
int main()
{
	Test();
	return 0;
}
#endif
//C语言
//意义相近的类型，允许相近的类型
//在操作符的两边有时候一会发生隐式类型转换
//所以在写C语言的时候我们一定要注意类型



/*
	标准C++为了加强类型转换的可视性，引入了四种命名的强制类型转换操作符：
	static_cast、reinterpret_cast、const_cast、dynamic_cast
*/

//static_cast用于非多态类型的转换（静态转换），编译器隐式执行的任何类型转换都可用static_cast，但它
//不能用于两个不相关的类型进行转换
//用于意义相近的类型
#if 0
int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);
	cout << a << endl;
	//不是相近的类型是转不了的
	/*int* pa = nullptr;
	int aa = static_cast<int>(pa);*/
	return 0;
}
#endif

#include<vector>
//reinterpret_cast
//reinterpret_cast操作符通常为操作数的位模式提供较低层次的重新解释，用于将一种类型转换为另一种不
//同的类型
#if 0
typedef void (*FUNC)();
//typedef vector<int> FUNC;
int DoSomething(int i)
{
	cout << "DoSomething" << endl;
	return 0;
}
void Test()
{
	// reinterpret_cast可以编译器以FUNC的定义方式去看待DoSomething函数
	// 所以非常的BUG，下面转换函数指针的代码是不可移植的，所以不建议这样用
	// C++不保证所有的函数指针都被一样的使用，所以这样用有时会产生不确定的结果
	FUNC f = reinterpret_cast<FUNC>(DoSomething);
	f();
}
int main()
{
	Test();
	return 0;
}
#endif


//const_cast
//const_cast最常用的用途就是删除变量的const属性，方便赋值
#if 0
void Test()
{
	const int a = 2;
	int* p = const_cast<int*>(&a);
	//int* p = &a;//编不过
	*p = 3;
	cout << a << endl;//2
	const int* pa = &a;
	cout << *pa << endl;//3 这次是直接通过内存访问的，所以是3
	cout << *p << endl;//3
	//C++的const修饰不是常量，没有存到静态区去，它是常变量 -- 在栈上
	
	//其实通过调试我们可以发现 ， *p = 3;之后，&a，也就是p指向的数据已经改成3了
	//那为什么打印的还是2？
	//这是因为编译器的优化
	//const修饰的变量 -- 会被编译器认为，不会被修改，所以编译器会放到寄存器这些地方
	//因为每次用都要去内存取太麻烦了
	//所以内存中改成3了，寄存器不知道
	//有些编译器也直接不搞寄存器（比如VS）
	//我们看vs下面的汇编就知道，cout函数call之后push参数，push的不是a是2
	//所以vs做了一个类似#define这样的宏替换的操作，所以后面即使内存中改了，也没用
}
void Test2()
{
	//还有一种方式可以不让编译器去优化这个const
	//关键字volatile
	volatile const int a = 2;
	int* p = const_cast<int*>(&a);
	//当然，我们还用C语言那一套也是可以的，直接强转
	//int * p = (int*)(&a);
	*p = 3;
	cout << a << endl;//3
	cout << *p << endl;//3
	
	//虽然C++还是兼容C的，可以用
	//但是不建议去用，建议用更规范的！
}
int main()
{
	//Test();
	Test2();
	return 0;
}
#endif

//static_cast(隐式类型转换)
//reinterpret_cast和const_cast(强转)


//dynamic_cast C++增加的
/*
dynamic_cast用于将一个父类对象的指针/引用转换为子类对象的指针或引用(动态转换)
向上转型：子类对象指针/引用->父类指针/引用(不需要转换，赋值兼容规则) 向下转型：父类对象指针/引用-
>子类指针/引用(用dynamic_cast转型是安全的)
注意： 1. dynamic_cast只能用于含有虚函数的类 2. dynamic_cast会先检查是否能转换成功，能成功则转
换，不能则返回0
*/

//此时我们要记得
//在类型转换中，无论是不规范的转，还是规范的转，都会产生临时变量的（具有常性）
//复习
#if 0
int main()
{
	int i = 10;
	double d = 2.0;
	double d = i;//可以转，但是会出现临时变量 i->tmp->d
	//所以
	//double& d = i;//err 
	//double& d = static_cast<double>(i);//err 
	//不是因为d不能引用i，而是因为这句话不是d引用i，是d引用临时变量，临时变量具有常性
	const double& d = i;
	return 0;
}
#endif

//注意，继承里面的向上转换不属于类型转换
//因为它不会出现临时变量
#if 0
class A
{
protected:
	int _a = 0;
public:
	virtual void f()
	{
		cout << "A::f()" << endl;
	}
};
class B :public A
{
protected:
	int _b = 1;
public:
	void f()
	{
		cout << "B::f()" << endl;
	}
};
#if 0
int main()
{
	A aa;
	B bb;
	A aa1 = bb;//没有发生类型转换,这里叫切片
	//因此
	A& ra1 = bb;//如果产生了临时变量，这里是编不过的
	//但是这里可以
	//如果我们把继承关系去掉，就编不过了

	//所以：继承里面的向上转换不属于类型转换
	return 0;
}
#endif
#if 0
int main()
{
	//1.父类对象无论如何都不能转子类的
	A aa;
	//B bb = (B)aa;//err
	//B bb = dynamic_cast<B>(aa);//err
	//无论如何都转不了

	//2.指针呢？引用呢？ -- 允许
	return 0;
}
#endif
void fun(A* pa)
{
	// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);
	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}
/*
注意 强制类型转换关闭或挂起了正常的类型检查，每次使用强制类型转换前，程序员应该仔细考虑是否还有
其他不同的方法达到同一目的，如果非强制类型转换不可，则应限制强制转换值的作用域，以减少发生错误
的机会。强烈建议：避免使用强制类型转换
*/
int main()
{
	A a;
	B b;
	fun(&a);
	fun(&b);
	return 0;
}
#endif


//下面我们来看一下这个问题的一个延申问题
class A1
{
public:
	virtual void f() {}
public:
	int _a1 = 0;
};
class A2
{
public:
	virtual void f() {}
public:
	int _a2 = 0;
};
class B :public A1, public A2
{
public:
	int _b = 0;
public:
	virtual void f() {}
};
int main()
{
	B bb;
	A1* ptr1 = &bb;
	A2* ptr2 = &bb;
	//这里两个指针肯定是不一样的
	cout << "&bb  " << &bb << endl << "ptr1 " << ptr1 << endl << "ptr2 " << ptr2 << endl;
	//B里面有A1，也有A2，A1的地址和B地址一样，A2会偏移

	//现在父类转子类，如果直接按照老方式的强转
	B* pb1 = (B*)ptr1;
	B* pb2 = (B*)ptr2;
	cout << endl << pb1 << endl << pb2 << endl;//我们发现这里是一样的

	B* pb3 = dynamic_cast<B*>(ptr1);
	B* pb4 = dynamic_cast<B*>(ptr2);
	cout << endl << pb3 << endl << pb4 << endl;//我们发现这里是一样的

	//我们直觉认为，如果直接强转，不会帮我们把pb1偏移回去，其实是会的！

	//如果要说区别，可能在于，如果不加虚函数，dynamic_cast就用不成了
	return 0;
}


//C++要注意的两个概念
//RAII
//RTTI -- 运行时类型识别
//	typeid/dynamic_cast/decltype
//typeid 获取对象类型字符串
//dynamic_cast运算符 弗雷德指针指向父类对象，还是子类对象？
//decltype 推导一个对象类型，可以用来定义另一个对象