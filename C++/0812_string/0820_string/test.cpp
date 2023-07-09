#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

//string



//string 有7个构造函数
//default (1)  string();
//copy(2) string(const string & str);
//substri ng(3) string(const string & str, size_t pos, size_t len = npos); -- 部分拷贝构造
//                                npos代表的是就是拷贝到最后（够长），如果不够长，也是拷贝到最后（拷贝一部分）具体可以看文档 
//npos是一个静态成员变量，static const size_t npos=-1  因为它是size_t类型的，所以其实是一个很大的值


//from c - string(4) string(const char* s);
//from sequence(5) string(const char* s, size_t n);
//fill(6) string(size_t n, char c);
//range(7) template <class InputIterator> string(InputIterator first, InputIterator last);
void test_string1() {
	string s1;
	string s2("hello string");
	cout << s1 << " " << s2 << endl;

	string s3(s2);//拷贝构造 -- 这里是深拷贝 -- 以后模拟实现的时候会学 -- 当然我们也可以写等号
	//注意： size不算\0

	//substring拷贝构造
	string s4(s2, 6, 5);
	cout << s4 << endl;

	//from sequence(5)
	string s5("hello world", 5);
	cout << s5 << endl;

	// fill(6)
	string s6(10, 'x');
	cout << s6 << endl;

	//这样写也可以！ -- 隐式类型转换 -- 类和对象的知识 -- 加了explicit就不行了
	string s = "hello world";
	cout << s << endl;
}

//赋值
/*string(1)
string& operator= (const string& str);
c - string(2)
string & operator= (const char* s);
character(3)
string& operator= (char c);*/
void test_string2() {
	string s1;
	string s2 = "hello world!";//构造+拷贝构造+优化=直接构造
	
	//下面三种就是赋值了
	s1 = s2;
	s1 = "xxxx";
	s1 = 'y';
}

//[] size length
void test_string3() {
	string s("hello world");
	//注意，用这些封装好的类，我们是不能看底层的，不能说我们去看底层的char*_str;

	//operator[]
	cout << s[1] << endl;
	s[1] = 'x';
	cout << s << endl;

	//size
	for (size_t i = 0; i < s.size(); i++) {
		cout << s[i] << " ";
	}
	cout << endl;

	//const 重载的[]
	const string s2("hello world");
	//s2[0] = " ";//err


	//length
	//其实也可以遍历 -- 推荐用size

	//[]中如果越界 -- 内部会检查

	//at的功能和[]是一致的
	//和[]的区别是 -- at越界之后会抛异常
}

//迭代器
//类似于指针的东西的东西
//有可能就是指针
//有可能不是指针
//用法像指针一样
void test_string4() {
	string s("hello");
	string::iterator it = s.begin();
	//auto it=s.begin()这样也行
	while (it != s.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;


	//abcdefg\0
	//^ s.begin()
	//        ^  s.end()
	//list/map/set只能用迭代器访问

	//迭代器是所有容器通用的访问方式

	//范围for
	//所有的容器都可以用范围for
	//范围for -- 自动迭代 ，自动判断结束
	for (auto ch : s) {
		ch++;//这里是改不了的 -- 要用引用接受才能改
		cout << ch << " ";
	}
	cout << s << endl;
	//范围for的底层是迭代器

	for (auto& ch : s) {//这样才能改
		ch++;
		cout << ch << " ";
	}
	cout << s << endl;

}

//rbegin(),rend() -- 反向迭代器
void test_string5() {
	string s("hello");
	string::reverse_iterator rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << " ";
		rit++;//这里也是++，因为是反向迭代器
	}
	cout << endl;
	//还有const迭代器 -- 只能读不能写
}//范围for只能正向遍历，反向只能用反向迭代器


void test_string6() {
	//
	string s("hello");
	s.push_back(' ');
	s.push_back('w');

	s.append("orld");
	cout << s << endl;

	//+=重载
	//可以字符可以字符串
	s += 'h';
	s += " hello";
	cout << s << endl;
}


void test_string7() {
	string s("hello world");
	string str = " hello linux";
	s.append(str.begin(), str.end());
	cout << s << endl;
	s.append(++str.begin(), --str.end());
	cout << s << endl;
}


//关于string的增容
void test_string8() {
#if 0
	string s = "hello world";
	cout << s.capacity() << endl;
#endif
	//string的扩容机制
	//思路：不断往s里面push_back()东西，把capacity都记录下来
	vector<int>string_capacity;
	string test_capacity;
	string_capacity.push_back(test_capacity.capacity());
	//记录
	for (int i = 0; i < 100; i++) {
		test_capacity.push_back('c');
		if (test_capacity.capacity() != string_capacity[string_capacity.size() - 1]) {
			string_capacity.push_back(test_capacity.capacity());
		}
	}
	//打印
	vector<int>::iterator it = string_capacity.begin();
	cout << *it;
	it++;
	while (it != string_capacity.end()) {
		cout << "->" <<*it;
		it++;
	}
	cout << endl;
	//15->31->47->70->105
	//我们也可以看看linux的
	/*a.out  code  Desktop  Documents  Downloads  Linux  Music  Pictures  Public  Templates  test.cpp  Videos
	[yufc@localhost ~]$ ./a.out
	0->1->2->4->8->16->32->64->128  -- 扩容机制是不一样的
	*/
	//说明 -- 用的时候不能以来底层实现 -- 但是我们要会 -- 不能依赖
	//不同平台不同编译器底层可能会有不同的地方


	//如果不想让编译器按照他的思路开空间 -- 我们可以用reserve
	string s2;
	s2.reserve(1000);//开空间
	cout << s2.capacity() << endl;
	s2.resize(1000,'a');//开空间+初始化（不给东西默认放\0)
}

int main() {
	//test_string1();
	//test_string2();
	//test_string3();
	//test_string4();
	//test_string5();
	//test_string6();
	//test_string7();
	test_string8();
	return 0;
}