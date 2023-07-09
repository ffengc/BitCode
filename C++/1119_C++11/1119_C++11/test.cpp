
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<functional>
using namespace std;
#elif
#endif

#if 0
int main()
{
	int a = 0, b = 0, c = 0, d = 0, e = 0;
	auto f1 = [=]()
	{
		cout << a << " " << b << " " << c << " " << d << " " << e << endl;
	};
	f1();

	//auto f2 = [=, a] ()  -- > err
	//{
	//	cout << a << " " << b << " " << c << " " << d << " " << e << endl;
	//};
	//f2();

	//混合捕捉
	auto f3 = [=, &a] ()
	{
		a++;
		cout << a << " " << b << " " << c << " " << d << " " << e << endl;
	};
	f3();
	return 0;
}
#endif


// 1、生命周期（存储区域）
// 2、作用域（编译器编译，用的地方能否找到）
// 捕捉列表的本质就是传参
#if 0
static int f = 1;

int func()
{
	int a, b, c, d, e;
	a = b = c = d = e = 1;

	// 全部传值捕捉
	auto f1 = [=](){
		cout << a << b << c << d << e << endl;
	};

	f1();

	// 混合捕捉
	auto f2 = [=, &a](){
		a++;
		cout << a << b << c << d << e << endl;
	};

	f2();
	static int x = 0;

	if (a)
	{
		auto f3 = [&, a](){
			//a++;
			b++;
			c++;
			d++;
			e++;
			f++;
			x++;
			cout << a << b << c << d << e << endl;
		};

		f3();
	}

	return 0;
}

int main()
{
	//auto f4 = [&, a](){
	//	//a++;
	//	b++;
	//	c++;
	//	d++;
	//	e++;
	//	f++;
	//	cout << a << b << c << d << e << endl;
	//};

	//f4();

	return 0;
}
#endif


//捕捉列表的底层本质是一个仿函数
#if 0
class Rate
{
public:
	Rate(double rate) : _rate(rate)
	{}

	double operator()(double money, int year)
	{
		return money * _rate * year;
	}

private:
	double _rate;
};


// 其实本质就是会生成这样一个类
// lambda_uuid
class lambda_xxxx
{

};

int main()
{
	// 函数对象
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);
	// 仿函数lambda_uuid
	// lambda -> lambda_uuid
	// 调用的本质是operator()
	auto r2 = [=](double monty, int year)->double{return monty*rate*year; };
	r2(10000, 2);
	auto r3 = [=](double monty, int year)->double{return monty*rate*year; };
	r3(10000, 2);
	return 0;
}
#endif



//包装器
//ret = func(x);
#if 0
template<class F, class T>
T useF(F f, T x)
{
	static int count = 0;
	cout << "count:" << ++count << endl;
	cout << "count:" << &count << endl;

	return f(x);
}

double f(double i)
{
	return i / 2;
}

struct Functor
{
	double operator()(double d)
	{
		return d / 3;
	}
};

int main()
{
	// 函数指针
	function<double(double)> f1 = f;
	cout << useF(f1, 11.11) << endl;

	// 函数对象
	function<double(double)> f2 = Functor();
	cout << useF(f2, 11.11) << endl;

	// lamber表达式对象
	function<double(double)> f3 = [](double d)->double{ return d / 4; };
	cout << useF(f3, 11.11) << endl;

	return 0;
}
#endif

//150. 逆波兰表达式求值
#if 0
#include<stack>
class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<long long>st;
		map<string, function<long long(long long, long long)>>opFuncMap =
		{
			{"+",[](int a,int b) {return a + b; }},
			{"-",[](int a,int b) {return a - b; }},
			{"*",[](int a,int b) {return a * b; }},
			{"/",[](int a,int b) {return a / b; }}
		};
		for (auto& str : tokens)
		{
			if (opFuncMap.count(str))
			{
				//操作符
				int right = st.top();
				st.pop();
				int left = st.top();
				st.pop();
				st.push(opFuncMap[str](left, right));
			}
			else
			{
				//操作数
				st.push(stoll(str));
			}
		}
		return st.top();
	}
};
#endif
//反正用包装器 -- 格式记住就行了
//function<返回值,(参数)>



//绑定
int Div(int a, int b)
{
	return a / b;
}
int Plus(int a, int b)
{
	return a + b;
}
int Mul(int a, int b, int rate = 2)
{
	return a * b * rate;
}
class Sub
{
public:
	int sub(int a, int b)
	{
		return a - b;
	}
};
int main()
{
#if 0
	//如果要用包装器怎么写
	function<int(int, int)>funcPlus = Plus;
	function<int(Sub, int, int)>funcSub = &Sub::sub;//我们发现这里要多一个参数Sub -- 因为这里要调用对象的
	//这样的话就会变得很麻烦了
	//这个时候就需要用到绑定了
#endif
	
	int x = 10, y = 2;
	//调整参数的顺序 -- 这个功能很鸡肋
	//_1,_2 ... 是定义再placeholders命名空间中，代表绑定函数对象的形参
	//_1代表第一个形参，_2代表第二个形参
	//调整参数顺序是指调整形参的 -- 传的时候的实参不变
	auto bindFunc1 = bind(Div, placeholders::_1, placeholders::_2);
	auto bindFunc2 = bind(Div, placeholders::_2, placeholders::_1);
	cout << Div(x, y) << endl;//5
	cout << bindFunc1(x, y) << endl;//5
	cout << bindFunc2(x, y) << endl;//0

	//真正的价值点 -- 绑定参数 -- 即调整个数
	//把第一个参数绑定了 -- 因为第一个参数是固定的
	function<int(int, int)>funcSub = bind(&Sub::sub, Sub(), placeholders::_1, placeholders::_2);
	function<int(int, int)>funcPlus = Plus;
	function<int(int, int)>funcMul = bind(Mul, placeholders::_1, placeholders::_2, 2);//给个2代表绑定2传给第三个参数
																			//这个2是要给的 -- 缺省值是不起作用的
	map<string, function<int(int, int)>>opFuncMap =
	{
		{"+",Plus},
		{"-",bind(&Sub::sub,Sub(),placeholders::_1,placeholders::_2)}
	};
	cout << funcPlus(1, 2) << endl;
	cout << funcSub(1, 2) << endl;
	cout << opFuncMap["+"](1, 2) << endl;
	cout << opFuncMap["-"](1, 2) << endl;
	cout << funcMul(1, 2) << endl;
	//这正的价值在于可以绑定某个参数
	return 0;
}