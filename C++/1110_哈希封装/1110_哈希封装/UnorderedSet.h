#pragma once

#include"open_hash.h"
using namespace std;

//tips:  deepcopy hasn't realize

namespace yfc
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, Hash, SetKeyOfT>::iterator iterator;//迭代器
		//记得加typename
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
	public:
		pair<iterator, bool> insert(const K& key)
		{
			return _ht.insert(key);
		}
		bool erase(const K& key)
		{
			return _ht.erase(key);
		}
	private:
		HashTable<K, K, Hash, SetKeyOfT>_ht;
	};
	//=================测试==================
	void test_set1()
	{
		unordered_set<int>s;
		s.insert(2);
		s.insert(3);
		s.insert(1);
		s.insert(2);
		s.insert(5);
		s.insert(-1);
		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << endl;
			++it;
		}
	}
}