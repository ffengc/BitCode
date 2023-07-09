#pragma once
#include<vector>
#include<deque>
using namespace std;


namespace yufc {
	//template<class T> //现在这个还不是适配器因为底层是写死的
	template<class T, class Container = deque<T>>
	class stack {
	public:
		//构造析构拷贝构造要不要写 -- 不用
		void push(const T& x) {
			_con.push_back(x);
		}
		void pop() {
			_con.pop_back();
		}
		T& top() {
			return _con.back();
		}
		bool empty() const {
			return _con.empty();
		}
		size_t size() const {
			return _con.size();
		}
	private:
		//vector<T>_con;
		Container _con;
		//我的Container到底是什么不重要，只需要它有这几个操作就行了
	};
}

//queue 双端队列
//1.支持任意位置的插入删除
//2.随机访问
//vector和list的合体 -- 看其实没有很牛 -- 外强中干

//优势：3D，头尾插入删除，随机访问
//设计缺陷：
//1.operator[]计算稍显复杂，大量使用性能下降
//2.中间插入删除效率不高
//3.迭代器会很复杂！


//优先级队列
//priority_queue