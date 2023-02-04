#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>



#if 0
#include"add.h"
//函数的声明
//静态库引用和使用

//导入静态库
#pragma comment(lib,"add.lib")
//注意，名字要符合才行

int main() {
	int a = 10;
	int b = 20;
	int sum = Add(a, b);
	//现在想要使用别人的Add
	//静态库引用和使用
	printf("%d\n", sum);
	return 0;
}
//当我们拿到add.h和add.lib这两个文件之后
//引入静态库，就可以使用了
//这样我们就可以将我们的代码很好的隐藏 只暴露声明，不暴露源代码

#endif




//函数递归
//程序调用自身的编程技巧成为递归(recursion)
#if 0
int main() {
	printf("hehe\n");
	main();
	return 0;
}
//这就是一个递归，但是，这个是一个错误递归，会栈溢出的
//死递归
#endif



#include<string.h>
//编写函数不允许创建临时变量，求字符串长度
int my_strlen(char* str) {
	if (*str == '\0') {
		return 0;
	}
	return 1 + my_strlen(str + 1);
}
int main() {
	char* arr = "abcdefg";
	int len = my_strlen(arr);
	printf("%d\n", len);
	return 0;
}