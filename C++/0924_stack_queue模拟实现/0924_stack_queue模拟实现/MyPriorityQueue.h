#pragma once
#include<vector>


using namespace std;
namespace yufc {
	template<class T, class Container = vector<T>, class Compare = std::less<T>>
													//默认是less  Compare是一个进行比较的仿函数
													//less -- 小堆
	class priority_queue {
	public:
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last) {
			while (first != last) {
				//不要直接去push，push调用的是向上调整，会慢很多
				//先弄进数组再建堆快一点，用向下调整
				_con.push_back(*first);
				++first;
			}
			//建堆
			for (int i = ((_con.size() - 1 - 1) / 2); i >= 0; i--) {
				adjust_down(i);
			}
		}
		//如果写了这个构造编译器就不会生成其它类型构造了，所以要自己写
		priority_queue() {}
		void adjust_up(size_t child) {
			Compare cmp;
			size_t parent = (child - 1) / 2;//找到父亲节点的下标
			while (child > 0) { //logn
				//if (_con[child] > _con[parent]) {
				//if (_con[parent] < _con[child]) {
				if (cmp(_con[parent],_con[child])) {
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else break;
			}
		}
		void adjust_down(size_t parent) {
			Compare cmp;
			size_t child = parent * 2 + 1;
			while (child < _con.size()) {
				//选出左右孩子中大的那个
				if (child + 1 < _con.size() && cmp(_con[child], _con[child + 1])) {
					++child;
				}
				if (cmp(_con[parent], _con[child])) {
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else break;//已经调整结束了，不用再调整了
			}
		}
		void push(const T& x) {
			_con.push_back(x);
			adjust_up(_con.size() - 1);
		}
		void pop() {
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}
		const T& top() {
			//返回值不允许修改 -- 修改了就不是堆了
			return _con[0];
		}
		bool empty() const {
			return _con.empty();
		}
		size_t size() const {
			return _con.size();
		}
	private:
		Container _con;
	};
}


//priority_queue
//stack
//queue 
//都是经典 容器适配器