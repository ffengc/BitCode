
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include<iostream>
#include<algorithm>
#include<vector>
#include<chrono>
#include<array>
#include<random>
using namespace std;

void print_vector(const vector<int>& a)
{
	for (const auto& e : a)cout << e << " ";
	cout << endl;
}
template<class iterator>
void print_vector(iterator begin, iterator last)
{
	auto it = begin;
	while (it != last)
	{
		cout << *it << " "; it++;
	}
	cout << endl;
}

//remove系列
void test1()
{
	//remove
	vector<int>a = { 1,2,3,4,5,2,2,3,3,4 };
	//1 2 4 5 2 2 4 3 3 4
	auto last = remove(a.begin(), a.end(), 3);//注意，这里是通过覆盖来进行删除的
	print_vector(a);
	print_vector(a.begin(), last);//这样打印才是对的
	//remove_if 和前面同样道理 -- 传一个仿函数

	//remove_copy 
	//将范围[first，last]中的元素复制到从result开始的范围，但比较等于val的元素除外。
	//返回值：一个指向复制范围末尾的迭代器，它包括[first，last）中的所有元素，但比较等于val的元素除外。
	//remove_copy_if
	vector<int>a2 = { 1,2,3,4,5,2,2,3,3,4 };
	remove_copy(a2.begin(), a2.end(), ostream_iterator<int>(cout, " "), 3); cout << endl;//删除3，把序列打印出来
	remove_copy_if(a2.begin(), a2.end(), ostream_iterator<int>(cout, " "), [](int i) {return i == 3; });//删除3，把序列打印出来
	cout << endl;//注意，remove_copy和remove_copy_if原序列是不变的
}
//unique系列
void test2()
{
#if 0
	//unique系列
	//unique
	//从范围[first，last）中的每个连续等效元素组中删除除第一个元素以外的所有元素。//要连续的才能去掉 -- 所以建议排一下序
	vector<int>a = { 1,2,3,4,5,2,2,3,3,4 };
	sort(a.begin(), a.end());
	print_vector(a);
	auto it = unique(a.begin(), a.end());
	print_vector(a.begin(), it);//不能这样打印 -- 它是覆盖删除 -- 函数返回了一个迭代器 -- 应该用迭代器区间
#endif
	//unique_copy
	vector<int>a2 = { 1,2,3,4,5,2,2,3,3,4 };
	sort(a2.begin(), a2.end());
	unique_copy(a2.begin(), a2.end(), ostream_iterator<int>(cout, " "), [](int a, int b) {return a == b; });//去重后打印
}
//reverse系列
void test3()
{
	//reverse
	vector<int>a = { 1,2,3,4,5 };
	std::reverse(a.begin(), a.end());
	print_vector(a);
	//reverse_copy
	std::reverse_copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
}
//rotate
void test4()
{
#if 0
	//rotate
	vector<int>a = { 1,2,3,4,5 };
	rotate(a.begin(), a.begin() + 2, a.end());
	print_vector(a);
#endif
	//rotate_copy
	vector<int>a1 = { 1,2,3,4,5 };
	rotate_copy(a1.begin(), a1.begin() + 2, a1.end(), ostream_iterator<int>(cout, " "));
}
//shuffle系列
void test5()
{
#if 0
	//random_shuffle
	//随机重新排列范围（first，last）中的元素。
	vector<int>a = { 1,2,3,4,5 };
	srand(time(nullptr));
	random_shuffle(a.begin(), a.end());//每次运行的打乱方式是一样的 -- 所以加一个srand()比较合适
	print_vector(a);
#endif
	//shuffle
	//使用g作为均匀随机数生成器，随机重新排列范围（first，last）中的元素。
	std::array<int, 5> foo = { 1,2,3,4,5 };
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));
	std::cout << "shuffled elements:";
	for (int& x : foo) std::cout << ' ' << x;
	std::cout << '\n';
}
int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}