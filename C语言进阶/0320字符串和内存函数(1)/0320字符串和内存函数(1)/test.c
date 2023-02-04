#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<assert.h>

//strlen
#if 0
int main() {
	char arr[] = "abcdef";
	//char arr[] = { 'a','b','c','d','e','f' };
	int len = strlen(arr);
	printf("%d\n", len);
	return 0;
}
#endif
//注意strlen的返回值是size_t
//所以不注意的时候容易写出bug
#if 0
int main() {
	if (strlen("abc") - strlen("qwertyu") > 0) {
		printf(">\n");
	}
	else {
		printf("<\n");
	}

	return 0;
}
//用到时候注意一下就可以了
#endif

//strlen的实现
//计数器解法 当然还有递归法，指针-指针的方法
#if 0
size_t my_strlen(const char* str) {
	assert(str);
	int count = 0;
	while (*str != '\0') {
		count++;
		str++;
	}
	return count;
}
int main() {
	char arr[] = "abcdef";
	int len = my_strlen(arr);
	printf("%d\n", len);
	return 0;
}
#endif 


//strcpy字符串拷贝
#if 0
int main() {
	char arr1[20] = { 0 };
	char arr2[] = "abcdef";
	strcpy(arr1, arr2);
	printf("%s\n", arr1);
	return 0;
}
#endif
//注意，原字符串必须以'\0'结尾
//拷贝的时候会把原字符串的\0也拷贝过去
//目标空间一定要足够大
//目标空间必须可变
#if 0
char* my_strcpy(char* dest, const char* src) {
	assert(dest && src);
	char* ret = dest;
	while (*dest++ = *src++) {
		;
	}
	return ret;
}
int main() {
	char arr1[20] ="xxxxxxxxxxxxxxxxx";
	char arr2[] = "abcdef";
	strcpy(arr1, arr2);
	printf("%s\n", arr1);
	return 0;
}
#endif



//strcat 字符串追加
#if 0
int main() {
	char arr1[20] = "hello ";
	char arr2[] = "bit";
	strcat(arr1, arr2);
	printf("%s\n", arr1);
	return 0;
}
#endif
//原字符串要有\0,目标空间也要\0，否则找不到开始追加的标志
//否则它也会继续往后越界访问，知道找到\0为止
#if 0
char* my_strcat(char* dest, const char* src) {
	assert(dest && src);
	//1.找原字符串中的\0
	char* start = dest;
	while (*start) {
		start++;
	}
	//开始拷贝
	while (*start++ = *src++) {
		;
	}
	return dest;
}
int main() {
	char arr1[20] = "hello ";
	char arr2[] = "bit";
	//my_strcat(arr1, arr2);
	printf("%s\n", my_strcat(arr1, arr2));
	return 0;
}
#endif
//问题：能自己给自己追加吗，这要看具体实现，我们写的这个版本是不行的

//strcmp
//不是比较长度，而是比较相对应位置的值的大小
#if 0
int my_strcmp(const char* str1, const char* str2) {
	assert(str1 && str2);
	while (*str1 == *str2) {
		if (*str1 == '\0')return 0;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}
int main() {
	char arr1[] = "abcdef";
	char arr2[] = "abq";
	int ret = strcmp(arr1, arr2);
	//int ret = my_strcmp(arr1, arr2);
	printf("%d\n", ret);
	return 0;
}
#endif

//上面都是长度不受限制的字符串操作函数
//
//strncpy
//strncat
//strncmp
//长度受限制的字符串函数
#if 0
int main() {
	char arr1[] = "abcdef";
	char arr2[] = "qwertyuiop";
	strncpy(arr1, arr2, 3);
	printf("%s\n", arr1);
	return 0;
}
#endif

//strncat
#if 0
int main() {
	//char arr1[20] = "abcdef";
	char arr1[20] = "abcdef\0xxxxxxxx";
	char arr2[] = "qwertyuiop";
	strncat(arr1, arr2, 5);
	printf("%s\n", arr1);
	return 0;
}
#endif
//追加结束之后，还会主动放一个\0进去


//strncmp
#if 0
int main() {
	char arr1[] = "abcdef";
	char arr2[] = "abcdefqwert";
	int ret = strncmp(arr1, arr2, 4);
	printf("%d\n", ret);
	return 0;
}
#endif


//这样比较比较的都是两个字符串的地址，不是在比较字符串
//要比较就用strcmp或strncmp就可以了
#if 0
int main() {
	char arr1[] = "abcdef";
	char arr2[] = "abc";
	if (arr1 > arr2) {//这里比的是地址
		printf("arr1>arr2\n");
	}
	if ("abcdef" > "abc") {
		;//这里比的也是地址
	}

	return 0;
}
#endif


//strstr
//判断一个字符串是不是另一个字符串的字串
//找到了-返回字串在里面出现的地址
//找不到-返回空
#if 0
int main() {
	char arr1[] = "abcdefg";
	char arr2[] = "cdef";
	char* ret = strstr(arr1, arr2);
	if (ret == NULL) { printf("找不到子串\n"); }
	else {
		printf("%s\n", ret);
	}
	return 0;
}
#endif


//strstr实现
//双指针实现
#if 0
char* my_strstr(const char* str1, const char* str2) {
	assert(str1 && str2);
	const char* s1 = str1;
	const char* s2 = str2;
	const char* cur = str1;
	while (*cur) {
		s1 = cur;
		s2 = str2;//这次匹配不成功，回到原位重新开始匹配
		while (*s1 && *s2 && *s1 == *s2) {
			s1++;
			s2++;
		}
		if (*s2 == '\0') {//这次匹配成功了
			return (char*)cur;
		}
		cur++;//匹配失败，说明从cur开始匹配不行
	}
	return NULL;
}
int main() {
	char arr1[] = "abcdefg";
	char arr2[] = "cdef";
	char* ret = my_strstr(arr1, arr2);
	if (ret == NULL) { printf("找不到子串\n"); }
	else {
		printf("%s\n", ret);
	}
	return 0;
}
#endif
//查找字串
//KMP算法 - B站比特大博哥