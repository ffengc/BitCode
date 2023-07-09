#pragma once

#include<vector>
#include<deque>
using namespace std;


namespace yufc {
	template<class T, class Container = deque<T>>
	class queue {
	public:
		void push(const T& x) {
			_con.push_back(x);
		}
		void pop() {
			_con.pop_front();
		}
		T& back() {
			return _con.back();
		}
		T& front() {
			return _con.front();
		}
		//const也可以补上
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