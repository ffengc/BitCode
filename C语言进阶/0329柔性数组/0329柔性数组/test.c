#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<string.h>

//柔性数组

//结构中最后一个元素允许是未知大小的数组，这就叫做柔性数组
//放在最后才是柔性数组
#if 0
struct S {
	int num;
	double d;
	int arr[];//柔性数组成员
};
//上面这个不一定跑得过，下面这个应该可以，两个之间一个肯定可以的
struct S2 {
	int num;
	double d;
	int arr[0];//也是柔性数组成员
};
struct S3 {
	int num;
	int arr[0];//也是柔性数组成员
};
int main() {
	printf("%d\n", sizeof(struct S3));//4
	return 0;
}
#endif
//柔性数组的特点
/*
* 1.结构中的柔性数组成员前面必须至少一个其它成员
* 2.sizeof()返回的这种结构大小不包括柔性数组的内存
* 3.包含柔性数组成员的结构用malloc函数进行内存的动态分配，并且分配的内存应该大于结构体的大小，以适应柔性数组的预期大小
*/



#if 0
struct S3 {
	int num;
	int arr[0];//也是柔性数组成员
};
int main() {
	struct S3* ps = (struct S3*)malloc(sizeof(struct S3) + 40);
	//最好就是判断一下开辟是否成功
	//想存放10个整形，就写40
	ps->num = 100;
	for (int i = 0; i < 10; i++) {
		ps->arr[i] = i;
	}
	//打印
	for (int i = 0; i < 10; i++) {
		printf("%d ", ps->arr[i]);
	}
	printf("\n");
	//扩容
	struct S3* ptr = (struct S3*)realloc(ps, sizeof(struct S3) + 80);
	if (ptr == NULL) {
		perror("realloc");
		exit(-1);
	}
	ps = ptr;
	for (int i = 0; i < 20; i++) {
		ps->arr[i] = i;
	}
	for (int i = 0; i < 20; i++) {
		printf("%d ", ps->arr[i]);
	}
	printf("\n");
	//释放
	free(ps);
	ps = NULL;
	return 0;
}
#endif


struct S4 {
	int num;
	int* arr;
};
int main() {
	struct S4* ps = (struct S4*)malloc(sizeof(struct S4));
	if (ps == NULL) {
		perror("malloc struct");
		exit(1);
	}
	ps->arr = (int*)malloc(40);
	if (ps->arr == NULL) {
		perror("malloc array");
		free(ps);
		ps = NULL;
		exit(1);
	}
	//释放
	free(ps->arr);
	ps->arr = NULL;
	free(ps);
	ps = NULL;
	return 0;
}
//感觉这个方式，和柔性数组是没有区别
//但是区别就是，柔性数组中num和arr是靠在一起的，连续存放
//而后面指针实现的方式，num和arr不一定靠在一起的
//但是我们两种方式的可以实现相同的效果

//但是

//柔性数组的优势
/*
* 1.方便内存的释放
* 2.有利于访问速度-有利于减少内存碎片
*/