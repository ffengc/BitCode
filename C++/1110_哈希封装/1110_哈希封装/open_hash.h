#pragma once

//tips:  deepcopy hasn't realize

#include<map>
#include<set>
#include<vector>
#include<string>
#include<iostream>
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



template<class T>
struct HashNode
{
	T _data;
	HashNode<T>* _next;
	HashNode(const T& data)
		:_data(data), _next(nullptr) {}
};
//前置声明一下哈希表
template<class K, class T, class Hash, class KeyOfT>
struct HashTable;
template<class K, class T, class Hash, class KeyOfT>
struct __hash_iterator
{
	typedef HashNode<T>Node;
	typedef HashTable<K, T, Hash, KeyOfT> HT;
	typedef __hash_iterator<K, T, Hash, KeyOfT>self;
	Node* _node;
	HT* _pht; //因为这里要用HashTable对象指针，所以前面要前置声明一下

	__hash_iterator(Node* node, HT* pht)
		:_node(node), _pht(pht) {}
	T& operator*()
	{
		return _node->_data;
	}
	T* operator->()
	{
		return &_node->_data;
	}
	self& operator++()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			//找下一个桶
			//首先要找到自己是哪个桶的 
			//算一下当前的哈希值就行了
			Hash hash;
			KeyOfT kot;
			size_t i = hash(kot(_node->_data)) % _pht->_tables.size();//这里是访问不了_tables的，要设置一个友元
			++i;//从下一个桶开始走
			for (; i < _pht->_tables.size(); i++)
			{
				if (_pht->_tables[i])//如果当前桶不为空
				{
				_node = _pht->_tables[i];
				break;
				}
			}
			//如果找到最后都没有找到不为空的桶 -- 也就是一开始下标为i的桶已经是最后一个桶了
			if (i == _pht->_tables.size())
			{
				_node = nullptr;
			}
		}
		return*this;
	}
	bool operator!=(const self& s)const
	{
		return _node != s._node;
	}
	bool operator==(const self& s)const
	{
		return _node == s._node;
	}
};
/// <summary>
/// 看下源码我们可以发现，以前我们都是会复用代码的 比如Ref Ptr这样复用
/// 但是在哈希表这里，是分开实现的，这肯定是有原因的

template<class K, class T, class Hash, class KeyOfT>
struct HashTable
{
private:
	typedef HashNode<T> Node;
private:
	vector<Node*>_tables;
	size_t _size = 0;//存储的有效数据个数
public:
	friend struct __hash_iterator<K, T, Hash, KeyOfT>;//让__hash_iterator可以访问_tables
	typedef __hash_iterator<K, T, Hash, KeyOfT> iterator;//迭代器
	iterator begin()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			if (_tables[i])
			{
				return iterator(_tables[i], this);//第二个参数是this，要的是哈希表的指针，给个this就行
			}
		}
		//如果一个桶都没有
		return end();
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
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
	pair<iterator, bool> insert(const T& data)
	{
		KeyOfT kot;
		//去重
		iterator ret = find(kot(data));
		if (ret != end())//已经有这个值了
		{
			return make_pair(ret, false);//插入失败
		}
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
					size_t hashi = hash(kot(cur->_data)) % newTables.size();
					cur->_next = newTables[hashi];
					newTables[hashi] = cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
			_tables.swap(newTables);//新的和旧的交换一下
		}

		Hash hash;
		size_t hashi = hash(kot(data)) % _tables.size();
		//头插？尾插？
		Node* newnode = new Node(data);
		newnode->_next = _tables[hashi];
		_tables[hashi] = newnode;
		this->_size++;
		return make_pair(iterator(newnode, this), true);//返回新节点的迭代器和true
	}
	iterator find(const K& key) 
	{
		//先判断一下表是不是空的
		if (_tables.size() == 0)
		{
			return end();//表为空 -- 返回空
		}
		Hash hash;
		KeyOfT kot;
		size_t hashi = hash(key) % _tables.size();
		Node* cur = _tables[hashi];
		while (cur)
		{
			if (kot(cur->_data) == key)return iterator(cur, this);
			cur = cur->_next;
		}
		return end();
	}
	bool erase(const K& key)
	{
		if (_tables.size() == 0)
		{
			return false;
		}
		Hash hash;
		KeyOfT kot;
		size_t hashi = hash(key) % _tables.size();
		Node* cur = _tables[hashi];
		Node* prev = nullptr;
		while (cur)
		{
			if (kot(cur->_data)==key)
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