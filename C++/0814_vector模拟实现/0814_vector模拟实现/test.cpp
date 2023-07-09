#define _CRT_SECURE_NO_WARNINGS 1

#include"MyVector.h"
#include<iostream>
#include<vector>
using namespace std;

void PrintVector(yufc::vector<int>& v) {//在没有写拷贝构造的时候，这里一定要引用的，不然浅拷贝，释放两次会出问题
	yufc::vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void PrintVector(const yufc::vector<int>& v) {
	yufc::vector<int>::const_iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test_vector1() {
	yufc::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	for (int i = 0; i < v.size(); i++) {
		++v[i];
		cout << v[i] << " ";
	}
	cout << endl;
}
void test_vector2() {
	yufc::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	yufc::vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		(*it)--;
		cout << *it << " ";
		it++;
	}
	cout << endl;

	for (auto& e : v) {
		e++;
		cout << e << " ";
	}
	cout << endl;

	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;

	PrintVector(v);
}
void test_vector3() {
	const yufc::vector<int>v;
#if 0 //改不了的
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
#endif
	PrintVector(v);
	//范围for虽然是傻瓜式的替换 -- 但是它也是会调用const迭代器的
}
//迭代器失效问题
void test_vector4() {
	yufc::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v.push_back(5); // 我们发现  -- 原来4个数据，insert之后要扩容的时候，就出现问题了！
	//v.push_back(6);
	yufc::vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//
	auto p = find(v.begin(), v.end(), 3);
	if (p != v.end()) {
		v.insert(p, 30);

		//在内部初步解决迭代器失效之后，其实问题还是没有根本解决！
		//因为内部的pos更新不会影响p
		//所以我们在使用的时候
		//在p位置插入数据以后，不要访问p，因为p可能失效了
		//因为我们使用STL的时候，不了解底层的扩容机制，所以以后我们insert之后，不要去访问p位置！ -- 可能会有问题

		//那能否把insert第一个参数改成&行吗？ -- 尽量不要这样做 -- 和库保持一致好
		//虽然我们看似解决了问题 -- 但是改了可能会引出其它问题 -- 比如，头插，我们想传v.begin();v.insert(v.begin(), 0);
		//编不过，因为类型不匹配
#if 0
		cout << *p << endl;
		v.insert(p, 40);
#endif
	}
	PrintVector(v);
}
//erase迭代器会失效吗？
//库里面的erase会失效吗？ -- 不知道
//STL并没有规定什么机制
//有没有一种可能，当size()<capacity()/2的时候，缩一下容（缩容：以时间换空间）
//反正用完那个别访问，别动那个p就行了！
void test_vector5() {
	yufc::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	auto p = find(v.begin(), v.end(), 3);
	if (p != v.end()) {
		v.erase(p);
	}
	PrintVector(v);
}
void test_vector6() {
	yufc::vector<int>v;
#if 0
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
#endif
	//情况1和2
	//我们发现此时有这个5 -- 程序正常，没有 -- 崩溃
#if 1
	//情况3
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
#endif
	//要求删除所有的偶数
	auto it = v.begin();
	//情况3的时候，it会跳过end()，直接继续往后了 -- 崩溃
	//所以下面这段算法是不正确的！
	//其实我们看源代码可以发现 -- erase是有返回值的 -- 会更新一下迭代器
	//STL规定erase返回删除位置下一个位置的迭代器！
	//vs这个编译器是查的很严格的 -- erase之后不允许去访问！ -- 访问就报错
	//Linux下就不同
	while (it != v.end()) {
		if (*it % 2 == 0) {
			it = v.erase(it);//我们要返回一个it才行
		}
		else {
			++it;
		}
	}
	PrintVector(v);
}
//总结
//其实迭代器失效，我们在自己做OJ的时候也能体会的，插入或者删除之后，迭代器指向了它不该指向的地方
//在使用vector的迭代器的时候，要多调试！

void test_vector7() {
	//系统默认的拷贝
	//1.自定义类型 -- 调拷贝构造 -- 默认生成的 -- 浅拷贝
	//2.内置类型 -- 值拷贝 -- 浅拷贝
	yufc::vector<int>arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	yufc::vector<int>arr2 = arr;
	//调用系统默认的话就是浅拷贝，这样程序肯定会崩溃的 -- 析构了两次
	//而且如果是浅拷贝，改一边的值另一边也会被改变
	arr2[0] = 100; //两边都会被改变的 -- 所以我们需要深拷贝！
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : arr2) {
		cout << i << " ";
	}
}
void test_vector8() {
	string s("hell");
	yufc::vector<int>vs(s.begin(), s.end());
	for (auto i : vs) {
		cout << i << " ";
	}
	cout << endl;
	//赋值
	yufc::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	vs = v;//要实现一个深拷贝
	//当然，如果f11 -- 这里是先进去拷贝的，因为传参要拷贝
	//走完拷贝就进去赋值了
	for (auto i : vs) {
		cout << i << " ";
	}
}
//其实内置类型也有构造
void test_type() {
	int i = 0;
	int j = int();
	int k = int(10);
}
void test_vector9() {
	//vector<int>v = { 1,2,3,4,5 };
	vector<int>v(10);
	yufc::vector<int>v(10, 1);//这样就报错了,如果传了两个参数都是int
	//这里出问题就是匹配问题，它匹配到不该去的地方去了
	//为什么 -- 因为迭代器区间构造那个函数，更适合这样传参 -- 所以进到那里去了
	//解决：
	//1.传参的时候写(10u,1)表示这个是个usigned int类型
	//2.把vector(size_t n,const T&val=T())里面的size_t改成int，也可以解决 -- 但是stl官方给的是size_t
	//3.复制一份，改成int，弄个重载就行 -- stl_3.0是这样解决的
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}
void test_vector10() {
	yufc::vector<int>v;
	v.resize(10, 1);
	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;

	yufc::vector<int>v1;
	v1.reserve(10);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.resize(8, 8);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;

	v1.resize(20, 20);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;

	v1.resize(3);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;
}


//vector到目前为止还有最后一个坑还没有解决
//我们用自己的vector测试一下杨辉三角
class Solution {
public:
	yufc::vector<yufc::vector<int>> generate(int numRows) {
		yufc::vector<yufc::vector<int>> ret(numRows);
		for (int i = 0; i < numRows; ++i) {
			ret[i].resize(i + 1);
			ret[i][0] = ret[i][i] = 1;
			for (int j = 1; j < i; ++j) {
				ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
			}
		}
		return ret;
	}
};
void test_vector11() {
	Solution().generate(10);
	//报错 -- 在函数结束的时候崩溃了
	//修改一下 -- 把函数改成void类型，不return -- 没事了
	//为什么？
	//拷贝有问题了 -- 普通的vector深拷贝没问题 -- 这里的深拷贝有问题
	//里面是浅拷贝，外面是深拷贝
	// //            //即：我们的vector是深拷贝了 -- 但是里面的自定义类型没有深拷贝！！！！！！！！！！
	//我们拷贝的时候，外面的空间是深拷贝，但是里面的东西，还是指向以前的地方
	//传统写法是因为memcpy导致的 -- 我们将memcpy改成一个一个赋值就行了（这样的话自定义类型也可以完成深拷贝（调用自己的deepcopy））
	//现代写法是因为因为要调用push_back()，而push_back()里面调用reserve(),是reserve()里面的memcpy出问题
}
int main() {
	//test_vector1();
	//test_vector2();
	//test_vector3();
	//test_vector4();
	//test_vector5();
	//test_vector6();
	//test_vector7();
	//test_vector8();
	//test_type();
	//test_vector9();
	//test_vector10();
	test_vector11();
	return 0;
}


//我们一定要清晰一个点：
//STL只是一个规范
//这个规范怎么去实现，是没有规定的！
//VS-PJ版   g++ SGI版