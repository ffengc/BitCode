#pragma once

#include"RBTree.h"

namespace yufc{
	template<class K>
	class set {
		struct SetKeyOfT {
			const K& operator()(const K& key) {
				return key;
			}
		};
	public:
		//µü´úÆ÷
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;
		iterator begin() {
			return _t.begin();
		}
		iterator end() {
			return _t.end();
		}
	public:
		pair<iterator, bool> insert(const K& key) {
			return _t.insert(key);
		}
	private:
		RBTree<K, K, SetKeyOfT>_t;
	};





	void test_set() {
		set<int>s;
		s.insert(3);
		s.insert(3);
		s.insert(1);
		s.insert(2);
		s.insert(5);
		s.insert(5);
		s.insert(7);
		s.insert(6);

		set<int>::iterator it = s.begin();
		while (it != s.end()) {
			cout << *it << endl;
			++it;
		}
		cout << endl;
	}
}
