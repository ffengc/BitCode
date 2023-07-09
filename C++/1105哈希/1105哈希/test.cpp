#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
using namespace std;
#elif
#endif

#include<iostream>
#include<algorithm>
/*
#include<unordered_map>
#include<unordered_set>
*/
//的用法和map/set是一样的

//unordered系列只有单向迭代器

#if 0
//961. 在长度 2N 的数组中找出重复 N 次的元素
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_map<int, int>hash;
        for (int i = 0; i < nums.size(); i++) {
            ++hash[nums[i]];
            if (hash[nums[i]] == nums.size() / 2)return nums[i];
        }
        return -1;
    }
};
//区别
//1.map/set遍历时有序，u_map,u_set无序
//2.map/set是双向迭代器，u_map/u_set是单向的
//基于上面两点而言 -- set/map更强大，为什么需要u系列？

//大量查找的时候u_map/u_set更快！

//性能对比
void test_op()
{
	int n = 10000000;
	vector<int> v;
	v.reserve(n);
	srand(time(0));
	for (int i = 0; i < n; ++i)
	{
		//v.push_back(i);
		v.push_back(rand() + i);  // 重复少
		//v.push_back(rand());  // 重复多
	}

	size_t begin1 = clock();
	set<int> s;
	for (auto e : v)
	{
		s.insert(e);
	}
	size_t end1 = clock();

	size_t begin2 = clock();
	unordered_set<int> us;
	for (auto e : v)
	{
		us.insert(e);
	}
	size_t end2 = clock();

	cout << "size:" << s.size() << endl;

	cout << "set insert:" << end1 - begin1 << endl;
	cout << "unordered_set insert:" << end2 - begin2 << endl;


	size_t begin3 = clock();
	for (auto e : v)
	{
		s.find(e);
	}
	size_t end3 = clock();

	size_t begin4 = clock();
	for (auto e : v)
	{
		us.find(e);
	}
	size_t end4 = clock();
	cout << "set find:" << end3 - begin3 << endl;
	cout << "unordered_set find:" << end4 - begin4 << endl;


	size_t begin5 = clock();
	for (auto e : v)
	{
		s.erase(e);
	}
	size_t end5 = clock();
	cout << "set erase" << endl;

	size_t begin6 = clock();
	for (auto e : v)
	{
		us.erase(e);
	}
	size_t end6 = clock();
	cout << "unordered_set erase" << endl;

	cout << "set erase:" << end5 - begin5 << endl;
	cout << "unordered_set erase:" << end6 - begin6 << endl;

	unordered_map<string, int> countMap;
	countMap.insert(make_pair("2", 1));
}
int main() {
	test_op();
	return 0;
}
#endif


//#include"closed_hash.h"
#include"open_hash.h"
int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
	return 0;
}