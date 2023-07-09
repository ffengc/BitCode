#pragma once

#include"RBTree.h"

namespace yufc {
	template<class K, class V>
	class map {
		struct MapKeyOfT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
	//迭代器
		//取模板的模板的类型 -- 所以要typename -- 告诉编译器是类型
		typedef typename RBTree <K, pair<K, V>, MapKeyOfT>::iterator iterator;
		iterator begin() {
			return _t.begin();
		}
		iterator end() {
			return _t.end();
		}
	public:
		//operator[] -- 只有map才有
		V& operator[](const K& key) {
			//如果有 -- 插入成功
			//如果没有 -- 插入失败
			pair<iterator, bool>ret = insert(make_pair(key, V()));
			return ret.first->second;
		}
	public:
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _t.insert(kv);
		}
	private:
		RBTree <K, pair<K, V>, MapKeyOfT>_t;
	};



	void test_map() {
		map<int, int>m;
		m.insert(make_pair(1, 2));
		m.insert(make_pair(5, 2));
		m.insert(make_pair(2, 2));
		m.insert(make_pair(2, 2));
		m.insert(make_pair(3, 2));
		m.insert(make_pair(4, 2));
		m.insert(make_pair(6, 2));

		cout << "测试++" << endl;
		map<int, int>::iterator it = m.begin();
		while (it != m.end()) {
			cout << it->first << endl;
			++it;
		}
		cout << "测试--" << endl;
		//--it;
		//while (it != m.begin()) {
		//	cout << it->first << endl;
		//	--it;
		//}
		cout << endl;
	}
	void test_map2() {
		string arr[] = { "苹果","香蕉","苹果","苹果","西瓜","香蕉","苹果","苹果" };
		map<string, int>hash;
		for (auto& str : arr) {
			hash[str]++;
		}
		//map<string, int>::iterator it = hash.begin();
		//while (it != hash.end()) {
		//	cout << it->first << ":" << it->second << endl;
		//	++it;
		//}
		//范围for
		for (auto& e : hash) {
			cout << e.first << ":" << e.second << endl;
		}
	}
}