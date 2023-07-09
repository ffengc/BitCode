
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
using namespace std;


void print(const vector<int>& v)
{
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}


//accumulate
/*
* template <class InputIterator, class T, class BinaryOperation>
   T accumulate (InputIterator first, InputIterator last, T init,
                 BinaryOperation binary_op);
	//可以传一个二元的适配器
*/
void test1()
{
	//返回从[first，last）到init范围内所有值的累积结果
	vector<int>a = { 1,2,3,4,5 };
	cout << accumulate(a.begin(), a.end(), 1, multiplies<int>()) << endl;
}
//adjacent_difference
void test2()
{
	//这个函数看文档也看不懂 -- 看下面代码打印的结果，细看一下就能懂了
	//相邻两个数进行操作
	//adjacent_difference默认是求两个相邻元素的差
	//我们也可以传二元的仿函数
	vector<int> data{ 2,3,1,5,2,8,4,2 };
	cout << "原始数组:" << endl;;
	copy(data.begin(), data.end(), ostream_iterator<int>(cout, " ")); cout << endl;
	cout << "相减：" << endl;;
	adjacent_difference(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	cout << "相加" << endl;;
	adjacent_difference(data.begin(), data.end(), ostream_iterator<int>(cout, " "), plus<int>());//加法
	cout << endl;
	cout << "相乘" << endl;;
	adjacent_difference(data.begin(), data.end(), ostream_iterator<int>(cout, " "), multiplies<int>());//乘法
}
//inner_product 求内积
void test3()
{
	/*
	* 返回将init与从first1和first2开始的两个范围的元素组成的对的内积相加的结果。
	*/
	vector<int>a = { 1,2,3,4 };
	vector<int>b = { 2,2,2,2 };
	//vector<int>b = { 2,2,2,2,2 };//可以编的过
	//vector<int>b = { 2 };//err
	cout << inner_product(a.begin(), a.end(), b.begin(), 0) << endl;
}
//partial_sum
void test4()
{
	/*
	* 从result开始，为范围内的每个元素分配范围内相应元素的部分和[first，last]
	*/
	//其中一个应用就是求前缀和
	//partial_sum 对于序列 a,b,c,d 产生序列 a,a+b,a+b+c,a+b+c+d
	vector<int>a = { 1,2,3,4,5 };
	partial_sum(a.begin(), a.end(), ostream_iterator<int>(cout, " ")); cout << endl;
}
//iota
void test5()
{
	/*
	* 向范围（first，last）中的每个元素分配val的连续值，就像在写入每个元素后用++val递增一样
	*/
	vector<int>a(10);
	print(a);
	iota(a.begin(), a.end(), -5);
	print(a);
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