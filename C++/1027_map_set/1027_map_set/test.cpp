#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>
#include<set>
#include<algorithm>
#include<numeric>
#include<queue>
#include<assert.h>
#include<map>
#include<set>

using namespace std;

#elif
#endif


//set
#if 0
void test1() {
	//set<int>s;
#if 0
#if 1
	int arr[] = { 1,2,1,6,3,8,5 };
	//排序 + 去重
	set<int>s(arr, arr + sizeof(arr) / sizeof(int));
	set<int>::iterator it = s.begin();
	//中序
	while (it != s.end()) {
		cout << *it << " ";
		it++;
		//*it = 3;//err 不支持改，key是不能改的
	}
	cout << endl;
	for (auto e : s) {
		cout << e << " ";
	}
	cout << endl;
#else
	int arr[] = { 1,2,1,6,3,8,5 };
	//排序 + 去重 -- 降序
	set<int, greater<int>>s(arr, arr + sizeof(arr) / sizeof(int));
	set<int>::iterator it = s.begin();
	//中序
	while (it != s.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	for (auto e : s) {
		cout << e << " ";
	}
	cout << endl;
#endif
#endif
	int arr2[] = { 1,2,1,6,3,8,5 };
	//排序 + 去重
	set<int>s2(arr2, arr2 + sizeof(arr2) / sizeof(int));
	set<int>::iterator it = s2.begin();
	//中序
	while (it != s2.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	for (auto e : s2) {
		cout << e << " ";
	}
	cout << endl;
	auto pos = s2.find(2);
	if (pos == s2.end())exit(-1);
	s2.erase(pos);
	for (auto e : s2) {
		cout << e << " ";
	}
}
void test2() {
	int arr[] = { 1,2,1,6,3,8,5 };
	set<int>s(arr, arr + sizeof(arr) / sizeof(arr[0]));
	cout << s.count(2) << endl;//判断在不在可以用这里
	cout << s.count(20) << endl;
	//count在普通的set里面不是1就是0 
	//count其实是为了multiple_set设计的，它和set的区别就是它可以允许键值冗余
}
void test3() {
	//lower_bound和upper_bound
	std::set<int> myset;
	std::set<int>::iterator itlow, itup;
	for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
	itlow = myset.lower_bound(30);				  //       ^
	//itlow = myset.lower_bound(35);                
	itup = myset.upper_bound(60);//70              //                   ^
	cout << "[" << *itlow << "," << *itup << "]" << endl;
	//所以我们可以得出 -- lower_bound返回的是大于等于val的位置的迭代器
	//upper_bound也是放回大于val的位置的迭代器
	
	//lower_bound是返回大于等于的
	//upper_bound返回的是大于的
	myset.erase(itlow, itup);                     // 10 20 70 80 90
	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
void test4() {
	std::set<int> myset;
	for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50
	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);
	ret = myset.equal_range(35);
	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}
int main() {
	//不要轻易深拷贝一棵树 -- 代价很大
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}
#endif


//multiset
//用法和set没有去边
#if 0
void print(multiset<int>& ms) {
	multiset<int>::iterator it = ms.begin();
	while (it != ms.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test1() {
	int arr[] = { 1,2,1,6,3,8,3,5,3 };
	//排序 -- 但不去重
	multiset<int>s(arr, arr + sizeof(arr) / sizeof(arr[0]));
	print(s);
	cout << s.count(1) << endl;
	auto pos = s.find(3);//返回的是中序的第一个3
	while (pos != s.end()) {
		cout << *pos << " ";
		++pos;
	}
	cout << endl;

	s.erase(3);//删除所有的
	print(s);
}
int main(){
	test1();
	return 0;
}
#endif



//map
#if 0
void test1() {
	map<string, string>dict;
	//pair<string, string>kv1("sort", "排序");
	//dict.insert(kv1);
	//这样写太复杂了 -- 我们直接用匿名对象
#if 0
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<string, string>("test", "测试"));
	dict.insert(pair<string, string>("string", "字符串"));
	dict.insert(pair<string, string>("string", "xxx"));//这个肯定是插不进去的
	cout << endl;
#endif
	//上面这样写也很繁琐
	//可以用make_pair -- 它是一个函数模板
	dict.insert(make_pair("sort", "排序"));
	dict.insert(make_pair("test", "测试"));
	dict.insert(make_pair("string", "字符串"));
	dict.insert(make_pair("string", "xxx"));

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end()) {
		//pair是没有重载流插入的
		cout << "key:" << it->first << "   val:" << it->second << endl;
		it++;
	}
	//这样也可以
	for (const auto& kv : dict) {
		//记得给kv加上& 不然pair就要被深拷贝了
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;
}
int main() {
	test1();
	return 0;
}
#endif



