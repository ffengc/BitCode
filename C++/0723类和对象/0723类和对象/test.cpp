#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
using namespace std;

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
#if 0
class Time {
public:
	//Time() {}
	Time(int hour = 0, int minute = 0, int second = 0) { //这里是无参的 -- ok
		                                                  //这里全缺省 -- ok 
														  //这里不是全缺省 -- 不行 -- 因为Time默认构造函数 -- 再写一个无参的和它重载 -- ok
		cout << "Time()" << endl;
		_hour = 0;
		_minute = 0;
		_second = 0;
	}
private:
	int _hour;
	int _minute;
	int _second;
};
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

	Time _t; //自定义类型
};
int main() {
	Date d1;
	//Date d2(2021, 7, 21);
	return 0;
}


//构造函数的特征：
//1.函数名与类名相同
//2.无返回值
//3.对象实例化的时候编译器自动调用
//4.可以重载

//一般写全缺省构造函数 -- 这样比较舒服

//默认生成的构造函数
//a.内置类型成员不做处理
//b.自定义类型成员回去调用他的默认构造函数 -- 注意，这里是只能调用默认构造，调用不了其他构造

//无参的构造函数和全缺省的构造函数都称为默认构造函数，并且默认构造函数只能有一个。注意：无参
//构造函数、全缺省构造函数、我们没写编译器默认生成的构造函数，都可以认为是默认成员函数。


/*  总结：
* 1.一般的类都不会让编译器默认生成构造函数，都会自己写 -- 显式写一个全缺省 -- 非常好用
* 2.特殊情况下才会让编译器默认生成
*          比如两个stack实现一个Queue的时候，我们MyQueue类里面就写两个栈行
*          那么我们的MyQueue就不用自己去写构造函数了，编译器会调用Stack的帮我们初始化
*/
#endif




//析构函数
//与构造函数功能相反，析构函数不是完成对象的销毁，局部对象销毁工作是由编译器完成的。而
//对象在销毁时会自动调用析构函数，完成类的一些资源清理工作

/*析构函数是特殊的成员函数。
其特征如下：
1. 析构函数名是在类名前加上字符 ~。
2. 无参数无返回值。
3. 一个类有且只有一个析构函数。若未显式定义，系统会自动生成默认的析构函数。
4. 对象生命周期结束时，C++编译系统系统自动调用析构函数*/

#if 0
class Date {
public:
	//全缺省的构造函数
	Date(int year = 2021, int month = 7, int day = 25)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	//析构函数
	~Date() {
		//其实日期类并没有什么需要清理的
		cout << "~Date()被调用了" << endl;
		//日期类其实没有必要显式写析构函数 -- 因为并没有什么必要
	}
private:
	int _year;
	int _month;
	int _day;
};
void Test() {
	Date d1;
}
int main() {
	Test();
	return 0;
}
#endif

//什么时候需要显式写析构函数呢？
//需要处理后事的时候 比如Stack 下面这个例子等等
//编译器生成的默认析构会帮忙释放heap上的空间吗？ -- 不会
//那么编译器生成的默认析构函数干什么事情 -- 我们后面再讨论
#if 0
typedef int DataType;
class SeqList
{
public:
	SeqList(int capacity = 10)
	{
		_pData = (DataType*)malloc(capacity * sizeof(DataType));
		assert(_pData);

		_size = 0;
		_capacity = capacity;
	}

	~SeqList() //析构函数用来善后堆上的空间
	{
		if (_pData)
		{
			free(_pData); // 释放堆上的空间
			_pData = nullptr; // 将指针置为空
			_capacity = 0;
			_size = 0;
			//其实后面这三步，可要可不要，因为栈上的空间会被自动释放 那个指针在外面也没办法访问到，所以可要可不要
			//养成好习惯还是写上
		}
	}

private:
	int* _pData;
	size_t _size;
	size_t _capacity;
};
int main() {
	SeqList sl1;//走完这一行会自动回去调用析构
	return 0;
}
#endif
//比如有效的括号那一题也是一样，用C++写会很爽，不用自己Destroy
//默认生成的析构函数特点：
//和构造函数类似 -- 内置类型不处理 -- 自定义类型处理会去调用它的析构函数



//拷贝构造函数
#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d) //这里一定是传引用  
	{//这里加个const可以防止d被修改
		//我们是不希望d被改的，因为我们只是用d来拷贝而已
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	Date d2(d1); //d2就是d1的拷贝
	Date d3 = d1;//这个是另一种写法
#if 0
	Date d4 = &d1;//这个是指针的形式
	Date d5(&d1);//这两个都一样
#endif
	return 0;
}
#endif
/*拷贝构造函数也是特殊的成员函数，其特征如下：
1. 拷贝构造函数是构造函数的一个重载形式。
2. 拷贝构造函数的参数只有一个且必须使  用引用传参，使用传值方式会引发无穷递归调用。*/

//如果拷贝构造不给引用 -- 会发生无穷递归 -- 为什么？
//因为传值调用 -- 本质就是拷贝一份一样的 -- 拷贝一份就要调用拷贝构造函数
//我们传参就是为了调用拷贝构造 -- 但是传参本身还要调用拷贝构造 -- 无穷递归了
//当然 -- 用指针也可以 -- 但是怪怪的 -- 我拷贝一份还传个地址 -- 所以用引用是最好的

#if 0
/// <summary>
/// string类
/// </summary>
class String
{
public:
	String(const char* str = "jack")//构造函数
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}
	~String()//析构函数
	{
		cout << "~String()" << endl;
		free(_str);
	}
private:
	char* _str;
};
int main()
{
	String s1("hello");
	String s2(s1); //拷贝的时候默认生成一个拷贝构造函数 -- 编译器为我们生成的拷贝函数都是浅拷贝版本！
}
#endif
//编译器为我们生成的拷贝函数都是浅拷贝版本！
//我们可以看看上面我们写那个Date -- 那个不需要free什么，所以不好测试

//编译器默认生成的拷贝构造函数内置类型和自定义类型都会处理
//内置类型 -- 按照字节方式直接拷贝，而自定义类型是调用其拷贝构造函数完成拷贝的
//但是！
//注意！
//无论是默认生成的还是自己写的 -- 拷贝构造函数完成的是浅拷贝！
//这意味着 -- 加入我们写了个Stack
//st1拷贝得到st2
//浅拷贝 -- st1，st2指向同一块空间 -- 这个会导致析构的时候崩了 -- 同一块空间被释放了两次
/*若未显示定义，系统生成默认的拷贝构造函数。 默认的拷贝构造函数对象按内存存储按字节序完成拷
贝，这种拷贝我们叫做浅拷贝，或者值拷贝。*/



///重点！！
///所以我们必须自己实现一个深拷贝！！！

//MyQueue是不用自己写拷贝构造的，因为它会去调Stack的拷贝构造
//我们把Stack的写好就行

/// ////////////////////////////////////////////////////////////////////////////////////


//运算符重载
#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d) //这里一定是传引用  
	{//这里加个const可以防止d被修改
		//我们是不希望d被改的，因为我们只是用d来拷贝而已
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	/// 运算符重载函数
	bool operator==(const Date& x2) { 
		return this->_year == x2._year
			&& this->_month == x2._month
			&& this->_day == x2._day;
	}
private:
	int _year;
	int _month;
	int _day;
};
/// <比较日期是否相等>
#if 0
bool operator==(const Date& x1, const Date& x2) { //这样拷贝消耗大，所以我们加&，
									//再加const，防止写错导致比较的时候破坏了原来类里面的值
	return x1._year == x2._year
		&& x1._month == x2._month
		&& x1._day == x2._day;
	//现在存在问题
	//1.年月日这些属性在类外面是不能被访问的
	//解决方法：我们可以在类里面写一些GetYear()函数之类的，在外面调用这些函数
	//现在我们先弄成public的，先让代码跑起来再说
}
#endif
/// <好，现在的问题是，我们把类里面的成员变量改成public，我们才有这些操作>
/// 我现在还想里面的成员变量是私有的 -- 怎么办？
/// 直接把operator==()放到类里面不就行了？
/// 但是，直接写到类里面，是有问题的，编译发现说：参数过多 -- 这是因为已经already有一个this指针了
/// 所以我们把函数copy进到类里面之后，我们稍微修改一下即可，把一个参数给删了就行
int main() {
	Date d1(2022, 7, 23);
	Date d2(2022, 7, 23);

	/// <summary>
	/// 这个肯定是ok的
	cout << (d1 == d2) << endl;//其实这句话会被转换成：
	//编译器会判断，d1，d2是不是内置类型，不是，ok，找重载
#if 0
	cout << operator==(d1, d2) << endl;//其实会被转换成这句话 -- 但是这样写就没意义了
	     //这是写在类外面的样子          //这和我们写一个is_Equal()函数，显式调用有什么区别?
									   //所以我们要学运算符重载
#endif
#if 0
	cout << d1.operator==(&d1, d2) << endl;//放进去之后，会转换成这句话
										   //但是我们肯定不能这么写，不能显式写this指针
#endif
	cout << d1.operator==(d2) << endl;//这样是ok的
	//这里一定要带括号，这里涉及优先级问题



	/// <>
	/// 我们能否实现一些更复杂有用的操作？
	/// 1.比较两个日期（判断相同）？
	/// 2.日期++
	/// 3.100天后时哪一天
	/// 4.国庆节到今天有多少天
	/// 等等
	/// 
	/// 当然，这里我们是不能直接用运算符运算的
	/// 内置类型可以直接使用运算符运算，因为编译器知道要去怎么算
	/// 自定义类型要去自己弄
	return 0;
}

/*C++为了增强代码的可读性引入了运算符重载，运算符重载是具有特殊函数名的函数，也具有其返回值类
型，函数名字以及参数列表，其返回值类型与参数列表与普通的函数类似。
函数名字为：关键字operator后面接需要重载的运算符符号。
函数原型：返回值类型 operator操作符(参数列表)*/
#endif



class Date
{
public:
	//判断闰年
	bool IsLeapYear(int year) {
		//懒得写了
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))return true;
		return false;
	}
	//获得每个月的天数
	int GetMonthDay(int year, int month) {
		static int days[] = { NULL, 31,28,31,30,31,30,31,31,30,31,30,31 };
		//最好写一个static吧，因为这个days[]可能会被频繁的调用，不需要每次都开一个days[]出来，开一个重复用就行
		if (month == 2 && IsLeapYear(year))return 29;
		return days[month];
	}
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	/// 运算符重载函数
	bool operator==(const Date& x2) {
		return this->_year == x2._year
			&& this->_month == x2._month
			&& this->_day == x2._day;
	}
	//这写都可以去写
	bool operator<(const Date& x2);
	bool operator>(const Date& x2);
	bool operator<=(const Date& x2);
	bool operator>=(const Date& x2);
	//日期加天数
	///很明显我们这样写的+是+=，因为d1变了
	Date operator+=(int day) {
		//逻辑：先直接加再说，加完再判断日期的合法性 -- 当然，我们还需要知道每个月多少天，是不是闰年 
		//当然这些都很easy
		_day += day;
		//判断是否合法，当然，可以写一个is_Valid()去判断
		while (_day > GetMonthDay(_year, _month)) {
			_day -= GetMonthDay(_year, _month);
			++_month;
			if (_month == 13) {
				_month = 1;
				_year++;
			}
		}
		/// 现在的问题是？_year这些东西，是改了谁的？是this的，所以我们返回*this
		return *this;
	}
/// 为了后面方便看结果 -- 写一个Print()
	void Print() {
		cout << "日期为:" << this->_year << "/" << this->_month << "/" << this->_day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main() {
	Date d1(2022, 7, 23);
	Date d2(2022, 7, 23);

#if 0
	d1.Print();
	(d1 += 50).Print();
	d1.Print();//我们发现我们写错了，我们写的不是+，是+=
#endif
	/// 怎么将+=改成+ -- 可以复用
	/// 这里先说第二种方式，我们在+的函数里面调用一下拷贝构造，弄一个ret
	/// 先把d1拷贝到ret里面，我们再返回ret
	/// 这样才是对的！
	return 0;
}
