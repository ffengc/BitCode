#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//计算复杂度
#if 0
long long Fac(size_t N) {
	if (0 == N)
		return 1;
	return Fac(N - 1) * N;
}
//O(N)


//计算复杂度
long long fib(size_t N) {
	if (N < 3)
		return 1;
	return fib(N - 1) + fib(N - 2);
}
#endif
//用等比数列公式
//2^0+2^1+2^2+.....2^(n-1)-1
//所以量级是2^n量级

//说明斐波那契递归算法--在实际上没有实践价值（只有理论价值）


//改循环之后--O(n)就可以了


//但是阶乘那个
//写10000的时候也崩了
//因为栈溢出了

//空间复杂度
void bubble_sort(int arr, int n);
//O(1)
//没有额外占用空间


#include<stdlib.h>
//fib前n项
#if 0
long long* fib(size_t n) {
	if (n == 0) {
		return NULL;
	}
	long long* _fibArray = (long long*)malloc((n + 1) * sizeof(long long));
	_fibArray[0] = 0;
	_fibArray[1] = 1;
	for (int i = 2; i <= n; i++) {
		_fibArray[i] = _fibArray[i - 1] + _fibArray[i - 2];
	}
	return _fibArray;
}
//O(n)
#endif

#if 0
long long fac(size_t n) {
	if (n == 0)
		return 1;
	return fac(n - 1) * n;
}
#endif
//空间复杂度：O(n)
//大多数算法的空间复杂度都是O(1)和O(n)


//
#if 0
long long fib(size_t n) {
	if (n < 3)
		return 1;
	return fib(n - 1) + fib(n - 2);
}
#endif

//时间是累计的，空间是不累计的
//空间复杂度：O(n)


//空间可以重复利用的实例
#if 0
void f1() {
	int a = 10;
	printf("%p\n", &a);
}
void f2() {
	int a = 10;
	printf("%p\n", &a);
}
int main() {
	f1();
	f2();
	return 0;
}
#endif
//发现结果是一样的