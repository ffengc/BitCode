#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

#elif
#endif


//需要注意的是成员函数的隐藏，只需要函数名相同就构成隐藏
//注意在实际中的继承体系里面最好不要定义同名的成员
//回顾
#if 0
class A {
public:
	void func() {
		cout << "func()" << endl;
	}
};
class B :public A {
public:
	void func(int i) {
		A::func();
		cout << "func(int i)->" << i << endl;
	}
};
void Test() {
	B b;
	b.func(10);
	b.A::func();
}

int main() {
	Test();
	return 0;
}
#endif


//赋值兼容转换
#if 0
class Person {
protected:
	string _name;
	string _sex;
	int _age;
};
class Student :public Person {
public:
	int _No;
};
int main() {
	Student sobj;
	//1.子类对象可以赋值给父类对象/指针/引用
	//这里虽然是不同类型，但不是隐式类型转换 -- 这里是特殊支持 -- 语法天然支持
	//有个形象的说法叫做切割
	//因为子类是特殊的父类
	Person pobj = sobj;
	Person* pp = &sobj;
	Person& rp = sobj; //它就可以确定 -- 不是隐式类型转换，否则这一句编译肯定不过
	//					如果是隐式类型转换 -- 会产生临时变量 -- 具有常性 -- 所以肯定引用不了

	//反过来肯定是不行的 -- 少了一部分东西，子类的东西父类没有，强转也是不行
	//但是指针和引用可以转 -- 但是这里涉及到很复杂的问题 -- 这里不展开讲
	return 0;
}
int main() {
	int i = 10;
	double d = 0;
	d = i;//隐式类型转换
	double& dd = i;//err
	const double& ddd = i;//ok
	return 0;
}
#endif



//子类的6个默认成员函数怎么办
//派生类的成员函数怎么处理
#if 0
class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{
		cout << "Person()" << endl;
	}
	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}
	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}
	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	string _name; // 姓名
};
//派生类怎么初始化呢
class Student : public Person
{
public:
	Student() {}
	Student(const char* name, int num)
		: Person(name)//这里不能写_name(name) 要写Person(name) -- 构造Person
		, _num(num)
	{
		cout << "Student()" << endl;
	}
	Student(const Student& s) //这个类其实可以不用写
		: Person(s) //直接传s -- 这就是切片的意义
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}
	Student& operator = (const Student& s)
	{
		cout << "Student& operator= (const Student& s)" << endl;
		if (this != &s)//如果是自己给自己赋值，就不用搞了
		{
			Person::operator =(s);//注意这句话！
			//为什么要显示写Person:: -- 因为同名函数构成隐藏！所以在这里调不动父类的operator=，只能Person::显式调用
			_num = s._num;
		}
		return *this;
	}

	//子类的析构的函数跟父类析构函数构成隐藏！虽然不同名
	//由于后面多态的需要，析构函数名字会同意处理成destructor()
	//这个一定要注意 -- 这个隐藏！
	~Student()
	{
		//Person::~Person();//当然显式构造是没用的，因为它会自动调用！显式写没有意义
		//每个子类析构后面，会自动调用父类析构函数，这样才能保证先析构子类，再析构父类
		cout << "~Student()" << endl;
	}
protected:
	int _num; //学号
};
void Test()
{
	//如果派生类里面什么都不写
#if 0
	Student s;
#endif
	/*
	Person()
	~Person()
	*/
	//子类编译器默认生成的默认构造函数：
	///1.自己的成员，跟类和对象一样 -- 内置不处理 -- 自定义类型调自定义类型的构造
	///2.对于继承父类成员，必须调用父类的构造函数初始化

	//拷贝构造：
	//1.自己的成员，跟类和对象一样（内置完成值拷贝，自定义类型调用调用它的拷贝构造）
	//2.继承父类的，必须调用父类的

	//赋值
	//同上

	//取地址重载 -- 是不用合成的，取自己的就行了，不用取父类的
	//而且一般不自己写

	Student s1("jack", 18);
	Student s2(s1);
	Student s3("rose", 17);
}
int main() {
	Test();
	return 0;
}
#endif



//继承与友元
//友元关系不能继承，也就是说基类友元不能访问子类私有和保护成员
#if 0
class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);//友元关系是不会被继承下去的
protected:
	string _name; // 姓名
};
class Student : public Person
{
protected:
	int _stuNum; // 学号
};
void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	//cout << s._stuNum << endl;//err
}
void main()
{
	Person p;
	Student s;
	Display(p, s);
}
#endif


/*
基类定义了static静态成员，则整个继承体系里面只有一个这样的成员。无论派生出多少个子类，都只有一
个static成员实例
*/
//无论在哪里访问到的count都是同一个count
#if 0
class Person
{
public:
	Person() { ++_count; }
protected:
	string _name; // 姓名
public:
	static int _count; // 统计人的个数。
};
int Person::_count = 0;
class Student : public Person
{
protected:
	int _stuNum; // 学号
};
class Graduate : public Student
{
protected:
	string _seminarCourse; // 研究科目
};
void TestPerson()
{
	Student s1;
	Student s2;
	Student s3;
	Graduate s4;
	cout << "人数 :" << Person::_count << endl;
	Student::_count = 0;
	cout << "人数 :" << Person::_count << endl;
	Person::_count++;
	cout << "人数 :" << Student::_count << endl;
	//发现都是一样的，count都是同一个
}
int main() {
	TestPerson();
	return 0;
}
#endif

//单继承：一个子类只有一个直接父类时称这个继承关系为单继承
//也就是一条链

//多继承：一个子类有两个或以上直接父类时称这个继承关系为多继承
//class Assistant :public student, public:teacher;


//来看两个题目：
//1.如何定义一个不能被继承的类？
//C++98的做法
//	a.父类构造函数私有 -- 子类是不可见
//  b.子类对象实例化，无法调用构造函数
//C++11的做法
//新增的关键字final
#if 0
class A final {
private:
	A() {}
protected:
	//构造函数私有化
	int _a;
};

//class B :public A {
//
//};

int main() {
	//B bb;//err
	return 0;
}

#endif


//题目2
//A.p1==p2==p3   B.p1<p2<p3   C.p1==p3!=p2  D.p1!=p2!=p3
#if 0
class Base1 {
public:
	int _b1;
};
class Base2 {
public:
	int _b2;
};
class Derive :public Base1, public Base2 {
public:
	int _d;
};
int main() {
	//考察的是一个切片 -- 赋值兼容转换
	//注意，先继承的在前面
	//所以整体结构是
	/*
		Base1       p1,p3指向这里
		Base2		p2指向这里
		int _d
	*/
	//所以选C
	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	//p1==p3
	//那p2大还是p1大
	//p2大
	//栈是倒着放的
	//注意：这个和大小端没关系，大小端分析的是一个整型里面的字节，这里是元素之间的地址关系
	return 0;
}
#endif


//菱形继承：
//菱形继承是多继承的一种特殊情况
//							   class Person
// class Student:public Person				class Teacher:public: Person
//				  class Assistant:public:Student,public Teacher
/*
菱形继承的问题：从下面的对象成员模型构造，可以看出菱形继承有数据冗余和二义性的问题。在Assistant
的对象中Person成员会有两份。
*/
#if 0
class Person
{
public:
	string _name; // 姓名
};
class Student : public Person
{
protected:
	int _num; //学号
};
class Teacher : public Person
{
protected:
	int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};
void Test()
{
	// 这样会有二义性无法明确知道访问的是哪一个
	Assistant a;

	//a._name = "peter";//err 二义性问题 -- 不明确
	 
	// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
	a.Student::_name = "xxx";
	a.Teacher::_name = "yyy";
}
#endif
//虽然能解决二义性，但是数据冗余没有解决


//虚继承可以解决冗余性和二义性的为题
//							   class Person
// 我们在这里加上   virtual                    virtual
// class Student:public Person				class Teacher:public: Person
//				  class Assistant:public:Student,public Teacher
#if 0
class Person
{
public:
	string _name; // 姓名
};
class Student : virtual public Person
{
protected:
	int _num; //学号
};
class Teacher : virtual public Person
{
protected:
	int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};
void Test()
{
	//虚继承解决了二义性和数据冗余
	Assistant a;
	a._name = "peter";//这样不会报错了 -- 这样的a._name就只有一份了
}
#endif
//现实中一般很少定义菱形继承
//或者说规定不要定义菱形继承
//但是有些地方是有用到的
//C++的IO库里面其实定义成了菱形继承
//这里就要用到虚继承

//那么虚继承是如何解决冗余性和二义性的？
//监视窗口已经不真实了，失真了
//我们用内存窗口来看
#if 0
class A
{
public:
	int _a;
};
// class B : public A
class B : virtual public A
{
public:
	int _b;
};
// class C : public A
class C : virtual public A
{
public:
	int _c;
};
class D : public B, public C
{
public:
	int _d;
};
int main()
{
	//我们可以通过内存看见
	//这个a，既不会放到B里面，也不会放到C里面，他会放到一个公共的位置
	//那B,C对象如何去找到a变量呢
	//通过内存窗口可以看到，其实存的是一个偏移量
	//这就会导致一个问题
	//因为a和B,C都不是放在一起的
	//如果遇到切割切片怎么办
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;

	B bb;
	cout << sizeof(B) << endl;//12 -- 还多了个虚基表的指针 -- 有点像deque的迭代器那种思想
	//B里面有没有_a?
	//肯定有，虽然是虚继承 -- 但是里面肯定有_a
	//如果搞不明白要再看看杭哥的视频

	return 0;
}
#endif

//以上是继承
//这种叫组合 -- 学校已经用过很多次了
class C {
	//...
};
class D {
protected:
	C _c;
};
//这个叫做组合
//适合用继承就用继承，适合用组合就用组合
//既可以使用组合和继承的情况下 -- 优先使用组合 

//继承的复用通常被称为 -- 白箱复用
//组合的复用通常被称为 -- 黑箱复用