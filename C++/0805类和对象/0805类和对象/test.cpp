#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
using namespace std;

//初始化列表
//初始化列表：以一个冒号开始，接着是一个以逗号分隔的数据成员列表，每个"成员变量"后面跟一个放在括
//号中的初始值或表达式
#if 0
class Date
{
public:
	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};
#endif
//有些成员必须使用初始化列表初始化
/*
引用成员变量
const成员变量
自定义类型成员(该类没有默认构造函数) -- 因为编译器会去调自定义类型成员的构造函数
			如果没有默认构造可以调 -- 就会报错
			但是其实构造函数其实是想初始化而已，我们在Date的成员函数里面给Time初始化 -- 就需要初始化列表
*/

//尽量使用初始化列表初始化，因为不管你是否使用初始化列表，对于自定义类型成员变量，一定会先使
//用初始化列表初始化。

//无论怎么写，都会用初始化列表的 -- 如果写了，就调用写的，如果没写，就是调用编译器的
//只是编译器的初始化列表只初始化自定义类型，不初始化内置类型而已

//结论：自定义类型成员建议使用初始化列表初始化

//初始化列表可以认为是成员变量定义的地方


#if false
class Time {
public:
	Time(int hour) {
		_hour = hour;
		cout << "调用了Time的默认构造" << endl;
	}
private:
	int _hour;
};
class Date
{
public:
	Date(int year,int hour) 
		:_t(hour) 
	{
		_year = year;
	}
private:
	int _year;
	Time _t;
};
int main() {
	Date d1(2022, 1);
	return 0;
}
#endif



//const必须用初始化列表的原因也很简单
//const成员只能在定义的时候被初始化
//const成员只能初始化一次
//而初始化列表的地方就是定义的地方，所以只能在初始化列表初始化

//引用也是同一个到底，必须要在定义的时候初始化
#if false
class A
{
public:
	A(int a)
		:_a(a)
	{}
private:
	int _a;
};
class B
{
public:
	B(int a, int ref)
		:_aobj(a)
		, _ref(ref)
		, _n(10)
	{}
private:
	A _aobj; // 没有默认构造函数
	int& _ref; // 引用
	const int _n; // const
};
#endif



//这个时候我们就可以解释C++11那个补丁是什么意思了
#if false
class Date {
public:
	Date(){}
	Date(int year) {
		_year = year;
	}
	void Print() {
		cout << _year << endl;
	}
private:
	//声明
	int _year = 1; //首先我们要搞清楚 ，这里的int _year是一个声明，不是定义！
	//定义是在初始化列表上的！
	//所以这个= 0的缺省值，本质上其实是给初始化列表的！
};
int main() {
	//Date d1(2002);
	Date d2;
	d2.Print();
	return 0;
}
#endif


//内置类型也推荐使用初始化列表初始化，当然内置类型在函数体内初始化也没有什么明显的问题
//统一的建议：能使用初始化列表就使用，基本没什么问题


//但是不能一棍子打死
//有些时候使用初始化列表就会很别扭
//比如初始化数组的时候
#if 0
class A {
public:
	//指针是内置类型
	//可以用初始化列表，但是很别扭，而且我们还要检查开空间是否成功
	//这种情况，我们写到函数体内会好一些
	A(int size)
		//:_a((int*)malloc(sizeof(int)* size)),
		//_size(size)   --    很别扭
		:_size(size)
	{
		_a = (int*)malloc(sizeof(int) * size);
		//_size = size;//不过这个变量的初始化写到初始化列表上是挺好的
		//可以混着写
		if (_a == nullptr) {
			perror("malloc fail");
		}
		memset(_a, 0, sizeof(int) * size);
	}
private:
	int* _a;
	int _size;
};
int main() {
	A aa(10);
	return 0;
}
#endif


//这个程序的运行结果是什么？
#if 0
class A
{
public:
	A(int a)
		:_a1(a)
		, _a2(_a1)
	{}

	void Print() {
		cout << _a1 << " " << _a2 << endl;
	}
private:
	int _a2;
	int _a1;
};
int main() {
	A aa(1);
	aa.Print();
	return 0;
}
#endif
//这个肯定会出问题的，因为是_a2先初始化
 
//成员变量在类中声明次序就是其在初始化列表中的初始化顺序，与其在初始化列表中的先后次序无关



//explicit关键字
#if false
class Date {
public:
	explicit Date(int year) :_year(year)
	{
		cout << "调用Date的构造函数" << endl;
	}
	Date(const Date& d) {
		cout << "调用了拷贝构造" << endl;
	}
private:
	int _year;
};
int main() {
	//这两种方式其实都调用构造函数
	Date d1(2022);//直接调用构造函数
	Date d2 = 2022;//构造+拷贝构造+优化->调用构造函数 -- 这里本质是隐式类型转换
	//如果加了explicit就会报错
	//但是过程是不一样的
	//其实我们可以自己写一个拷贝构造，看看是不是真的用了拷贝构造
	//我们写好之后发现看不出来拷贝构造的调用 -- 优化了
	//所以我们可以加上explicit关键字，阻止隐式类型的转换

	//如果加了()强转 -- 就不是隐式类型转换 它自己变的才是
	return 0;
}
#endif

#if false
int main() {
	int i = 10;
	double d1 = (double)i;//这里是显式的类型转换
	double d2 = i;//这里就发生了隐式类型的转换
	//double& d3 = i;//err -- 隐式类型转换会产生临时变量，临时变量具常性，d3不是引用i，是引用临时变量
	const double& d4 = i;//这样就可以编过了
	i++;
	int& ii = i;//如果没有不做转换，ii就会随i变，因为ii是i的引用
	//但是d4不是i的引用，d4是临时变量的引用
	cout << d4 << endl;//这个是不会变的
	cout << ii << endl;
	cout << i << endl;
	return 0;
}
#endif

//匿名对象
#if 0
class Date {
public:
	Date(int year) :_year(year)
	{
		cout << "调用Date的构造函数" << endl;
	}
	Date(const Date& d) {
		cout << "调用了拷贝构造" << endl;
	}
	~Date() {
		cout << "调用了Date的析构函数" << endl;
	}
private:
	int _year;
};
int main() {
	//Date d3(2022);
	Date(2022);//匿名对象 -- 生命周期只有这一行
	//因此这个匿名对象的析构马上会被调用
	return 0;
}
#endif


//匿名对象在一些场景还是有用的
//比如我们做OJ题的时候要调试
#if false
class Solution {
public:
	void fun() {//解题函数
		//...
	}
};
int main() {
	//我们想要调试力扣的OJ
	//1.
	Solution su;
	su.fun();//这样去调函数
	//但是我们可以思考，我们实例化这个类的目的就是用这个函数，没有别的目的
	//因此我们可以这样调用
	//2.
	Solution().fun();//这样一行搞定 -- 很简洁
	return 0;
}
#endif




//静态成员
/*声明为static的类成员称为类的静态成员，用static修饰的成员变量，称之为静态成员变量；用static修饰的
成员函数，称之为静态成员函数。静态的成员变量一定要在类外进行初始化*/

//我们是否能创建一个只能让我们这个类使用的全局变量呢 -- 静态成员
#if 0
class A
{
public:
	A() { ++_scount; }
	A(const A& t) { ++_scount; }
	//静态成员函数 -- 没有this指针
	static int& GetCount() {//这里如果把&也加上，类外面就可以对_scount进行操作了
		//没有this指针，所以是访问不了_a的
		return _scount;
	}
private:
	//静态成员变量 属于整个类 生命周期在整个程序运行期间 存在静态区
	static int _scount;//声明 -- 我们都知道，只有声明是肯定会报错的

	int _a;
};
//所以我们要想办法去定义这个_scount
//我们目前所知的
//1.初始化列表 -- 不行 -- 初始化列表不能声明静态变量
//2.缺省值 -- 不行 -- 缺省值本来就是给初始化列表的，现在初始化列表行不通了，缺省肯定行不通的

//所以 -- 类外面定义初始化
int A::_scount = 0; //定义的时候不用带static

void TestA()
{
	A a1;
	A a2;
	A a3(a2);

#if 0
	cout << a1._scount << endl;//假如静态成员是公有的，我们去访问一下
	cout << a2._scount << endl;
	cout << A::_scount << endl;
	a1._scount++;
	cout << a1._scount << endl;
	cout << a2._scount << endl;
	cout << A::_scount << endl;
#endif//如果是私有的就访问不了了 -- 引出一个新的概念 -- 静态成员函数
	cout << a1.GetCount() << endl;
	cout << a2.GetCount() << endl;
	cout << A::GetCount() << endl;
	a1.GetCount()++;//这个操作能执行只是因为我们返回了&类型
	cout << a1.GetCount() << endl;
	cout << a2.GetCount() << endl;
	cout << A::GetCount() << endl;
}
int main() {
	TestA();
	return 0;
}

/*
1. 静态成员为所有类对象所共享，不属于某个具体的实例 -- a1,a2,a3共享一个_scount
2. 静态成员变量必须在类外定义，定义时不添加static关键字
3. 类静态成员即可用类名::静态成员或者对象.静态成员来访问
4. 静态成员函数没有隐藏的this指针，不能访问任何非静态成员
5. 静态成员和类的普通成员一样，也有public、protected、private 3种访问级别，也可以具有返回值
*/
#endif



//静态的使用场景
//应用1：
//求1+....+n
#if 0
class Sum {
public:
	Sum() {
		_sum += _i;
		++_i;
	}
	static int GetSum() {
		return _sum;
	}
private:
	static int _sum;
	static int _i;
};
int Sum::_sum = 0;
int Sum::_i = 1;
class Solution {
public:
	int Sum_Solution(int n) {
		Sum a[n];
		return Sum::GetSum();
	}
};
//这个就是我们的标准玩法
//这个底层的具体思路就是封装
#endif


//应用2：
//设计一个只能在栈上定义的类
#if 0
class StackOnly {
public:
	static StackOnly CreateObj() {
		StackOnly so;//这个是在栈上的
		return so;
	}
private:
	StackOnly(int x = 0, int y = 0)
		:_x(x),
		_y(0)
	{}
private:
	int _x = 0;
	int _y = 0;
};
int main() {
#if 0
	StackOnly so1;//栈
	static StackOnly so2;//静态区
#endif
	//在这个时候，如果我们把构造函数设置成公有的
	//就限制不了在哪里创建了，因为哪都可以调用这个函数
	//所以我们直接把构造函数设置成私有的
	// -- 设置成私有之后，哪都创建不了，这个时候，我们在类里面提供一个函数就行
	//我们在这个成员函数里面，在栈上创建，然后返回 -- 这样外面就只能得到我们在栈上创建那个了
	
	//现在就出现了先有鸡还是先有蛋的问题了，我们用这个CreateObj()就要创建对象，但是对象创建需要CreateObj
	//所以给这个函数带上static
	StackOnly so3 = StackOnly::CreateObj(); //这样就行了！
	return 0;
}


//两个问题
//1.静态成员函数可以调用非静态成员函数吗？ -- 不能，因为没有this
//2.非静态成员函数可以调用类的静态成员函数吗？ -- 可以

#endif



//友元
//1.友元函数
//2.友元类
//友元提供了一种突破封装的方式，有时提供了便利。但是友元会增加耦合度，破坏了封装，所以友元不宜多用。

/*
友元函数可以直接访问类的私有成员，它是定义在类外部的普通函数，不属于任何类，但需要在类的内部声
明，声明时需要加friend关键字。
友元函数不能用const修饰
友元函数可以在类定义的任何地方声明，不受类访问限定符限制
一个函数可以是多个类的友元函数
友元函数的调用与普通函数的调用和原理相同
*/

/*
1.友元类的所有成员函数都可以是另一个类的友元函数，都可以访问另一个类中的非公有成员。
2.友元关系是单向的，不具有交换性。
比如上述Time类和Date类，在Time类中声明Date类为其友元类，那么可以在Date类中直接访问Time
类的私有成员变量，但想在Time类中访问Date类中私有的成员变量则不行。
友元关系不能传递
3.如果B是A的友元，C是B的友元，则不能说明C时A的友元。
*/


//内部类
#if 0
class A {
private:
	int h;
public:
	//B定义在A里面 -- 只变了这些方面
	//1.受A的类域限制，受访问限定符的限制
	//2.B天生是A的友元
	class B {
	public:
		void foo(const A& a) {
			cout << a.h << endl;//可以访问A的私有
		}
	private:
		int _b;
	};
};
int main() {
	cout << sizeof(A) << endl;//4
	A a;
	A::B b;
	return 0;
}
#endif
/*
1. 内部类可以定义在外部类的public、protected、private都是可以的。
2. 注意内部类可以直接访问外部类中的static、枚举成员，不需要外部类的对象/类名。
3. sizeof(外部类)=外部类，和内部类没有任何关系
*/


//关于编译器的一些优化
class A {
public:
	A() {
		cout << "调用了A的构造函数" << endl;
	}
	A(int x) {
		cout << "调用了A的构造函数" << endl;
	}
	A(const A& a) {
		cout << "调用了A的拷贝构造函数" << endl;
	}
	//~A() {
	//	cout << "调用了A的析构函数" << endl;
	//}
};
void f2(const A& a) {

}
A f3() {
	A a;
	return a;//当然，这里只能传值返回
}
int main() {
	A a1;
	cout << endl;
	f2(A());//这里的拷贝构造就会被优化调
	//结论：
	//连续一个表达式步骤中，连续构造一般都会优化 -- 一般会合二为一

	cout << endl;     
	A a = 1;//同样 拷贝构造被优化了

	cout << endl;
	f3();

	cout << endl;
	A a2 = f3();//理论上了1次构造2次拷贝构造
	//但是有一次拷贝构造被优化了！
	return 0;
}