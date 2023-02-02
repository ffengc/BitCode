#define _CRT_SECURE_NO_WARNINGS 1
//0709_bit_Cpp_introduction2

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

//返回引用 -- 可以修改返回的对象

//传值返回和传引用返回的性能对比
#if 0
#include <ctime>
struct A { int a[10000]; };
A a;
// 值返回
A TestFunc1() { return a; }
// 引用返回
A& TestFunc2() { return a; }
void TestReturnByRefOrValue()
{
	// 以值作为函数的返回值类型
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// 以引用作为函数的返回值类型
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// 计算两个函数运算完成之后的时间
	cout << "TestFunc1 time:" << end1 - begin1 << endl;
	cout << "TestFunc2 time:" << end2 - begin2 << endl;
}
int main() {
	TestReturnByRefOrValue();
	return 0;
}
#endif


//const引用
#if 0
int main() {
	int a = 10;
	int& b = a;//这里是权限平移
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	const int c = 20;
	//int& d = c;//err
	//d不能是c的别名 -- 因为c不能改
	//这一句出现了权限的放大，是不允许的
	cout << typeid(c).name() << endl;
	//C++可以打印变量类型

	int e = 30;
	const int& f = e;//权限的缩小

	//隐式类型的转换
	int ii = 1;
	double dd = ii;// -- 其实都是会开一个临时变量
	//double& rdd = ii;//错误的
	const double& rdd = ii;//正确的
	//类型转换中间会产生临时变量
	//而这个临时变量具有常性
	//所以不加const的时候其实临时变量和目标变量有权限放大
	//加了const其实只是权限平移

	//const也可以做常量的别名
	const int& x = 10;//
	//所以我们以后用了引用就尽量用const -- 不然可能会引发很多问题
	return 0;
}
//强转不会改变原变量的类型
#endif



#if 0
void func1(int n)
{}
void func2(int& n)
{}
int main() {
	int a = 10;
	const int b = 20;
	func1(a);
	func1(b);
	func1(30);
	//注意：权限放大只针对引用，因为引用本质是同一块空间
	//但是这里传参是拷贝，不存在权限的问题

	func2(a);
	//func2(b);
	//func2(30);//err
	//在func2()里加个const后面两个就能传过去了
	return 0;
}
#endif
/* 总结：const具有很强的接收度
* 如果使用引用传参，函数内如果不改变n，那么建议用const引用传参
*/



//引用和指针
#if 0
int main()
{
	int a = 10;
	int& ra = a;

	cout << "&a = " << &a << endl;
	cout << "&ra = " << &ra << endl;
	return 0;
}
//指针更强大，更危险，更危险
//应用相对局限一些，更安全，更简单


//在语法角度：引用没有开空间，指针开了4或者8
//我们打开汇编，可以发现，两种方式的汇编代码是一样的
//所以引用的底层就是指针
int main() {
	//
	int a = 10;
	int& ra = a;
	ra = 20;
	//
	int* pa = &a;
	*pa = 20;

	return 0;
}
#endif
//相当于引用是指针的封装
//我们用的时候，就想引用就是换个名字 -- 这去想取用才是最好的


//C++为什么支持函数重载
//Linux 7_19_cpp里演示
//安装g++指令
//yum install gcc-c++ libstdc++-devel

//预处理+编译+汇编+链接
//预处理：头文件展开，宏替换，条件编译，去掉注释
//生成：func.i test.i

//编译：语法检查，生成汇编代码
//生成：func.s test.s

//汇编：把汇编代码转换二进制机器码
//生成：func.o test.o -- 两个func都有汇编代码

//链接
//a.out(linux)  
//xxx.exe(windows)

//链接的时候怎么找声明的定义
//call func (?)里面是地址
//地址在哪找，在定义里面
//所以链接阶段找
//怎么找
//一开始会生成符号表
//
//问题就出在符号表了
//无法分清函数
//因为函数名相同，生成的符号叫一样

//那么g++编译的时候，生成符号表的时候，会有一个函数名修饰规则
//readelf test.o -s
//readelf func.o -s 可以看符号表
//符号表里面对func函数的修饰
//_Z4funcid
//_Z4funcii
// 4代表函数名的长度，id代表参数类型的首字母（ii同理）
//这样就不会冲突了

//总结：为什么cpp支持函数重载 -- 函数名修饰规则 -- 参数不同，修饰出来名字就不同了


//C++怎么调用C
//C++程序    C++库
//C程序      C库
//如果交叉调用呢？
//可以的 -- 但是需要做一些处理
//C++编译器认识C的规则
//C编译器不认识C的规则
// 

//C++调用C的库
//如果我们用C写了一个静态库(.lib)，现在需要在C++编译器里面用(静态库包括了Stack.c里面的一些函数定义)
//我们是用不了的，因为C生成的.lib文件的符号规则和C++不同
//我们extern "C" 即可
extern "C" {
#include"Stack.h"
}
//这里的extern "C"的作用其实就是告诉C++编译器这里面的声明的实现，使用C实现的
//等下用C的规则去链接查找它们


//C调用C++库
//操作和上面一样
//和上面不一样的点是，这次C程序不变了，因为C不可能认识C++
//我们只能改库
//在.h文件里面给函数接口声明弄上extern "C"，把接口都包起来
//但是这样其实会出现问题，因为.h会在.c文件里面展开，但是.c文件里面不支持extern "C"因为C++才支持这个玩意儿
//所以我们要弄一个C++标识宏 -- 让生成符号表的时候（Cpp编译器）有extern "C"，即用C的规则生成.lib文件
//但是要在.c里面不展开，因为.c看不懂extern "C"
#ifdef __cplusplus
extern "C"
{
#endif
	//...接口声明
	//...
#ifdef __cplusplus
}
#endif
//这样弄的话，cpp里面有extern "C"，c里面就没有了


//内联函数
/*
* 以inline修饰的函数叫做内联函数，编译时C++编译器会调用内联函数的地方
* 展开，没有函数压栈的开销，内联函数提升程序运行的效率
*/
//1.短小的函数
//2.频繁的调用（如10万次）
//场景：堆排和快排的swap函数

//C: 宏函数
//C++: inline

//ADD的宏函数
#if 0
#define ADD(X,Y)((X)+(Y))
int main() {
	int a = 10+1;
	int b = 15;
	int ret = ADD(a, b);
	cout << ret << endl;
	return 0;
}
#endif

#if 0
inline int Add(int a, int b) {
	return a + b;
}
int main() {
	int a = 10;
	int b = 20;
	cout << Add(a, b) << endl;
	return 0;
}
#endif
//inline 符合条件的情况下，在调用的地方展开
//C++中基本不再建议使用宏
//《effective C++》中一个条款：尽量用const enum inline去替代宏

//关于inline
/*
* 1.inline是一种以空间换时间的做法，省去调用函数的开销。
*   所以当代码很长或者有循环/递归的函数不适合使用作为内联函数
* 2.inline对于编译器而言只是一个建议。编译器会自动优化
*   如果定义为inline的函数体内有递归，或函数比较长等等，编译器优化时会忽略掉内联
* 3.inline不建议声明和定义分离，分离会导致链接错误，因为inline被展开，就没有函数地址了，链接就会找不到 -- 内联我直接不放到符号表里了
*/


//auto 自动推导变量
#if 0
int TestAuto()
{
	return 10;
}
int main()
{
	int a = 10;
	auto b = a;
	auto c = 'a';
	auto d = TestAuto();

	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;

	//auto e; 无法通过编译，使用auto定义变量时必须对其进行初始化
	return 0;
}
#endif

#if 0
int main() {
	int a[] = { 1,2,3,4,5,6 };
	//现在要遍历a这个数组
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	//现在
	//范围for
	//自动取a的数据赋值给e
	//自动迭代，自动判断结束
	for (auto e : a) {
		cout << e << " ";
	}
	cout << endl;
	return 0;
}
#endif

#include<map>
#if 0
int main() {
	std::map<std::string, std::string>dict;
	std::map<std::string, std::string>::iterator it = dict.begin();
	auto it = dict.begin();//上面这行可以用auto优化成这个样子
	//类型比较长的时候，可以用auto来简化
	return 0;
}
#endif


//auto和指针结合使用
#if 0
int main() {

	int x = 10;
	auto a = &x;//int*
	auto* b = &x;//强调一定要传指针
	auto& c = x;//强调c是一个引用
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;

	*b = 30;
	c = 40;
	return 0;

}
#endif

//现在再举一个刚才数组的例子，我想通过范围for来修改数组的值怎么办
#if 0
void print_arr(int* arr, int sz) {
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
#if 0
	for (auto e : arr) {
		e--;
	}
#endif
	for (auto& e : arr) {
		e--;
	}
	//这样肯定是没有效果的,因为e是arr[]的一个拷贝，但是我改成引用就不同了，引用就不是拷贝了
	print_arr(arr,sizeof(arr)/sizeof(int));
	return 0;
}
#endif

//auto不能作为函数的参数
//auto不能用来声明数组s



//NULL的问题
void f(int) {
	cout << "f(int)" << endl;
}
void f(int*) {
	cout << "f(int*)" << endl;
}
int main() {
	int* p = NULL;
	f(0);
	f(NULL);//我们发现NULL其实去调用第一个了，因为在cpp中NULL被定义成0了
	f(p);
	return 0;
}
//nullptr补C++的坑，不是补C语言的坑，以后都用nullptr就行