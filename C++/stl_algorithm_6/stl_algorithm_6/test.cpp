
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
using namespace std;

void print(const vector<int>& v)
{
	for (const auto& e : v)cout << e << " ";
	cout << endl;
}
void print(const set<int>& s)
{
	for (const auto& e : s)cout << e << " ";
	cout << endl;
}

//heap系列
void test1()
{
	vector<int>a = { 1,2,3,4,5 };
	make_heap(a.begin(), a.end());//先把序列处理成堆
	cout << is_heap(a.begin(), a.end()) << endl;
	print(a);
	a.push_back(6);//此时的a已经不是堆了
	print(a);
	push_heap(a.begin(), a.end());//把序列处理成堆
	print(a);
	//现在想要提取最大的元素
	pop_heap(a.begin(), a.end());//此时用堆顶元素和最后一个元素交换，这就是学习堆的时候的那个方法，一样的
	print(a);
	cout << "------------" << endl;
	vector<int>a2 = { 1,5,3,9,7 };
	make_heap(a2.begin(), a2.end());
	sort_heap(a2.begin(), a2.end());//注意，待排序的序列一定要是一个堆
	print(a2);
	cout << "sort_heap()之后，还是堆吗？" << is_heap(a2.begin(), a2.end()) << endl;
	//is_heap_until
	//Returns an iterator to the first element in the range [first,last) which is not in a valid position 
	//if the range is considered a heap (as if constructed with make_heap).
	//返回第一个不符合堆性质的元素，如果全都符合，返回不在有效位置的迭代器（例如.end()）
}
//min/max系列
void test2()
{
	//min,max
	//minmax返回的是一个pair
	cout << min(2, 4) << endl;
	cout << min({ 2,1,4 }) << endl;
	cout << minmax({ 2,1,4 }).first << " " << minmax({ 2,1,4 }).second << endl;
	cout << "-------------------------" << endl;
	set<int>s = { 1,2,3,4,5,6,7,8,9,10,0,11,-1 };
	cout << *max_element(s.begin(), s.end()) << endl;
	set<int>s2 = { 1,1 };
	cout << *max_element(s2.begin(), s2.end()) << endl;
	//minmax_element返回的是一个pair 里面装的是迭代器
	cout << *(minmax_element(s.begin(), s.end()).first) << ' ' <<
		*(minmax_element(s.begin(), s.end()).second) << endl;
}
//others
void test3()
{
	//lexicographical_compare
	//如果范围[first1，last1）在字典上比范围[first2，last2）小，则返回true
	string a = "abcdefg";
	string b = "aa";
	vector<int>v1 = { 1, 2, 3 };
	vector<int>v2 = { 1, 1, 1 };
	cout << lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) << endl;
	cout << lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl;

	//next_permutation
	//将范围（first，last）中的元素重新排列为下一个字典式更大的排列。
	next_permutation(v1.begin(), v1.end());
	print(v1);
	//prev_permutation
	//将范围（first，last）中的元素重新排列为先前的字典顺序排列
	prev_permutation(v1.begin(), v1.end());
	print(v1);
}
int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}
