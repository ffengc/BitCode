#pragma once

//布隆过滤器

#include"BitSet.h"
#include<algorithm>
#include<string>
using namespace std;



namespace yfc
{	
	template<class K = string>
	struct HashBKDR
	{
		size_t operator()(const K& key)
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
	template<class K = string>
	struct HashAP
	{
		size_t operator()(const K& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); i++)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ key[i] ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ key[i] ^ (hash >> 5)));
				}
			}
			return hash;
		}
	};
	template<class K = string>
	struct HashDJB
	{
		size_t operator()(const K& key)
		{
			size_t hash = 5381;
			for (auto ch : key)
			{
				hash += (hash << 5) + ch;
			}
			return hash;
		}
	};

	template<size_t N, class K = string,
		class Hash1 = HashBKDR<string>,
		class Hash2 = HashAP<string>,
		class Hash3 = HashDJB<string>>
	class BloomFilter
	{
	private:
		const static size_t _ratio = 5;
		bit_set<_ratio* N> _bits;
		//如果使用std::bitset
		//考虑放到堆上new一个
		//因为std::bit有个隐藏的bug会把栈撑爆
	public:
		void set(const K& key)
		{
			size_t hash1 = Hash1()(key) % (_ratio * N);
			_bits.set(hash1);
			size_t hash2 = Hash2()(key) % (_ratio * N);
			_bits.set(hash2);
			size_t hash3 = Hash3()(key) % (_ratio * N);
			_bits.set(hash3);
		}
		bool test(const K& key)
		{
			size_t hash1 = Hash1()(key) % (_ratio * N);
			if (!_bits.test(hash1))return false;
			size_t hash2 = Hash2()(key) % (_ratio * N);
			if (!_bits.test(hash2))return false;
			size_t hash3 = Hash3()(key) % (_ratio * N);
			if (!_bits.test(hash3))return false;

			return true;//可能存在误判 -- 上面的不在是准确的
		}
	};
	void testBloomFilter1()
	{
		BloomFilter<10>bf;
		string arr[] = { "苹果","西瓜","阿里","美团","苹果","字节","西瓜","苹果","香蕉","苹果","腾讯" };
		for (auto& str : arr)
		{
			bf.set(str);
		}
		for (auto& str : arr)
		{
			cout << bf.test(str) << endl;
		}
	}
	//测误判率的性能测试
	void TestBloomFilter2()
	{
		srand(time(0));
		const size_t N = 100000;
		BloomFilter<N> bf;
		cout << sizeof(bf) << endl;

		std::vector<std::string> v1;
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";

		for (size_t i = 0; i < N; ++i)
		{
			v1.push_back(url + std::to_string(1234 + i));
		}

		for (auto& str : v1)
		{
			bf.set(str);
		}

		// 相似
		std::vector<std::string> v2;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "http://www.cnblogs.com/-clq/archive/2021/05/31/2528153.html";
			url += std::to_string(rand() + i);
			v2.push_back(url);
		}

		size_t n2 = 0;
		for (auto& str : v2)
		{
			if (bf.test(str))
			{
				++n2;
			}
		}
		cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;

		std::vector<std::string> v3;
		for (size_t i = 0; i < N; ++i)
		{
			string url = "zhihu.com";
			url += std::to_string(rand() + i);
			v3.push_back(url);
		}

		size_t n3 = 0;
		for (auto& str : v3)
		{
			if (bf.test(str))
			{
				++n3;
			}
		}
		cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;
	}
}