
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include<algorithm>
#include<vector>
#include<array>
#include<iostream>
using namespace std;


//sort系列
void print_vector(const vector<int>& v)
{
	for (const auto& e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
}
template<class iterator>
void print_vector(iterator begin, iterator end)
{
	while (begin != end)
	{
		cout << *begin++ << " ";
	}
	cout << endl;
}
void test1()
{
	vector<int>a = { 1,3,2,7,9,5,4,6,8,10 };
	sort(a.begin(), a.end());
	print_vector(a);

	//stable_sort 稳定的排序
	vector<int>a2 = { 1,3,5,7,9,2,4,6,8,10 };
	stable_sort(a2.begin(), a2.end());
	print_vector(a2);

	//partial_sort
	//重新排列范围[第一个，最后一个）中的元素，使中间之前的元素是整个范围中最小的元素，
	//并按升序排序，而其余的元素没有任何特定的顺序。
	//即只排了前半部分
	vector<int>a3 = { 1,3,5,7,9,2,4,6,8,10 };
	partial_sort(a3.begin(), a3.begin() + 5, a3.end());
	print_vector(a3);

	//partial_sort_copy
	//将[first，last）范围内的最小元素复制到[result_first，result_last），
	//对复制的元素进行排序。复制的元素数量与result_firs和result_last之间的距离相同（除非这大于[first、last）中的元素数量）。
	//没搞懂是干啥的
	/*vector<int>a4 = { 1,3,5,7,9,2,4,6,8,10 };
	vector<int>res(10);
	partial_sort(a4.begin(), a4.end(), res.begin());
	print_vector(a4);*/ //err
}
//sort系列
void test2()
{
	//is_sorted 判断是否是升序
	vector<int>a = { 1,2,3,4,5 };
	cout << is_sorted(a.begin(), a.end()) << endl;
	//is_sorted_until 返回范围[first，last）中不遵循升序的第一个元素的迭代器
	vector<int>a1 = { 1,2,3,4,5,2,3,1,3,4 };
	auto it = is_sorted_until(a1.begin(), a1.end());
	print_vector(it, a1.end());

	//nth_element
	//重新排列范围[first，last]中的元素，以使第n个位置的元素是排序序列中位于该位置的元素 -- 还没搞懂
	vector<int>a2 = { 1,8,7,6,5,4,3,9 };
	nth_element(a2.begin(), a2.begin() + 4, a2.end());
	print_vector(a2);
}

//二分查找系列
//要在分区/有序序列上操作
void test3()
{
	//lower_bound
	//返回一个迭代器，该迭代器指向范围[first，last）中的第一个元素，该元素的比较值不小于val

	//upper_bound
	//返回一个迭代器，该迭代器指向范围[first，last）中比较值大于val的第一个元素

	//equal_range
	//返回子范围的边界，该子范围包含范围（first，last）值等于val的所有元素
	vector<int>a = { 1,2,3,4,4,4,4,5,6,7,8,9 };//需要是有序序列
	pair<vector<int>::iterator, vector<int>::iterator>p = equal_range(a.begin(), a.end(), 4);
	print_vector(p.first, p.second);

	//binary_search 二分查找
	//找到了 -- 返回true，否则返回false
	cout << binary_search(a.begin(), a.end(), 4) << endl;
}

//merge系列
//序列要有序
void test4()
{
	//merge
	//将排序范围[first1，last1）和[first2，last2）中的元素组合成一个新的范围，从result开始，所有元素都已排序
	vector<int>a1 = { 1,3,5,7,9 };
	vector<int>a2 = { 0,2,4,6,8 };
	merge(a1.begin(), a1.end(), a2.begin(), a2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	//inplace_merge
	//合并两个连续的排序范围：[第一，中间）和[中间，最后），将结果放入组合的排序范围[第一，最后）
	vector<int>a = { 1,3,5,7,9,2,4,6,8,10 };
	inplace_merge(a.begin(), a.begin() + 5, a.end());
	print_vector(a);

	//includes
	//如果排序范围[first1，last1）包含排序范围[ffirst2，last2）中的所有元素，则返回true
	//不要忘了序列需要有序
	vector<int>a3 = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int>a4 = { 1,2,6,8 };
	cout << includes(a3.begin(), a3.end(), a4.begin(), a4.end()) << endl;

	//set_union  并集
	//Constructs a sorted range beginning in the location 
	//pointed by result with the set union of the two sorted ranges [first1,last1) and [first2,last2).
	print_vector(a1); print_vector(a2);
	a2.push_back(9);
	set_union(a1.begin(), a1.end(), a2.begin(), a2.end(), ostream_iterator<int>(cout, " ")); cout << endl;
	//set_intersection 交集
	set_intersection(a1.begin(), a1.end(), a2.begin(), a2.end(), ostream_iterator<int>(cout, " ")); cout << endl;
	//set_difference -- 差集 序列1中的序列2中没有的元素 （单边差集）
	set_difference(a1.begin(), a1.end(), a2.begin(), a2.end(), ostream_iterator<int>(cout, " ")); cout << endl;
	//set_symmetric_difference -- 双边差集 -- 也就是（总序列 - 交集）
	set_symmetric_difference(a1.begin(), a1.end(), a2.begin(), a2.end(), ostream_iterator<int>(cout, " ")); cout << endl;
}
int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}
