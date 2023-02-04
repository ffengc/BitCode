#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//库函数
//www.cplusplus.com
//strcpy
//memset

#if 0
int main() {
	char arr[] = "hello bit";
	memset(arr, 'X', 5);//以字节为单位设置的
	printf("%s\n", arr);
	return 0;
}
#endif


//交换函数
void swap(int x, int y);//err
void swap(int* x, int* y);//正确写法
//形式参数和实际参数



//练习：
//1.写一个函数判断素数，打印100~200的素数
//2.判断闰年
//3.实现有序数组的二分查找


//写一个函数，每调用一次这个函数，就会将num的值增加1
#define TIMES 3//定义次数
void test(int*p) {
	*p += 1;
#if 0
	*p++;//err
	(*p)++;//正确
#endif
}
int main() {
	int num = 0;
	for (int i = 0; i < TIMES; i++) {
		test(&num);
	}	
	printf("%d\n", num);
	return 0;
}