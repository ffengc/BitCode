
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include<algorithm>
#include<unordered_map>
#include<set>
#include<vector>
#include<iostream>
using namespace std;

void print_vector(vector<int>& v)
{
	for (const auto& e : v)cout << e << " ";
	cout << endl;
}
//copy系列和move系列
void test1()
{
	//copy
	vector<int>a1 = { 1,2,3,4,5 };
	copy(a1.begin(), a1.end(), ostream_iterator<int>(cout, " "));//拷贝到输出流上
	cout << endl;
	copy_n(a1.begin(), 2, ostream_iterator<int>(cout, " "));//拷贝前n个到输出流上
	//copy_n(a1.begin(), 10, ostream_iterator<int>(cout, " "));//超了会报错
	cout << endl;
	copy_if(a1.begin(), a1.end(), ostream_iterator<int>(cout, " "), [](const int& a) {return a > 2; });//拷贝大于2的到输出流上
	cout << endl;
	//copy_backward -- 反向拷贝 -- 需要双向迭代器 -- 要用的时候去查 -- 估计用不到
	//move 和 move_backward 和copy用法应该是相似的
	/*
	[first，last）中元素的值被传递给result指向的元素。调用后，[first、last）范围中的元素将处于未指定但有效的状态。
	*/
}

//swap系列
#include<array>
void test2()
{
	//swap
	//swap_ranges
	/*
	将范围[first1，last1）中的每个元素的值与其从first2开始的范围中的相应元素的值交换。
	*/
	vector<int>a1 = { 1,2,3,4,5 };
	vector<int>a2 = { 5,4,3,2,1,1 };
	swap_ranges(a1.begin(), a1.end(), a2.begin());//如果此时a2元素比a1少的时候会报错
	for (const auto& e : a1)cout << e << " ";
	cout << endl;
	for (const auto& e : a2)cout << e << " ";
	cout << endl;

	//iter_swap
	//交换a和b指向的元素。
	array<int, 3>b1 = { 1,2,3 };
	array<int, 3>b2 = { 100,2,1 };
	auto it1 = b1.begin();
	auto it2 = b2.begin();
	iter_swap(it1, it2);
	for (const auto& e : b1)cout << e << " ";
	cout << endl;
	for (const auto& e : b2)cout << e << " ";
	cout << endl;
}
void test3()
{
	//tranform
	//将操作顺序应用于一（1）个或两（2）个范围的元素，并将结果存储在从结果开始的范围中。
	vector<int>a = { 1,2,3,4 };
	transform(a.begin(), a.end() - 1, ostream_iterator<int>(cout, " "), [](int& a) {a *= a; return a; });
}

//replace系列
void test4()
{
	//replace
	//将new_value赋给范围[first，last]中与old_value相等的所有元素。
	vector<int>a = { 1,2,3,4 };
	replace(a.begin(), a.end(), 2, 3);//把2全部换成3 -- 找不到就不替换
	// 1 3 3 4
	print_vector(a);
	//replace_if 符合条件的换掉
	replace_if(a.begin(), a.end(), [](int i) {return i == 3; }, 2);//把所有的3换成2
	// 1 2 2 4
	print_vector(a);
	//replace_copy
	replace_copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "), 2, 3);//把所有的2换成3，然后复制到输出流上
	cout << endl;
	//replace_copy_if 同理
}

//fill 和 generate 系列
void test5()
{
	//fill
	//将val赋给范围[first，last]中的所有元素。
	vector<int>arr(10);
	fill(arr.begin(), arr.end(), 5);
	print_vector(arr);
	//fill_n 指定填充个数
	vector<int>a2(10);
	fill_n(a2.begin(), 10, 1);//越界会报错
	print_vector(a2);

	//generate
	//将连续调用gen返回的值分配给范围[first，last）中的元素。
	vector<int>a3(10);
	generate(a3.begin(), a3.end(), []() { //把1~10赋值给a3
		static int i = 1;
	return i++;
		});
	//1 2 3 4 5 6 7 8 9 10
	print_vector(a3);
	//generate_n
	//将连续调用gen返回的值分配给first指向的序列的前n个元素。
	vector<int>a4(10);
	generate_n(a4.begin(), 5, []() {static int i = 1; return i++; }); //第二个参数越界会报错
	//1 2 3 4 5 0 0 0 0 0
	print_vector(a4);
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