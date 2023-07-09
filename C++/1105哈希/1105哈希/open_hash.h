#pragma once



#include<map>
#include<set>
#include<vector>
using namespace std;


//开散列
//拉链法
//哈希桶

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



template<class K, class V>
struct HashNode
{
	pair<K, V>_kv;
	HashNode<K, V>* _next;
	HashNode<K, V>(const pair<K, V>& kv)
		:_kv(kv), _next(nullptr) {}
};
template<class K, class V, class Hash = HashFunc<K>>
struct HashTable
{
	typedef HashNode<K, V> Node;
private:
	vector<Node*>_tables;
	size_t _size = 0;//存储的有效数据个数
public:
	HashTable() = default;
	~HashTable()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = this->_tables[i];
			while (cur)
			{
				Node* next = cur->_next;
				free(cur);
				cur = next;
			}
			_tables[i] = nullptr;
		}
	}
private:
	inline size_t __stl_next_prime(size_t n)
	{
		static const size_t __stl_num_primes = 28;
		static const size_t __stl_prime_list[__stl_num_primes] =
		{
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
		};

		for (size_t i = 0; i < __stl_num_primes; ++i)
		{
			if (__stl_prime_list[i] > n)
			{
				return __stl_prime_list[i];
			}
		}

		return -1;
	}
public:
	bool insert(const pair<K, V>& kv)
	{
		//去重
		if (find(kv.first))return false;
		//扩容
		//负载因子到1就扩容
		if (_size==_tables.size())
		{
			//同样的问题：弄个新vector好还是复用insert好？
			//这里创建vector更好
			//因为节点我们可以直接拿下来
			//size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			vector<Node*>newTables;
			//newTables.resize(newSize, nullptr);
			newTables.resize(__stl_next_prime(_tables.size()), nullptr);
			//旧表中的节点移动映射到新表
			Hash hash;
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;//因为cur会改 -- 所以提前保存下一个
					size_t hashi = hash(cur->_kv.first) % newTables.size();
					cur->_next = newTables[hashi];
					newTables[hashi] = cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
			_tables.swap(newTables);//新的和旧的交换一下
		}

		Hash hash;
		size_t hashi = hash(kv.first) % _tables.size();
		//头插？尾插？
		Node* newnode = new Node(kv);
		newnode->_next = _tables[hashi];
		_tables[hashi] = newnode;
		this->_size++;
		return true;
	}
	Node* find(const K& key) 
	{
		//先判断一下表是不是空的
		if (_tables.size() == 0)
		{
			return nullptr;
		}
		Hash hash;
		size_t hashi = hash(key) % _tables.size();
		Node* cur = _tables[hashi];
		while (cur)
		{
			if (cur->_kv.first == key)return cur;
			cur = cur->_next;
		}
		return nullptr;
	}
	bool erase(const K& key)
	{
		if (_tables.size() == 0)
		{
			return false;
		}
		Hash hash;
		size_t hashi = hash(key) % _tables.size();
		Node* cur = _tables[hashi];
		Node* prev = nullptr;
		while (cur)
		{
			if (cur->_kv.first==key)
			{
				if (prev == nullptr)
				{
					//说明删的是头
					_tables[hashi] = cur->_next;
					delete(cur);
					--this->_size;
					return true;
				}
				else
				{
					prev->_next = cur->_next;
					delete cur;
					--this->_size;
					return true;
				}
			}
			prev = cur;
			cur = cur->_next;
		}
		return false;
	}
	size_t size()
	{
		return this->_size;
	}
	size_t bucket_size()
	{
		return _tables.size();
	}
	size_t bucket_num()
	{
		size_t ret = 0;
		for (size_t i = 0; i < _tables.size(); i++)
		{
			if (_tables[i])
			{
				++ret;
			}
		}
		return ret;
	}
	size_t longest_bucket_length()
	{
		size_t max_len = 0;
		for (size_t i = 0; i < _tables.size(); i++)
		{
			size_t len = 0;
			Node* cur = _tables[i];
			while (cur)
			{
				++len;
				cur = cur->_next;
			}
			max_len = max(max_len, len);
		}
		return max_len;
	}
};

#include<iostream>
void test4()
{
	int a[] = { 1,11,4,15,26,7,44,99,55,78 };
	HashTable<int, int>ht;
	for (auto e : a) {
		ht.insert(make_pair(e, e));
	}
	ht.insert(make_pair(22, 22));
	cout << endl;
}
//把key扩展一下
void test5()
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
/**
 * 现在有一个理论：让哈希表的大小为素数 -- 这样会一定程度减少冲突
 * 但是是如何得到下一个合适的素数呢？
 * stl_hashtable.h里面是通过打表的方式的.
 */



void test6()
{
	int n = 100000;
	vector<int>v;
	v.reserve(n);
	srand(time(0));
	for (size_t i = 0; i < n; i++)
	{
		v.push_back(rand());
	}
	size_t begin1 = clock();
	HashTable<int, int>ht;
	for (auto e : v)
	{
		ht.insert(make_pair(e, e));
	}
	size_t end1 = clock();
	cout << "size():" << ht.size() << endl;
	cout << "table.size():" << ht.bucket_size() << endl;
	cout << "bucket_number():" << ht.bucket_num() << endl;
	cout << "avg_bucket_list_length: " << (double)ht.size() / ht.bucket_num() << endl;
	cout << "longest_bucket_length(): " << ht.longest_bucket_length() << endl;
	cout << endl;
}

//一般情况下，find效率都是很快的
//再再再极端 -- 我们可以挂红黑树
//一般来说挂单链就行了

//哈希表的消耗主要在哪 -- 扩容的时候重新计算位置才是耗时间的
//所以哈希表的插入不占优势的


/**
 * 现在我们回过头来看
 * u_map里面
 * bucket_count
 * max_bucket_count
 * bucket_size
 * load_factor这些接口
 * 我们就都能明白了.
 */