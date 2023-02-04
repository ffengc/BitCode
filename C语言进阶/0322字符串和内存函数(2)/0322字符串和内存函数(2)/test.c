#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
//字符串和内存函数(2)



//strtok 字符串切割
//char* strtok(char* str, char* sep);
//sep参数是个字符串，定义了用作分隔符的字符集合
//第一个参数指定一个字符串，它包含了0个或多个由sep字符串中一个或多个分隔符分割的标记

/*
* strtok函数找到str中的下一个标记，并将其用\0结尾，返回一个指向这个标记的指针
* (注：strtok函数会改变被操作的字符串，所以在使用的时候一般都是临时拷贝的内容)
* strtok函数的第一个参数不为NULL，函数将找到str中的第一个标记，strtok函数将保存它在字符串中的位置
* strtok函数的第一个参数为NULL，函数将在同一个字符串中被保存的位置开始，查找下一个标记
* 如果字符串中不存在更多的标记，则返回NULL
*/
#if 0
int main() {
	char arr[] = "xiaoxiaoprogrammer@yeah.net";
	char buf[30] = { 0 };
	strcpy(buf, arr);
	const char* sep = "@.";
	//"@."--sep
#if 0
	printf("%s\n",strtok(buf, sep));//只找到第一个标记
	printf("%s\n",strtok(NULL, sep));//从保存好的位置继续往后找
	printf("%s\n", strtok(NULL, sep));//从保存好的位置继续往后找
#endif
	//我们发现传buf只需要传一次，所以巧妙利用for循环，for循环初始化只执行一次
	char* str = NULL;
	for (str = strtok(buf, sep); str != NULL; str = strtok(NULL, sep)) {//处理完要赋值
		printf("%s\n", str);
	}
	return 0;
}
//至于strtok为什么记得，我们先不用关心，但是肯定是有一个静态指针来记录的
#endif


//strerror和perror
//返回错误码的错误信息
//如果运行的时候出现错误
//会自动生成一个全局变量：errno（错误码）
#include<errno.h>
#include<limits.h>
#include<stdlib.h>
#if 0
int main() {
#if 0
	printf("%s\n", strerror(0));
	printf("%s\n", strerror(1));
	printf("%s\n", strerror(2));
	printf("%s\n", strerror(3));
#endif
	//每个错误码对应都有错误信息
	//malloc向堆区申请内存空间
	int* p = (int*)malloc(INT_MAX);
	//如果申请失败，就会返回一个空指针
	if (p == NULL) {
		printf("%s\n", strerror(errno));
		perror("malloc");//会在后面加一个冒号，再加一个空格，再加错误信息
		                 //如果传空字符串的话就不会加冒号和空格
		return 1;
	}
	return 0;
}
#endif




//字符分类函数
/*
iscntrl 任何控制字符
isspace 空白字符：空格‘ ’，换页‘\f’，换行'\n'，回车‘\r’，制表符'\t'或者垂直制表符'\v'
isdigit 十进制数字 0~9
isxdigit 十六进制数字，包括所有十进制数字，小写字母a~f，大写字母A~F
islower 小写字母a~z
isupper 大写字母A~Z
isalpha 字母a~z或A~Z
isalnum 字母或者数字，a~z,A~Z,0~9
ispunct 标点符号，任何不属于数字或者字母的图形字符（可打印）
isgraph 任何图形字符
isprint 任何可打印字符，包括图形字符和空白字符
*/
#include<ctype.h>
#if 0
int main() {
	int ret = isdigit('q');
	//...
	printf("%d\n", ret);
	char ch = 'a';
	putchar(toupper(ch));
	return 0;
}
#endif
//字符转换
//tolower
//toupper


//内存操作函数
//memcpy
//memmove
//memcmp
//memset


//memcpy
//void* memcpy(void* dest, const void* src, size_t count);
#include<assert.h>
#if 0
void* my_memcpy(void* dest, const void* src, size_t count) {
	assert(dest && src);
	void* ret = dest;
	while (count--) {
		*(char*)dest = *(char*)src;
		dest = (char*)dest + 1;//一定要有类型才能加
		src = (char*)src + 1;
	}
	return ret;
}
int main() {
	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr2[5] = { 0 };
	//memcpy(arr2, arr1, 20);
	my_memcpy(arr2, arr1, 20);
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr2[i]);
	}
	return 0;
}
#endif


//这仅仅只是一种场景而已
//如果我要自己拷贝到自己后面的地址上呢，比如：
#if 0
void* my_memcpy(void* dest, const void* src, size_t count) {
	assert(dest && src);
	void* ret = dest;
	while (count--) {
		*(char*)dest = *(char*)src;
		dest = (char*)dest + 1;//一定要有类型才能加
		src = (char*)src + 1;
	}
	return ret;
}
void* my_memmove(void* dest, const void* src, size_t count) {
	//这里是从后往前拷贝和从前往后拷贝的问题
	//1 2 3 4 5 6 7 8 9 10
	//如果dest<src 从前向后拷贝
	//如果dest>src 从后向前拷贝
	//如果没重叠：都可以
	assert(dest && src);
	void* ret = dest;
	if (dest < src) {
		//前->后
		while (count--) {
			*(char*)dest = *(char*)src;
			dest = (char*)dest + 1;
			src = (char*)src + 1;
		}
	}
	else {
		//后->前
		while (count--) {
			*((char*)dest + count) = *((char*)src + count);
		}
	}
	return ret;
}
int main() {
	int arr1[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//my_memcpy(arr1 + 2, arr1, 20);//发现不符合我们的预期，因为我们实现的memcpy是不打算用来处理重叠内存的
	//处理这个场景可以用memmove函数
	//memmove(arr1 + 2, arr1, 20);//可以实现重叠内存拷贝
	my_memmove(arr1 + 2, arr1, 20);
	return 0;
}
#endif 

//memcmp
#if 0
int main() {
	int arr1[] = { 1,2,3,4,5 };
	int arr2[] = { 1,2,3,4,0x1122334405 };
	int ret1 = memcmp(arr1, arr2, 16);
	int ret2 = memcmp(arr1, arr2, 17);//17也是一样的
	int ret3 = memcmp(arr1, arr2, 18);
	printf("%d %d %d", ret1,ret2,ret3);

	return 0;
}
#endif




//memset-内存设置
#if 0
int main() {
	int arr[] = { 1,2,3,4,5 };
	memset(arr, 0, 20);
	memset(arr, 6, 20);//这里并不是把数据改成6，而是把每个字节都改成6
	return 0;
}
#endif



//模拟实现atoi
//将字符串转化成整型
#if 1
#include<assert.h>
enum Status {
	VALID,INVALID
}status=INVALID;//先一开始设置成非法
int my_atoi(const char* str) {
	//空指针
	assert(str);
	int flag = 1;//表示是正数
	//空字符串
	if (*str == '\0') {
		//发现这样返回无论怎样都不合适，所以我们设置一个变量
		//判断当前返回值是否有效，合法还是非法
		//使用枚举
		return 0;
	}
	//处理空白字符
	while (isspace(*str)) {
		//如果是空白字符，就跳过去了
		str++;
	}
	//正负号
	if (*str == '-') {
		flag = -flag;//有一个'-'变一次号
		str++;
	}
	//遍历串
	long long n = 0;
	while (*str) {
		if (isdigit(*str)) {
			n = n * 10 + (flag) * (*str - '0');
			if (n<INT_MIN || n>INT_MAX) {//说明越界了
				//但是，如果存到n里面去，是肯定不会越界的，因为会发生截断
				//所以，设置成long long是最好的
				n = 0;
				break;
			}
		}
		else {
			n = 0;
			break;
		}
		str++;
	}
	if (*str == '\0') {
		status = VALID;
	}
	return (int)n;
}
//1.空指针问题
//2.空字符串问题
//3.非数字字符
//4.空白字符等，逗号字符
//5.正负号
int main() {
	while (1) {//重复测试
		char arr[100] = { 0 };
		gets(arr);
		int ret = my_atoi(arr);
		if (status == VALID)
			printf("%d\n", ret);
		else
			printf("%d err\n", ret);
	}
	return 0;
}
#endif



