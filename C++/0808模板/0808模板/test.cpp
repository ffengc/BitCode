#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cassert>
using namespace std;

//模板 -- 泛型编程
#if false
void Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}
void Swap(double& left, double& right)
{
	double temp = left;
	left = right;
	right = temp;
}
void Swap(char& left, char& right)
{
	char temp = left;
	left = right;
	right = temp;
}
int main() {

	return 0;
}
#endif


//template<typename1,typename2,....> -- 模板参数
//template<typename T>//<>里面也可以写class T -- 目前这里是没有区别的，以后会有区别
#if 0
void Swap(T& left, T& right) {
	T temp = left;
	left = right;
	right = temp;
}
int main() {
	int a = 10, b = 20;
	double c = 10, d = 20;
	char e = 'a', f = 'b';
	//注意，这三句话调用的不是同一个函数
	Swap(e, f);
	Swap(c, d);
	Swap(a, b);
	return 0;
}
#endif
//三句话不是同一个函数！
//因为模板会 推演参数实例化 -- 会推演出3个函数出来


//注意：模板不能隐式类型转换！
//
#if 0
template<class T>
T Add(const T& left, const T& right) {
	return left + right;
}
int main() {
	//隐式实例化
	cout << Add(1, 2) << endl;
	//cout << Add(1.1, 2) << endl;//err -- 或者我们写两个模板参数也是可以的
	cout << Add((int)1.1, 2) << endl;//隐式转不行，那我们就显示转
	cout << Add(1.1, (double)2) << endl;

	//显式实例化
	cout << endl << endl;
	cout << Add<int>(1.1, 2) << endl;
	cout << Add<double>(1.1, 2) << endl;
	return 0;
}
//有些地方是一定要显式实例化的！！！
//有时候是没有办法推隐式推演的
#endif

//一个int Add()和一个模板的能否同时存在呢
//同时存在会去调用哪一个呢？
//先去调用现成的 -- 如果没有 -- 才去实例化一个
//但是完全不建议这样去写



//类模板
template<class T>
class Stack {
public:
	//构造
	Stack(size_t capacity = 4)
		:_a(nullptr),
		_capacity(0),
		_top(0)
	{
		//默认给个4
		if (capacity > 0) {
			_a = new T[capacity];
			_capacity = capacity;
			_top = 0;
		}
	}
	//析构
	~Stack() {
		delete[] _a;
		_a = nullptr;
		_capacity = _top = 0;
	}
	void Push(const T& x) {
		if (_top == _capacity) {
			size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
			//在C++中不到万不得已不要去用malloc 因为它不会去调用自定义类型对象的构造函数
			//这样会导致自定义类型没有被初始化

			//这个是C++的扩容方式，相比realloc可能麻烦一点，但是我们还是推荐用new
			T* tmp = new T[newCapacity];
			if (_a) {
				memcpy(tmp, _a, sizeof(T) * _top);
				delete[] _a;
			}
			_a = tmp;
			_capacity = newCapacity;
		}
		//1.开新空间
		//2.自己手动拷贝过去
		//3.delete旧空间
		_top++;
		_a[_top - 1] = x;
	}
	void Pop() {
		assert(_top > 0);
		--_top;
	}
	bool Empty() {
		return _top == 0;
	}
	const T& Top() {//这里最好传引用吧，因为出了作用域还在，因为它们在堆上
		//当然，如果直接传引用返回 -- 外面就可以修改了：st1.Top()++
		//如果不想让这件事发生
		//加个const就行
		assert(_top > 0);
		return _a[_top - 1];
	}
private:
	int* _a;
	int _top;
	int _capacity;
	//不用初始化列表也可以在这缺省 -- 本质是一样的
	//写在这里缺省本质就是初始化列表
	//int*_a=nullptr;
};
int main() {
	//规范点应该要去try catch 但是平时练习可以不用的
	try
	{
		Stack<int>st1;
#if 0
		Stack<double>st2;

		//直到要存100个数据（构造的缺省值的用处）
		Stack<int>st3(100);
#endif
		st1.Push(1);
		st1.Push(2);
		st1.Push(3);
		st1.Push(4);
		st1.Push(5);
		while (!st1.Empty()) {
			cout << st1.Top() << " ";
			st1.Pop();
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

//模板不支持分离编译。
//模板不支持声明放.h 定义放在.cpp
//如果是同一个文件中，是可以声明和定义分离的
//模板是可以缺省的，但是一般不使用
//详细的我们在模板进阶再讲

//template<typename TT = int>
//但是下面也要加<>
//Stack<>st1
//这样就是用了缺省类型