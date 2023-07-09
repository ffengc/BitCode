#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<functional>
using namespace std;

//这个命名空间会和自己写的合并
namespace std {
	//打印顺序表
	void PrintVector(vector<int>v) {
		for (size_t i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}
	//构造
	void test_vector1() {
		vector<int> v1;//构造
		vector<int> v2(10, 1);//用10个1构造
		vector<int> v3(v1);//拷贝构造
	}
	//
	void test_vector2() {
		vector<int> v1;//构造
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//下标+[]
		for (int i = 0; i < v1.size(); i++) {
			v1[i]++;
		}
		for (size_t i = 0; i < v1.size(); i++) {
			cout << v1[i] << " ";
		}
		cout << endl;
		//迭代器
		vector<int>::iterator it = v1.begin();
		while (it != v1.end()) {
			(*it)--;//可以修改
			cout << *it << " ";
			++it;
		}
		cout << endl;
		//const迭代器 -- 只读不写
		//反向迭代器是一样的

		//范围for
		for (auto e : v1) {
			cout << e << " ";
		}
		cout << endl;
	}
	//扩容机制我们可以自己写个代码在vs和g++下面试
	void test_vector3() {
		vector<int> v1;//构造
		v1.reserve(100);
		cout << v1.capacity() << endl;
	}
	//vector里面是没有实现find的，这个和string不同，string可能是找字符，找字串
	//vector/list这些去找数据，都是在迭代器区间里面去找的
	//#include<algorithm> -- 用这个里面的find就行 -- 传迭代器区间就行
	//insert
	void test_vector4() {
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//现在要在3前面插入一个30
		vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);//查找3
		//find如果找不到，返回的是给的右区间的位置（左闭右开） -- 这里如果找不到，返回的是v1.end()
		//返回的是一个迭代器类型
		if (pos != v1.end()) {
			//检查返回值
			v1.insert(pos, 30);
		}
		for (size_t i = 0; i < v1.size(); i++) {
			cout << v1[i] << " ";
		}
		cout << endl;
	}
	//erase -- 删除某个位置/删除某个迭代器区间
	void test_vector5() {
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//现在要删除3
		vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);
		if (pos != v1.end()) {
			//检查返回值
			v1.erase(pos);
		}
		PrintVector(v1);


		//删除一个区间
		v1.erase(v1.begin(), v1.end() - 2);
		PrintVector(v1);
	}
	void test_vector6() {
		//排序
		vector<int>v = { 4,5,1,2,7,8,10,2,3 };
		//sort -- 快排
		//传迭代器区间就行
		sort(v.begin(), v.end());
		PrintVector(v);
		//降序 -- 仿函数，等到stack和queue再去讲
		less<int>ls;// 升序
		greater<int> gt;// 降序
		//sort(v.begin(), v.end(), ls);
		sort(v.begin(), v.end(), greater<int>());//这样写也可以 -- 匿名对象
		PrintVector(v);

		vector<string>strV;
		strV.push_back("1234");
		strV.push_back("2345");
		//为什么这里要加引用
		//因为vector里面存的是string对象！
		//如果不加引用，是要调用拷贝构造的，是深拷贝！
		for (const auto& str : strV) {
			cout << str << endl;
		}
	}
}
int main() {
	//std::test_vector1();
	//std::test_vector2();
	//std::test_vector3();
	//std::test_vector4();
	//std::test_vector5();
	std::test_vector6();
	return 0;
}