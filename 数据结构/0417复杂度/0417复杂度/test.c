#define _CRT_SECURE_NO_WARNINGS 1


//数据结构初阶：C语言实现--20节课

//C++：50节课
//C++语法
//高阶数据结构
//STL

//结课：明年的3月份


//数据结构和数据库的区别：
/*
* 数据结构--在内存中存储管理数据
* 数据库--再磁盘中存储管理数据
*/


//时间复杂度
//一个算法运行的时间和硬件配置有关系，所以同样一个算法是没有办法算出准确时间的


//请计算一下Func1中++count语句总共执行了多少次
#if 0
void Func1(int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			++count;
		}
	}
	for (int k = 0; k < 2 * n; ++k) {
		++count;
	}
	int M = 10;
	while (M--) {
		++count;
	}
}
#endif

//F(N)=n^2+2*n+10
//函数式计算的算法运行准确次数
//大O的渐进表示
/*
* 1.用常数1取代时间中的所有加法常数
* 2.再修改后的运行次数函数中，只保留最高阶项
* 3.如果最高项存在且系数不为1，则去除这个常数
* //得到的结果就是大O阶
*/



//计算时间复杂度
#if 0
void Func2(int n) {
	int count = 0;
	for (int k = 0; k < 2 * n; k++) {
		++count;
	}
	int M = 10;
	while (M--) {
		++count;
	}
}
#endif
//O(N)



//
#if 0
void func3(int n, int m) {
	int count = 0;
	for (int k = 0; k < m; k++) {
		count++;
	}
	for (int k = 0; k < n; k++) {
		count++;
	}
}
//O(M+N)


//
void func4(int n) {
	int count = 0;
	for (int i = 0; i < 100; i++) {
		count++;
	}
}
//O(1)


//
const char* strchr(const char* str, int character);
//O(n)
//时间复杂度一般找最坏的情况



//时间复杂度不要数循环
//一定要看算法思想
//
void _bubble_sort(int* arr, int sz);
//O(n^2)
//F(n)=n+n-1+n-2+......+2+1


//二分查找
int _BinarySearch(int* a, int n, int x)
{
	assert(a);
	int begin = 0;
	int end = n - 1;
	// [begin, end]：begin和end是左闭右闭区间，因此有=号
	while (begin <= end)
	{
		int mid = begin + ((end - begin) >> 1);
		if (a[mid] < x)
			begin = mid + 1;
		else if (a[mid] > x)
			end = mid - 1;
		else
			return mid;
	}
	return -1;
}
#endif
//最好O(1)
//最坏--找不到（最后一个找到）
//假设折半查找了x次
//2^x=n
//n=log(2)n


//因为文本中写对数不好写，而时间复杂度中，log(2)N经常出现
//所以直接简写成logN
//有些书籍或博客等等会简写成lgN，其实是不太对的，那么要知道他写的是log(2)N

//O(n)和O(logN)
//其实是不同级别的算法
//其实二分法是一个很牛逼的算法



//力扣
//面试题 17.04. 消失的数字
//思路2
int missingNumber(int* nums, int numsSize) {
	int x = 0;
	for (int i = 0; i < numsSize; i++) {
		x ^= nums[i];
	}
	for (int j = 0; j < numsSize + 1; j++) {
		x ^= j;
	}
	return x;
}
//思路1（哈希思想）构造一个映射
//malloc一个n+1个数组
//遍历这些数字，这个数是多少，就写到对应位置

//思路2：异或

//思路3：排序+二分查找

//思路4：公式计算--求和相减就行了