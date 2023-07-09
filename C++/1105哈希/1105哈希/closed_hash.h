#pragma once

#include<map>
#include<set>
#include<vector>
#include<iostream>
using namespace std;

enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template<class K, class V>
struct HashData
{
	pair<K, V>_kv;
	State _state = EMPTY;
};

template<class K>
struct HashFunc
{
	//目的就是把一个复杂类型转化成一个无符号整型
	size_t operator()(const K& key) 
	{
		return (size_t)key;
	}
};
//特化
template<>
struct HashFunc<string>
{
	//BKDR算法
	size_t operator()(const string& key)
	{
		size_t val = 0;
		for (auto ch : key)
		{
			val *= 131;
			val += ch;
		}
		return val;
	}
};


#define THRESHOLD 0.7 //负载因子阈值
//HashFunc设置成默认的仿函数 -- （针对可以直接转化成size_t的类型）
template<class K, class V, class Hash = HashFunc<K>>
class HashTable
{
public:
	bool insert(const pair<K, V>& kv)
	{
		if (find(kv.first))return false;
		if (_table.size() == 0 || (double)_size / _table.size() >= THRESHOLD)
		{
			//扩容
			//思路1：自己开vector
#if 0
			size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
			vector<HashData<K, V>>newTable;
			newTable.resize(newSize);
			//旧表的数据映射到新表
			for ()
			{

			}
			_table.swap(newTable);
#endif
			//思路2：复用insert
			size_t newSize = _table.size() == 0 ? 10 : _table.size() * 2;
			HashTable<K, V, Hash>newHT;
			newHT._table.resize(newSize);
			for (auto& e : _table)
			{
				if (e._state == EXIST)
				{
					newHT.insert(e._kv);//直接调自己的insert
				}
			}
			_table.swap(newHT._table);
		}
#if false
		Hash hash;
		size_t hashi = hash(kv.first) % _table.size();
		//线性探测
		while (_table[hashi]._state == EXIST)
		{
			++hashi;
			hashi %= _table.size();
		}
		_table[hashi]._kv = kv;
		_table[hashi]._state = EXIST;
		++_size;
#endif
		//二次探测
		Hash hash;
		size_t start = hash(kv.first) % _table.size();
		size_t i = 0;
		size_t hashi = start;
		while (_table[hashi]._state == EXIST)
		{
			++i;
			hashi = start + i * i;
			hashi %= _table.size();
		}
		_table[hashi]._kv = kv;
		_table[hashi]._state = EXIST;
		++_size;

		return true;
	}
	bool erase(const K& key) 
	{
		HashData<K, V>* ret = find(key);
		if (ret) 
		{
			ret->_state = DELETE;
			--_size;
			return true;
		}
		else 
		{
			return false;
		}
	}
	HashData<K, V>* find(const K& key)
	{
		if (_table.size() == 0)return nullptr;
		Hash hash;
		size_t hashi = hash(key) % _table.size();
		size_t start = hashi;
		while (_table[hashi]._state != EMPTY) 
		{
			if (_table[hashi]._state != DELETE && _table[hashi]._kv.first == key)//找到了
			{
				return &_table[hashi];
			}
			hashi++;
			hashi %= _table.size();
			if (hashi == start) 
			{
				break;
			}
		}
		return nullptr;//找不到
	}
	void print_for_test()
	{
		//为了方便调试写的 -- 事实上u_map底层不是用这个
		for (size_t i = 0; i < _table.size(); ++i)
		{
			if (_table[i]._state == EXIST) 
			{
				printf("[%d:%d]", i,_table[i]._kv.first);
			}
			else
			{
				printf("[%d:*]", i);
			}
		}
		cout << endl;
	}
private:
	vector<HashData<K, V>>_table;
	size_t _size = 0;
};


void test1() 
{
	int a[] = { 1,11,4,15,26,7,44,9 };
	HashTable<int, int>ht;
	for (auto e : a) {
		ht.insert(make_pair(e, e));
	}
	ht.erase(4);
	ht.print_for_test();
	cout << ht.find(44)->_kv.first << endl;
	cout << ht.find(4) << endl;
	//负数行吗
	ht.insert(make_pair(-2, -2));
	ht.print_for_test();
	cout << ht.find(-2)->_kv.first << endl;
	//我们测试发现 -- 负数也可以 -- 这是为什么？
	//计算的时候 -- 负数被提升成无符号了

}

//表里面全是delete也是没问题的


/// <summary>
/// 但如果我们的key的类型是string这些复杂类型的时候
/// 我们怎么去把它哈希化？
/// 当然这个类型肯定是可哈希类型
/// 因此我们还需要带一个仿函数 -- 即我们的哈希函数
/// </summary>

//给string类型加上仿函数之后 -- 传过去 -- 就跑通了
//但是我们发现，u_map<>是不用传仿函数的 -- 因为string还算一个比较常见的类型
//所以这里我们可以采用模板特化！
//这样我们的string就不用传了
void test2() 
{
	string arr[] = { "苹果","苹果","香蕉","西瓜","苹果","香蕉","西瓜","苹果","西瓜","香蕉","西瓜","西瓜" };
	//HashTable<string, int, HashFuncString>countHT;
	HashTable<string, int>countHT;
	for (auto& str : arr) 
	{
		auto ptr = countHT.find(str);
		if (ptr) 
		{
			ptr->_kv.second++;
		}
		else
		{
			countHT.insert(make_pair(str, 1));
		}
	}
	cout << endl;
}
void test3()
{
	HashFunc<string>hash;
	//现在我们又遇到了新问题
	cout << hash("abcd") << endl;
	cout << hash("bcad") << endl;
	cout << endl;
	cout << hash("abcd") << endl;
	cout << hash("aadd") << endl;
	//我们发现又冲突了
	//现在评分比较高的字符串哈希算法 -- BKDR算法 -- 我们采用这个对字符串哈希化
}

/** 线性探测存在的问题 */
//如果某个位置冲突很多的情况下，会导致互相占用，导致一整片冲突
//效率降低
//比如插入：
//1 11 21 31 2 3
//解决方法：二次探测
//线性探测：在当前位置+i不断探测
//二次探测：在当前位置+i^2不断探测
//	在当前位置：第一次+1，第二次+4，第三次+9... 相对而言趋向于分散
//但是二次探测没有本质上解决问题 -- 本质还是占用别人的位置