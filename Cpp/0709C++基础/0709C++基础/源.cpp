#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

//using namespace std;

//一般来说std不要完全展开
//建议
//1.项目中，尽量不要用using namespace std;
//2.日常练习中用using namespace std;
//3.项目中，可以指定命名空间访问+展开常用的

#if 0
using std::cout;
using std::endl;
int main() {
	//像这种，指定一次vector，里面的函数就不用指定了
	std::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//下面这些要重复写，我们就展开常用的
	cout << "hello world!" << endl;
	cout << "hello world!" << endl;
	cout << "hello world!" << endl;

	return 0;
}
#endif



//C++的输入和输出
using namespace std;
#if 0
int main() {
	int i;
	double d;
	cin >> i >> d;
	cout << i << " " << d << endl;
	cout << "hello world" << endl;
	char arr[] = "hello bit";
	cout << arr << endl;
	//C语言的东西可以继续用的
	//如果想要控制输出的格式，只输出小数点后几位，等这些
	//直接用printf就好
	return 0;
}
//这里可以自动识别类型
#endif


#if 0
//缺省参数
void Func(int a = 0) {
	cout << a << endl;
}
int main() {
	Func(1);
	Func(2);
	Func();//不传参数的时候，缺省参数起作用，如果传了参数，缺省参数就不起作用
	return 0;
}


//全缺省参数和半缺省参数
void TestFunc1(int a = 10, int b = 20, int c = 30)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}
void TestFunc2(int a, int b = 10, int c = 20)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}
//缺省只能从左往右
//void F(int a = 10, int b, int c);//不行
void F(int a, int b = 10, int c = 10);
//void F(int a = 10, int b, int c = 10);//不行


int main() {
	TestFunc1();
	TestFunc1(1);
	TestFunc1(1, 2);//传的参数是从左往右给的
	TestFunc1(1, 2, 3);

	//TestFunc2();
	TestFunc2(1);
	TestFunc2(1, 2);//传的参数是从左往右给的
	TestFunc2(1, 2, 3);
	return 0;
}
#endif

#if 0
//怎么用呢
struct Stack {
	int* _a;
	int _top;
	int _capacity;
};
void StackInit(struct Stack* ps, int capacity = 4) {
	ps->_a = (int*)malloc(sizeof(int) * capacity);
	//...
	ps->_top = 0;
	ps->_capacity = capacity;
}
int main() {
	//如果知道一定会插入100个数据，就可以显示传参数100
	//这样提前开好空间，这样插入数据就可以避免扩容，扩容是有代价的
	struct Stack st1;
	StackInit(&st1, 100);

	//如果不知道就不传-直接缺省-用默认的4
	struct Stack st2;
	StackInit(&st2);

	return 0;
}

//缺省参数不能在声明和定义同时出现
//一般是声明给，定义不给
//一般是按照声明为准的
#endif


//函数重载
//一个函数有多个意思
//C语言是不允许重名函数存在的
//C++可以
//1.同名函数一定要在同一个作用域里作用
//2.这些同名函数的形参列表（参数个数 或者类型 顺序）必须不同
///常常用来处理实现功能类似数据类型不同的函数
#if 0
int Add(int left, int right)
{
		return left + right;
}
double Add(double left, double right)
{
	return left + right;
}
long Add(long left, long right)
{
	return left + right;
}
int main()
{
	cout << Add(10, 20) << endl;
	cout << Add(10.0, 20.0) << endl;
	cout << Add(10L, 20L) << endl;
	return 0;
}
#endif

//函数重载对C++意义重大
#if 0
int main() {
	int a = 1;
	int b = 2;

	double c = 1.1;
	double d = 2.2;

	swap(a, b);
	swap(c, d);

	cout << a;//其实自动识别类型-就是函数重载支持的
	cout << c;
	return 0;
}
#endif
//为什么C++支持函数重载，为什么C不支持
//C++如何调用C？
//大命题：函数重载的底层原理


//引用
//就是给变量取别名
#if 0
int main() {
	int a = 0;
	int& b = a;//这里是引用
	cout << &b << endl;//这里是取地址
	cout << &a << endl;
	//发现地址是一样的
	a++;
	cout << a << " " << b << endl;
	return 0;
}
#endif



//引用特性
//1.引用在定义的时候一定要初始化
//2.一个变量可以有多个引用
//3.如果引用给了一个实体，就不能给另外一个实体了
#if 0
int main() {
	//1.
	int a = 1;
	//int& b;  //err
	//2.
	int& b = a;
	int& c = a;
	int& d = c;
	cout << a << " " << b << " " << c << endl;
	++a;
	cout << a << " " << b << " " << c << endl;
	//3.
	//这里和指针是不一样的，指针可以随时改变，一会儿指向它一会儿指向它
	int x = 10;
	b = x;//b是x的别名呢？还是x赋值给b呢？---这里是赋值
	cout << a << " " << b << " " << c << endl;
	return 0;
}
#endif

//引用的应用场景
//1.做参数 -- 输出型参数
#if 0
void _swap(int& r1, int& r2) {
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}void _swap_ptr(int* r1, int* r2) {
	int tmp = *r1;
	*r1 = *r2;
	*r2 = tmp;
}

//vector
typedef struct SeqList {
	//...
}SL;
void SLPushBack(SL& s, int x)//引用
{}
#endif

//forwardList
#if 0
typedef struct SListNode {
	//...
}SLTNode;
void SListPushBack(SLTNode** pphead, int x) {}//指针版本
void SListPushBack(SLTNode*& pphead, int x) {}//引用版本
#endif

//再改进
#if 0
typedef struct SListNode {
	//...
}SLTNode,*PSLTNode;//这里其实把指针略去了，其实这个优化其实达不到优化的效果，复杂化了问题
void SListPushBack(PSLTNode& phead, int x) {//phead其实就是list的别名，phead改变其实list也会改变
	if (phead == NULL) {
		phead = (SLTNode*)malloc(sizeof(SLTNode));
		//...
	}
}
//这些我们也要看懂！
//刚才那个typedef底下的*PSLTNode其实就是
typedef struct SListNode* PSLTNode;//其实是一个道理

int main() {
	int a = 0, b = 2;
	cout << a << " " << b << endl;
	_swap_ptr(&a, &b);
	cout << a << " " << b << endl;
	_swap(a, b);
	cout << a << " " << b << endl;
	//
	SL s;
	SLPushBack(s, 1);
	SLPushBack(s, 2);
	SLPushBack(s, 3);
	//
	SLTNode* list = NULL;
	SListPushBack(list, 1);
	SListPushBack(list, 2);
	SListPushBack(list, 3);

	return 0;
}
#endif


//引用
//2.大对象传参，提高效率
//现在先认为，引用是不开空间的
#if 0
#include <ctime>
struct A {
	int arr[10000];
};
void TestFunc1(A a) {}
void TestFunc2(A& a) {}
void TestRefAndValue()
{
	A a;
	// 以值作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000000; ++i)//传多次
		TestFunc1(a);
	size_t end1 = clock();

	// 以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc2(a);
	size_t end2 = clock();

	// 分别计算两个函数运行结束后的时间
	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
}
int main() {
	TestRefAndValue();
	return 0;
}
#endif 
//现在先不要关心底层是怎么实现的





//引用
//3.返回值
#if 0
int Count1() {
	//int n = 0;
	static int n = 0;
	n++;
	//...
	return n;
}
//上面用传值返回的时候，n其实不是返回值，是要拷贝一个新的
//所以会压栈 -- 在函数的栈帧和销毁那里有讲 -- 小的话用寄存器，大的话会提前开好空间
//为什么传值返回要这样做呢
//因为函数Count1的栈帧是要销毁的
//所以无论n是在静态区还是在栈里面，操作系统都要拷贝好，因为是传值返回
//所以只要是传值返回
//都会生成一个返回对象拷贝作为函数调用的返回值

//传引用返回
int& Count2() {
	int n = 1;
	//static int n = 0;
	n++;
	//...
	return n;
}
int main() {
	int& ret = Count2();
	//如果这样写，ret其实就是n，函数结束之后，ret其实没了
	//这样写和int ret= Count2(); 是不一样的
	//
	printf("%d\n", ret);
// -- 此时ret的结果是未定义的，如果栈帧结束时，系统会清理栈帧，置成随机值
//那么这里ret应该是随机值
//这里侥幸刚好是1
	printf("%d\n", ret);
	cout << ret << endl;//打印第二次的时候其实就是随机值了 -- 而且调printf和cout的结果不一样
	cout << ret << endl;
	//如果不用static其实是越界了
	//但是越界!=报错
	//为什么这里不报错呢 -- 源于一个侥幸

	//后面这些全越界了
	ret = 10;
	*(&ret + 1) = 20;
	*(&ret + 2) = 30;
	for (int i = 0; i < 100; i++) {//这里数量少的时候编译器发现不了，循环多一点编译器就报错了
		*(&ret + i) = i;
	}
	return 0;
}
#endif
//总结：
/*
* 出了函数作用，返回对象就销毁了 -- 那么一定不能用引用返回，一定要用传值返回
* 如果用一个static就可以用了
*/

//引用返回的场景
#include<cassert>
typedef struct SeqList {
	int* a;
	int size;
	int capacity;
}SL;
void SLInit(SL& s, int capacity = 4) {
	s.a = (int*)malloc(sizeof(int) * capacity);
	assert(s.a);
	//...
	s.size = 0;
	s.capacity = capacity;
}
void SLPushBack(SL& s, int x) {
	if (s.size == s.capacity) {
		//...
	}
	s.a[s.size++] = x;
}
//现在需要一个修改顺序表数据的接口
void SLModify(SL& s, int pos, int x);//以前的版本 -- 不爽
int& SLAt(SL& s, int pos) {
	assert(pos >= 0 && pos <= s.size);
	return s.a[pos];
}
int main() {
	SL sl;
	SLInit(sl);
	SLPushBack(sl, 1);
	SLPushBack(sl, 2);
	SLPushBack(sl, 3);
	for (int i = 0; i < sl.size; i++) {
		cout << SLAt(sl, i) << " ";
	}
	cout << endl;
	//修改
	//因为返回值是引用，所以可以直接获取顺序表里面的值
	SLAt(sl, 0)++;
	//再打印
	for (int i = 0; i < sl.size; i++) {
		cout << SLAt(sl, i) << " ";
	}
	cout << endl;
	//再改
	SLAt(sl, 0) = 10;
	//再打印
	for (int i = 0; i < sl.size; i++) {
		cout << SLAt(sl, i) << " ";
	}
	cout << endl;
	return 0;
}
//这样我们改的就很爽
//这个SLAt接口其实就像数组的[]一样，可写可改
//只要我们return的东西在堆上面，我们直接用引用返回得了