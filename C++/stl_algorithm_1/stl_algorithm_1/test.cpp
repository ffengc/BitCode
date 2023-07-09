
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<algorithm>
#include<iostream>
using namespace std;
#include<vector>
#include<array>
#elif
#endif


//all_of
//any_of
//none_of
void test1() {
	//all_of 第三个参数是仿函数 -- 返回值是布尔值
	//判断迭代器区间里面的数字是否全部符合条件（条件就是第三个参数的仿函数）
	std::array<int, 8> foo = { 3,5,7,11,13,17,19,23 };
	if (std::all_of(foo.begin(), foo.end(), [](int i) {return i % 2; }))
		std::cout << "All the elements are odd numbers.\n";
	vector<int>foo2 = { 1,2,3,4,5,-1 };
	cout << all_of(foo2.begin(), foo2.end(), [](int i) {return i >= 0; }) << endl;//0
	cout << any_of(foo2.begin(), foo2.end(), [](int i) {return i < 0; }) << endl;//看看数组中是否存在小于0的数
	cout << none_of(foo2.begin(), foo2.end(), [](int i) {return i > 100; }) << endl;//看看是不是没有大于100的数
}

//for_each
void func(const int& a)
{
	cout << a << " ";
}
void func2(int& a)
{
	a *= 2;
}
void test2()
{
	//for_each
	//将函数fn应用于范围[first，last]中的每个元素。
	vector<int>arr = { 1,2,3,4,5 };
	for_each(arr.begin(), arr.end(), func); cout << endl;
	for_each(arr.begin(), arr.end(), func2);
	for_each(arr.begin(), arr.end(), func); cout << endl;
}
void test3()
{
	//find系列
	vector<int>arr = { 1,2,3,4,5,1,2,3,9,5,6,7,8,10 };
	cout << *find(arr.begin(), arr.end(), 3) << endl;
	//find_if 找到第一个符合条件的元素 -- 同样也是传仿函数
	cout << *find_if(arr.begin(), arr.end(), [](int i) {return i == 10; }) << endl;//这里这样打印要注意，如果返回.end()
																				   //解引用会报错
	cout << *find_if_not(arr.begin(), arr.end(), [](int i) {return i == 1; }) << endl;//返回第一个 不 等于1的元素的迭代器
}
class mycomp
{
public:
	bool operator()(const int& i, const int& j)
	{
		return (i % j == 0);
	}
};
//find_end 和 find_first_of 和 adjacent_find
void test4()
{
#if 0
	vector<int> myvector{ 11, 22, 33, 100, 99, 101, 11, 22, 33 };
	int myarr[] = { 11, 22, 33 };
	vector<int>::iterator it = find_end(myvector.begin(), myvector.end(), myarr, myarr + 3);
	if (it != myvector.end())
	{
		cout << "Find：" << it - myvector.begin() << ",*it = " << *it << endl;
	}
	int myarr2[] = { 100, 99, 101 };
	it = find_end(myvector.begin(), myvector.end(), myarr2, myarr2 + 3, mycomp());
	if (it != myvector.end())
	{
		cout << "Find：" << it - myvector.begin() << ",*it = " << *it;
	}
	cout << endl;


	//find_first_of
	//返回范围[first1，last1）中与[first2，last2）中的任何元素匹配的第一个元素的迭代器。如果找不到这样的元素，函数将返回last1。
	vector<int>arr = { 100,2,3,4,5,6,7,8,9,102 };
	vector<int>foo = { 100,101,102,103 };
	if (find_first_of(arr.begin(), arr.end(), foo.begin(), foo.end()) != arr.end())
	{
		cout << *find_first_of(arr.begin(), arr.end(), foo.begin(), foo.end()) << endl;
	}
	else cout << "找不到" << endl;
#endif
	//adjacent_find
	/*
	在范围[first，last）中搜索匹配的两个连续元素的第一次出现，
	并向这两个元素中的第一个元素返回迭代器，
	如果没有找到这样的元素对，则返回last。
	*/
	array<int, 11>arr = { 1,3,3,5,7,9,2,4,6,8,10 };
	auto it = adjacent_find(arr.begin(), arr.end());
	if (it == arr.end())cout << "找不到" << endl;
	else cout << *it << endl;
}

//count系列
void test5()
{
	//count
	//返回范围[first，last]中比较等于val的元素数。
	vector<int>arr = { 1,2,3,4,5,6,7,8,9,10 };
	cout << count(arr.begin(), arr.end(), 10) << endl;
	//count_if 传一个仿函数，符合仿函数条件的计数器++ 这个也很容易理解
	cout << count_if(arr.begin(), arr.end(), [](int i) {return i > 5; }) << endl;//统计大于5的个数
}
bool newpredicate(int m, int n)
{
	return(m == n);
}
void test6()
{
	//mismatch
	/*
	如果函数发现一对不匹配的元素，则它将返回第一对这样的元素，每个集合中都有一个。
	如果集合中的所有元素都不匹配，则该函数返回pair(first1，first2)
	如果该对中的整个元素匹配，则该函数将对last1和具有相同位置的元素返回到第二个集合中的last1。
	*/
	std::vector<int> newvector;
	for (int m = 1; m < 6; m++)
		newvector.push_back(m * 10);
	int newints[] = { 10,20,80,320,1024 };
	std::pair<std::vector<int>::iterator, int*> newpair;
	newpair = std::mismatch(newvector.begin(), newvector.end(), newints);
	std::cout << "Out of the given elements the first mismatching pair is:" << *newpair.first;
	std::cout << " and " << *newpair.second << "\n";
	++newpair.first; ++newpair.second;
	newpair = std::mismatch(newpair.first, newvector.end(), newpair.second, newpredicate);
	std::cout << "The next pair of mismatching elements are:" << *newpair.first;
	std::cout << " and " << *newpair.second << "\n";
}
#include<set>
void test7()
{
	//equal
	//将范围[first1，last1）中的元素与从first2开始的范围中的元素进行比较，如果两个范围中的所有元素都匹配，则返回true。
	vector<int>arr1 = { 1,2,3,4,5,6 };
	vector<int>arr2 = { 1,2,2,4,5,6 };
	cout << equal(arr1.begin(), arr1.end(), arr2.begin() ) << endl;
	/*
	* STL 中的 equal 函数用于比较两个序列，如果两个序列的长度相同，并且对应元素都相等，equal() 算法会返回 true。
	*/
	set<int>s1 = { 1,2,3,2,1 };
	set<int>s2 = { 2,1,2,3 };
	cout << (s1 == s2) << endl;
}
void test8()
{
	//is_permutation 判断一个序列是否是另一个序列的排列
	vector<int>a1 = { 1,2,3,4,5 };
	vector<int>a2 = { 5,4,3,1,2 };
	cout << is_permutation(a1.begin(), a1.end(), a2.begin(), a2.end()) << endl;
}
void test9()
{
#if 0
	//search系列
	/* search
	在范围[first1，last1）中搜索[first2，last2）定义的序列的第一次出现，并向其第一个元素返回迭代器，如果没有出现，则返回last1。
	*/
	//其实就是找子序列
	vector<int>a1 = { 1,2,3,4,5,6,7 };
	vector<int>a2 = { 2,3,4 };
	auto it = search(a1.begin(), a1.end(), a2.begin(), a2.end());
	if (it == a1.end())cout << "找不到" << endl;
	else cout << *it << endl;
#endif
	vector<int>a1 = { 1,2,2,2,3,4,5,6,7 };
	auto it = search_n(a1.begin(), a1.end(), 3, 2);//在a1中找连续的三个2，如果有，返回第一个2的位置，如果没有，返回a1.end()
	if (it == a1.end())cout << "找不到" << endl;
	else
	{
		cout << *it << endl;
		it++;
		cout << *it << endl;
	}
}
int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	test9();
	return 0;
}