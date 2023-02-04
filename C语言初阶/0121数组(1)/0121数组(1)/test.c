#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//数组
/*
* 1.一维数组的创建和初始化
* 2.一维数组的使用
* 3.一维数组在内存中的存储
* 4.二维数组的创建和初始化
* 5.二维数组的使用
* 6.二维数组在内存中的存储
* 7.数组越界
* 8.数组作为函数参数
* 9.三子棋和扫雷
*/


#if 0
int main() {
	int n = 10;
	int arr[10] = { 0 };
	//int arr[n] = { 0 };
	//C99支持变长数组，但是vs不支持

	//cpp和c是不一样的，cpp里面的const修饰就是常量，c里面是常变量，是不一样的
	return 0;
}
#endif
//数组的越界



//数组作为函数参数 


//数组名的意义
int main() {
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	//差4
	printf("%p\n",arr);
	printf("%p\n", arr + 1);
	//差4
	printf("%p\n", &arr[0]);
	printf("%p\n", &arr[0] + 1);
	//差40
	printf("%p\n", &arr);
	printf("%p\n", &arr + 1);//因为&arr是数组地址，不是首元素地址

	return 0;
}