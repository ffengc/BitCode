#define _CRT_SECURE_NO_WARNINGS 1




#include<stdio.h>

//求1!+2!+3!+4!+....




//死循环
#if 0
int main() {
	int i = 0;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//for里面不要习惯性写int i 否则就没死循环了
	for (i = 0; i <= 12; i++) {
		arr[i] = 0;
		printf("hehe\n");
	}
	return 0;
}
#endif




//const的修饰
int main() {
	//int num = 10;
	//num = 20;
	//int* p = &num;
	//*p = 100;

	const int num = 10;
	//nums=20;
	int n = 100;
	int* const p = &num; 
	*p=200;
	//p = &n;

	//const可以修饰指针
	//const放在*的左边(const int*p)
	//const修饰的是*p，表示p指向的对象不能通过p来改变，但是p变量中的地址是可以改变的

	return 0;
}


//strcpy的实现
//写成一下这种形式是最好的
#include<assert.h>
//返回一个char*就可以实现链式访问了
char* my_strcpy(char* dest, const char* src) {
	assert(dest && src);
	char* ret = dest;
	while (*dest++ = *src++) { ; }
	return ret;
}
int main() {
	char arr1[] = "hello bit";
	char arr2[20] = "xxxxxxxxxxxxxxxxx";
	char* p = NULL;
	printf("%s\n", my_strcpy(arr2, arr1));

	return 0;
}