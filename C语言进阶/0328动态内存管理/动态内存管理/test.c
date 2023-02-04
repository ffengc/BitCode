#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<memory.h>
#include<stdlib.h>

//堆区开辟空间

//stack-局部变量
//heap-malloc-free-calloc-realloc
//static-全局变量


//堆是由二叉树结构实现


//Heap上的内存
#if 0
int main() {
	int* ptr = (int*)malloc(10 * sizeof(int));//里面写成0是标准为定义的
	int* p = ptr;
	if (p == NULL) {
		perror("malloc");
	}
	for (int i = 0; i < 10; i++) {
		*p = i;
		p++;
		//*(p+i)=i;也是可以的，而且这种写法p的位置没有改变
	}
	free(ptr);
	ptr = NULL;
	return 0;
}
#endif
//free只能释放heap上的空间

#if 0
int main() {
	int* p = NULL;
	free(p);//啥都不发生
	return 0;
}
#endif


#if 0
int main() {
	int* ptr = (int*)malloc(40);
	if (ptr == NULL) { perror("malloc"); return 1; }
	free(ptr);
	//如果不释放就会造成内存泄露的问题
	return 0;
}
//比如说服务器程序
#endif


#if 0
int main() {
	while (1) {
		malloc(10000);
	}
	return 0;
}
#endif


//calloc
//calloc申请好的内存是初始化好的，都为0
#if 0
int main() {
	int* p = (int*)malloc(40);
	int* q = (int*)calloc(10, sizeof(int));//可以打开内存，全部初始化成0了
	//当然，开辟完也是要判断开辟是否成功的
	return 0;
}
#endif


//realloc
#if 0
int main() {
	int* p = (int*)malloc(10 * sizeof(int));//里面写成0是标准为定义的
	if (p == NULL) {
		perror("malloc");
	}
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	//此时空间不够了
    //p = (int*)realloc(p, 20 * sizeof(int));
	//这样写有风险
	//如果扩容失败，就会返回空指针了
	//所以我们建立一个临时指针
	int* _ptr = (int*)realloc(p, 20 * sizeof(int));
	if (_ptr != NULL) {
		p = _ptr;
	}
	free(p);
	p = NULL;
	return 0;
}
#endif
//realloc的返回值分析
/*
* 1.如果后面的空间足够，直接追加就可以了
* 2.后面的空间不够用了--重新找一块空间--同时把前面拷贝过来--同时会帮我们把前面的free掉
*/


#include<limits.h>
//动态内存常见的一些错误
//1.对空指针的解引用操作
#if 0
int main() {
	int* p = (int*)malloc(INT_MAX);
	//所以我们要判空
	if (p == NULL) {
		exit(-1);
	}
	for (int i = 0; i < 5; i++) {
		*(p + i) = i;
	}
	return 0;
}
#endif
//2.对堆上的空间越界访问
#if 0
int main() {
	int* arr = (int*)malloc(10 * sizeof(int));
	if (arr == NULL)exit(-1);
	for (int i = 0; i <= 10; i++) {//err
		*(arr + i) = i;
	}
	return 0;
}
#endif


//3.对非堆上的空间进行free操作
#if 0
int main() {
	int a = 10;
	int* pa = &a;
	//...
	free(pa);///err
	return 0;
}
#endif


//4.对堆上的空间不完全释放，造成内存泄露
#if 0
int main() {
	int* p = (int*)malloc(10 * sizeof(int));
	if (p == NULL)exit(-1);
	for (int i = 0; i < 10; i++) {
		*p = i;
		p++;
	}
	free(p);//前面的空间已经找不到了，err
	return 0;
}
#endif
//一定要记住内存的起始位置，不能丢失

//5.对空一块空间多次释放
#if 0
int main() {
	int* p = malloc(1000);
	if (p == NULL)return 1;
	free(p);
	//...


	free(p);
	return 0;
}
#endif


//6.忘记释放
#if 0
void test() {
	int* p = malloc(100);
	//使用
	//如果出了这个函数还没free
	//这样的话内存就泄露了
	//因为p只是一个局部变量
}
int main() {
	test();
	return 0;
}
#endif


//#include<HBD.h>
#if 0
int main() {
	char str[] = "Happy Birthday To you!";
	char str1[] = "Happy everyday!";
	char str2[] = "Achieve your dream!";
	printf("%s\n%s\n%s\n", str, str1, str2);
	system("pause");
	return 0;
}
#endif

//笔试题1
#if 0
void GetMemory(char* p) {
	p = (char*)malloc(100);
}
//这里是临时的，所以结果是err
void Test(void) {
	char* str = NULL;
	GetMemory(str);
	strcpy(str, "hello world");
	printf(str);
}
int main() {
	Test();
	return 0;
}
#endif


#if 0
char* GetMemory(void) {
	char p[] = "hello world";
	return p;
}
void Test(void) {
	char* str = NULL;
	str = GetMemory();
	printf(str);
}
int main() {
	Test();
	return 0;
}
#endif
//返回栈上空间的地址是不行，出函数的时候就释放了

#if 0
#include<string.h>
void GetMemory(char** p, int num) {
	*p = (char*)malloc(num);
}
void Test(void) {
	char* str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "hello");
	printf(str);
	free(str);
	str = NULL;
}
int main() {
	Test();
	return 0;
}
#endif



void Test(void) {
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str);
	//野指针的问题
	//所以要值得置空
	//str=NULL;
	if (str != NULL) {
		strcpy(str, "world");//这里就是非法的操作了
		printf(str);
	}
}
int main() {
	Test();
	return 0;
}