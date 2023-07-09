#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<iostream>
#include<algorithm>	
#include<vector>
#include<string>
#include<map>
using namespace std;
#elif
#endif


//0929 模板+继承
#if 0
template<typename Type>
Type Max(const Type& a, const Type& b)
{
	cout << "This is Max<Type>" << endl;
	return a > b ? a : b;
}
template<>
int Max<int>(const int& a, const int& b)
{
	cout << "This is Max<int>" << endl;
	return a > b ? a : b;
}
template<>
char Max<char>(const char& a, const char& b)
{
	cout << "This is Max<char>" << endl;
	return a > b ? a : b;
}
int Max(const int& a, const int& b)
{
	cout << "This is Max" << endl;
	return a > b ? a : b;
}
int main()
{	
	Max(10, 20);
	// This is Max
	Max(12.34, 23.45);
	//This is Max<Type>
	Max('A', 'B');
	//This is Max<char>
	Max<int>(20, 30);
	//This is Max<int>
	return 0;
}


class A
{
public:
  void f() { cout << "A::f()" << endl; }
  int a;
};
class B : public A
{
public:
	void f(int a) { cout << "B::f()" << endl; }
	int a;
};
int main()
{
	B b;
	b.f();
	return 0;
}


class A {
public:
	A() {
		cout << "A()" << endl;
	}
};
class B :A {
public:
	B() {
		cout << "B()" << endl;
	}
};
int main() {
	B();
	return 0;
}




template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
template <class T1>
class Data<T1, int>
{
public:
	Data() { cout << "Data<T1, int>" << endl; }
private:
	T1 _d1;
	int _d2;
};
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
template <typename T1, typename T2>
class Data <T1&, T2&>
{
public:
	Data(const T1& d1, const T2& d2)
		: _d1(d1)
		, _d2(d2)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1& _d1;
	const T2& _d2;
};
int main()
{
	Data<double, int> d1;
	//"Data<T1, int>"
	Data<int, double> d2;
	//"Data<T1, T2>"
	Data<int*, int*> d3;
	//"Data<T1*, T2*>"
	Data<int&, int&> d4(1, 2);
	//"Data<T1&, T2&>"
	return 0;
}
#endif


//1015继承概念等
#if 0
class Base1 { 
public: 
	int _b1;
};
class Base2 { 
public: 
	int _b2; 
};
class Derive : public Base1, public Base2 
{ 
public: 
	int _d; 
};
int main(){
	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	return 0;
}

class A
{
public:
	A() { cout << "A::A()" << endl; }
	~A() { cout << "A::~A()" << endl; }
	int a;
};
class B : public A
{
public:
	B() { cout << "B::B()" << endl; }
	~B() { cout << "B::~B()" << endl; }
	int b;
};
void f()
{
	B b;
}
int main() {
	f();
	return 0;
}

class B { public: int b; };
class C1 : public B { public: int c1; };
class C2 : public B { public: int c2; };
class D : public C1, public C2 { public: int d; };
int main() {
	cout << sizeof(D) << endl;
	D d;
	//cout << d.b << endl;
	return 0;
}
#endif


//1015虚函数考察
#if 0
class A
{
public:
	A() :m_iVal(0) { test(); }
	virtual void func() { std::cout << m_iVal << ' '; }
	void test() { func(); }
public:
	int m_iVal;
};
class B : public A
{
public:
	B() { test(); }
	virtual void func()
	{
		++m_iVal;
		std::cout << m_iVal << ' ';
	}
};
int main(int argc, char* argv[])
{
	A* p = new B;
	p->test();
	return 0;
}
#endif


#if 0
class A
{
public:
	virtual void f()
	{
	cout << "A::f()" << endl;
	}
};
class B : public A
{
public:
	virtual void f()
	{
		cout << "B::f()" << endl;
	}
};
int main()
{
	A* pa = new B;
	pa->f();
	return 0;
}
#endif


//1031
//牛客KY264 单词识别
vector<string> break_sentence_to_words(string& s) {
	vector<string>ret;
	int fast = 0, slow = 0;
	while (fast < s.size()) {
		while (fast < s.size() && s[fast] != ' ' && isalpha(s[fast])) {
			fast++;
		}
		string tmp = s.substr(slow, fast - slow);
		ret.push_back(tmp);
		fast++;
		slow = fast;
	}
	return ret;
}
void solve_words_times(string& s) {
	vector<string>ret = break_sentence_to_words(s);
	map<string, int>_map;
	for (int i = 0; i < ret.size(); i++) {
		++_map[ret[i]];
	}
	//遍历map就行了
	for (auto e : _map) {
		cout << e.first << ":" << e.second << endl;
	}
}
int main() {
	string sentence;
	getline(cin, sentence);
	for (int i = 0; i < sentence.size(); i++) {
		sentence[i] = tolower(sentence[i]);
	}
	cin.clear();
	solve_words_times(sentence);
	return 0;
}
