#define _CRT_SECURE_NO_WARNINGS 1
#include"MyStack.h"
#include"MyQueue.h"
#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<functional>
#include"MyPriorityQueue.h"
using namespace std;

void test_stack() {
	//yufc::stack<int,vector<int>>st; //适配 -- 传一个vector<int>类型过去
	//yufc::stack<int, list<int>>st;
	//vector和list其实底层已经完全变样了 -- 但是还是可以正常使用的
	yufc::stack<int>st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
}
void test_queue() {
	//yufc::queue<int>q;
	yufc::queue<int, list<int>>q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
}
void test_priority_queue() {
	yufc::priority_queue<int,vector<int>,less<int>>pq; //底层是个堆
	//默认是大顶堆 -- 大的优先级高
	pq.push(3);
	pq.push(1);
	pq.push(2);
	pq.push(5);
	pq.push(0);
	pq.push(1);
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
	int a[] = { 1,3,5,7,9,2,4,6,8,0 };
	yufc::priority_queue<int>pq1(a, a + sizeof(a) / sizeof(int));
	while (!pq1.empty()) {
		cout << pq1.top() << " ";
		pq1.pop();
	}
	cout << endl;
	//priority_queue<int>heap(a, a + sizeof(a) / sizeof(int));//这样构造也可以
	//如果想控制是小的优先级高呢？
	//我们要调整第三个模板参数，如果想传第三个，就必须传第二个
	priority_queue<int,vector<int>,greater<int>>heap(a, a + sizeof(a) / sizeof(int));//这样构造也可以
	while (!heap.empty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	cout << endl;
}
#if 1
int main() {
	//test_stack();
	//test_queue();
	test_priority_queue();
	return 0;
}

//215. 数组中的第K个最大元素
//topk问题
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		//topk问题
		priority_queue<int>pq(nums.begin(), nums.end());//建堆O(n)
		while (--k) {
			pq.pop();
		}
		return pq.top();
	}
};
#endif

//仿函数 -- 函数对象 -- 类，重载了operator()
//类对象可以像函数一样去使用
#if 0
namespace yufc {
	template<class T>
	struct less {
		bool operator()(const T& l, const T& r)const {
			return l < r;
		}
	};
	template<class T>
	struct greater {
		bool operator()(const T& l, const T& r)const {
			return l > r;
		}
	};
}
int main() {
	yufc::less<int> IsFunc1;
	yufc::greater<int> IsFunc2;
	cout << IsFunc1(1, 2) << endl;
	cout << IsFunc1.operator()(1, 2) << endl;//两者等价
	cout << IsFunc2(1, 2) << endl;
	return 0;
}
#endif