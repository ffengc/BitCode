#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>
#include<set>
#include<algorithm>
#include<numeric>
#include<queue>
#include<assert.h>
#include<map>
#include<set>
using namespace std;
#elif

#endif

void test1() {
	string arr[] = { "苹果","西瓜","苹果","西瓜" ,"苹果" ,
		"苹果" ,"西瓜" ,"苹果" ,"香蕉" ,"苹果","香蕉" };
	//统计次数
	map<string, int>countMap;
	//方法1
#if 0
	for (auto& str : arr) {
		map<string, int>::iterator it = countMap.find(str);
		if (it != countMap.end()) {
			it->second++;
		}
		else {
			countMap.insert(make_pair(str, 1));
		}
	}
	auto it = countMap.begin();
	while (it != countMap.end()) {
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
#endif
	//方法2 -- 用[]
	for (auto& str : arr) {
		//[]如果没有找到 -- 即插入一个新的key，并调用val的默认构造，int就是0
		countMap[str]++;
	}
	auto it = countMap.begin();
	while (it != countMap.end()) {
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}
void test2() {
	map<string, string>dict;
	dict.insert(make_pair("sort", "排序"));
	dict["insert"];
	dict["insert"] = "插入";
	dict["left"] = "左边";
	//1.map中有这个key，返回val的引用（查找、修改val）
	//2.map没有这个key，会插入一个pair(key,V()); -- V()匿名对象 -- 调用default_constructor()
		//即插入+修改
}
void test3() {
	//multimap 不支持[]
	multimap<string, string>mdict;
	//其它的和multiset一样 我们简单演示一下就行
	//只看key -- 无论怎么样都插入
	mdict.insert(make_pair("sort", "排序"));
	mdict.insert(make_pair("left", "左边"));
	mdict.insert(make_pair("left", "左边"));
	mdict.insert(make_pair("left", "剩余"));
}
int main() {
	//test1();
	//test2();
	return 0;
}


//692. 前K个高频单词
//1.用优先级队列
class Solution {
private:
	struct less {
		bool operator()(const pair<string, int>& kv1, const pair<string, int>& kv2)const {
			if (kv1.second < kv2.second)return true;
			if (kv1.second == kv2.second && kv1.first > kv2.first)return true;
			return false;
		}
	};
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int>countMap;//如果用优先队列 -- 这里直接换成哈希更快
		for (auto& str : words) {
			countMap[str]++;
		}
		//topk
		typedef priority_queue<pair<string, int>, vector<pair<string, int>>, less> maxHeap;
		maxHeap mh(countMap.begin(), countMap.end());
		vector<string>v;
		while (k--) {
			pair<string, int>kv = mh.top();
			mh.pop();
			v.push_back(kv.first);
		}
		return v;
	}
};

//方法2：直接用map的性质
class Solution {
	struct greater {
		bool operator()(const pair<string, int>& kv1, const pair<string, int>& kv2)const {
			if (kv1.second > kv2.second)return true;
			//如果我们用稳定排序 -- 就不用下面这个if了
			/*if (kv1.second == kv2.second && kv1.first < kv2.first) {
				return true;
			}*/
			return false;
		}
	};
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int>countMap;
		for (auto& str : words) {
			countMap[str]++;
		}
		//我们考虑可以用一个排序
		//但是这个排序一定是要稳定的
		//因为在map里面的key已经是按照字典序排序了，现在我们要对它的val排序
		//排序完成之后希望还是保持原来的字典序
		vector<pair<string, int>>sortV(countMap.begin(), countMap.end());

		//sort(sortV.begin(), sortV.end(), greater());//err 这个是个不稳定排序
		//我们可以用一个稳定排序 -- 我们也可以给greater()增加条件 -- 也可以满足题目要求
		//后者不是让函数稳定 -- 而是通过给多一个比较条件 -- 让它满足题目要求
		
		//sort(sortV.begin(), sortV.end(), greater());
		stable_sort(sortV.begin(), sortV.end(), greater());

		vector<string>v;
		for (int i = 0; i < k; ++i) {
			v.push_back(sortV[i].first);
		}
		return v;
	}
};


//如果不用仿函数 -- 还能怎么办
//我们可以用map排序
//我们颠倒一下，变成<int,string>，对val排序
//但是我们要注意 -- map是会去重的，我们的val是有可能有重复的 -- 不能去重
//所以使用multimap
class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int>countMap;
		for (auto& str : words) {
			countMap[str]++;
		}

		multimap<int, string, greater<int>>sortMap;//因为这里是按val排，val是int，所以仿函数不用自己写了
		//注意：不能用反向迭代器去走 -- 因为倒着走字典序又反了
		//我们既要字典序是正的，又要出现次数的数字是降序 -- 所以给个int的仿函数
		for (auto& kv : countMap) {
			sortMap.insert({ kv.second,kv.first });//颠倒一下
			//因为multimap重复的是默认往右边插，所以这里其实自带了一个稳定
		}
		//现在排好了
		vector<string>v;
		multimap<int, string, greater<int>>::iterator it = sortMap.begin();
		for (int i = 0; i < k; i++) {
			v.push_back(it->second);
			it++;
		}
		return v;
	}
};


//除了map/set之外，我们还可以用<algorithm>里面的unique对有序序列去重

//349. 两个数组的交集
/*
* 算法：（前提是有序）
* 找交集：
* 1.小的++
* 2.相等的就是交集，同时++
* 找差集：
* 1.小的就是差集
* 2.相等就同时++
*/
class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		set<int>s1(nums1.begin(), nums1.end());
		set<int>s2(nums2.begin(), nums2.end());
		auto it1 = s1.begin();
		auto it2 = s2.begin();
		vector<int>ret;
		while (it1 != s1.end() && it2 != s2.end()) {
			if (*it1 < *it2) {
				++it1;
			}
			else if (*it1 > *it2) {
				++it2;
			}
			else {
				ret.push_back(*it1);
				++it1;
				++it2;
			}
		}
		return ret;
	}
};