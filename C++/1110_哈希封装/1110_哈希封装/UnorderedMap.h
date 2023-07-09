#pragma once

#include"open_hash.h"
using namespace std;

//tips:  deepcopy hasn't realize

namespace yfc
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, Hash, MapKeyOfT>::iterator iterator;//迭代器
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
		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.insert(kv);
		}
		bool erase(const K& key)
		{
			return _ht.erase(key);
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		HashTable<K, pair<K, V>, Hash, MapKeyOfT>_ht;
	};
	//=================测试==================
	void test_map1()
	{
		unordered_map<string, string>dict;
		dict.insert(make_pair("a", "A"));
		dict.insert(make_pair("b", "B"));
		dict.insert(make_pair("c", "C"));
		dict.insert(make_pair("d", "D"));
		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
	}
	void test_map2()
	{
		string arr[] = { "苹果","苹果","香蕉","西瓜","苹果","香蕉","西瓜","苹果","西瓜","香蕉","西瓜","西瓜" };
		//HashTable<string, int, HashFuncString>countHT;
		unordered_map<string, int>map;
		for (auto& str : arr)
		{
			map[str]++;
		}
		for (auto& kv : map) 
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;
	}
}