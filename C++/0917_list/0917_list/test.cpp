#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<list>
#include<time.h>
using namespace std;
//list -- 双向循环链表
//不支持operator[]
//稍微查一下文档就能用起来了

//使用
void test_list1() {
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2); 
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	//遍历它
	list<int>::iterator it = lt.begin();
	while (it != lt.end()) { //迭代器可读也可写 -- 很简单
		//反向迭代器那些 -- 都是一样的
		//front(),back()取头和尾的数据
		cout << *it << " ";
		it++;
	}
	cout << endl;
	for (auto e : lt) {
		cout << e << " ";
	}
}
void test_list2() {
	//insert和erase
	//同样 -- 都是用迭代器
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	//在3的前面插入一个30
	auto pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end()) {
		lt.insert(pos, 30);
	}//老操作了 -- 很简单
	//问题来了：
	//pos是否会失效 -- 不会的
	//链表的结构很清楚了，不会像顺序存储那样的
	for (auto e : lt) {
		cout << e << " ";
	}
	cout << endl;
	//删除数据
	auto pos1 = find(lt.begin(), lt.end(),30);
	if (pos1 != lt.end()) {
		lt.erase(pos1);//pos会不会失效 -- 会失效！访问一下就知道了
					   //很简单 -- 节点都被delete掉了，经典的野指针问题
	}
	for (auto e : lt) {
		cout << e << " ";
	}
}
void test_list3() {
	//这些方法要用的时候去查文档就行了
	//splice 转移
	//remove 
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(2);
	lt.push_back(5);
	lt.remove(2);//删全部的 -- 查文档就行了，不一定要试
	for (auto e : lt) {
		cout << e << " ";
	}
	cout << endl;
	//remove_if 带着条件删
}
void test4() {
	list<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(2);
	lt.push_back(5);
	//unique
	//unique 去重 -- 先排序才能去
	//一般也不用这个，先排序再去，其实代价不小
	// 
	//以后用搜索树set去重
	lt.sort();
	lt.unique();
	for (auto e : lt) {
		cout << e << " ";
	}
	cout << endl;

	
	//sort
	//为什么<algorithm>已经有一个sort了，这里还要一个sort？
	//<algorithm>的sort要求物理空间是需要连续的
	//快排的实现需要算区间，还要三数取中
	// 
	//list::sort()使用的归并排序，链式结构归并空间是O(1)的
	lt.push_front(10);
	lt.sort();
	for (auto e : lt) {
		cout << e << " ";
	}
	//merge -- 归并
	//这些都用的非常少
}
//现在有n(很大)个数据需要排序，哪一种好？
//1.vector+algorithm::sort
//2.list+list::sort
//写个程序来看一下,用release跑
//vector快
//当大量数据需要访问的时候，vector的随机访问性的优势就能体现出来了
void TestOP() {
	srand(time(0));
	const int N = 10000000;
	vector<int>v;
	v.reserve(N);
	list<int>lt1;
	list<int>lt2;
	for (int i = 0; i < N; i++) {
		auto e = rand();
		v.push_back(e);
		//lt1.push_back(e);
		lt2.push_back(e);
	}
	//拷贝到vector排序，排完之后再拷贝回来
	int begin1 = clock();
	//for (auto e : lt1) {
	//	v.push_back(e);
	//}
	sort(v.begin(), v.end());
	//size_t i = 0;
	//for (auto& e : lt1) {
	//	e = v[i++];
	//}
	int end1 = clock();

	int begin2 = clock();
	lt2.sort();
	int end2 = clock();

	cout << "vectorSort" << " " << end1 - begin1 << endl;
	cout << "listSort" << " " << end2 - begin2 << endl;
}
int main() {
	//test_list1();
	//test_list2();
	//test_list3();
	//test4();
	TestOP();
	return 0;
}