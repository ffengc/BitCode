#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>


//同一条代码在不同编译器下得到的答案不同，说明这是一条错误代码

//32位虚拟地址空间
//CPU-32位地址-地址线传输->内存
//64位虚拟地址空间
//CPU-64位地址-数据线传输->内存


//初阶指针
#if 0
int main() {
	int a = 10;
	int* pa = &a;
	printf("%p\n", pa);
	return 0;
}
#endif


//指针和指针类型
//为什么需要指针类型



#if 0
int main() {
	int a = 0x11223344;
	//int* pa = &a;
	//*pa = 0;
	char* pa2 = &a;
	*pa2 = 0;
	return 0;
}
#endif
//通过看内存我们可以发现
//指针类型决定解引用的时候的访问权限





//指针类型决定指针+1跳过几个字节
#if 0
int main() {
	int a = 10;
	int* p1 = &a;
	char* p2 = &a;
	printf("%p\n", p1);
	printf("%p\n", p2);
	printf("%p\n", p1 + 1);
	printf("%p\n", p2 + 1);
	return 0;
}
#endif




//野指针
#if 0
int* test() {
	int a = 10;
	printf("%d\n", a);
	return &a;
}
int main() {
	int* p = test();
	*p = 100;
	printf("%d\n", *p);
	return 0;
}
#endif
//err
//a的内存在出test()的时候已经释放
//p就是给野指针
//p指向的地方已经没有操作权限了

//记得初始化！
//该置空就置空！
//防止越界！
//使用指针前检查指针的有效性！
//避免返回局部变量的地址！



//指针的运算
//指针-指针的绝对值是指针和指针之间的元素个数
///前提：两个指针必须指向同一块空间


//my_strlen()的第三种方法：指针-指针
#if 0
int my_strlen(char* str) {
	char* cur = str;
	while (*cur)
		cur++;
	return cur - str;
}
int main() {
	char arr[] = "abcdef";
	int ret = my_strlen(arr);
	printf("%d\n", ret);
	return 0;
}
#endif

//数组名是首元素地址
//但是有两个例外
//sizeof(数组名)，数组名表示整个数组
//&数组名，表示去除整个数组的地址
#if 0
int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = arr;
	int* p2 = &arr;//这样的p2依旧是int*类型,+1只会跳过4个字节，只会跳过一个
	int ret = *(&arr + 1);
	printf("%p\n", p + 1);
	printf("%p\n",p2 + 1);
	printf("%p\n", &arr + 1);
	printf("%d\n", ret);
	return 0;
}
//数组地址+1跳过整个数组
#endif


#if 0
//二级指针
int main() {
	int a = 10;
	int* pa = &a;
	int** ppa = &pa;
	printf("%p\n", pa);
	printf("%p\n", ppa);
	return 0;
}
#endif



int main() {
	int data1[] = { 1,2,3,4,5 };
	int data2[] = { 2,3,4,5,6 };
	int data3[] = { 3,4,5,6,7 };

	int* arr[3] = { data1,data2,data3 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
	return 0;
}