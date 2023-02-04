#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//输出1-100间的奇数
#if 0
int ifOdd(int x) {
	return x % 2 == 1 ? 1 : 0;
}
int main() {
	int input = 0;
	printf("请输入n:");
	scanf("%d", &input);
	for (int i = 1; i <= input; i++) {
		if (ifOdd(i)) {
			printf("%d ", i);
		}
	}
}
//switch语句
//case后面只能跟 整型常量表达式
#endif

//循环
//continue:跳过本次循环

#if 0
//看几个代码
int main() {
	int ch = 0;
	while ((ch = getchar()) != EOF)
		putchar(ch);
	return 0;
}
//在用getchar()的时候，按ctrl Z可以触发getchar()的-1返回值，让循环终止
//但是scanf()的时候输入ctrl Z不一定能停下来，这个是vs的一个bug，vs下要输入三个ctrl Z才行


//例子
int main() {
	char password[20] = { 0 };
	printf("请输入密码:");
	scanf("%s", password);

	printf("请确认密码(Y/N):");
	int ch = getchar();
	if ('Y' == ch)
		printf("确认成功\n");
	else
		printf("确认失败\n");
	return 0;
}
//err
//这个代码是不能实现想要的功能的，在这个代码中，getchar获取的是缓冲区里面的\n ，所以一定是确认失败的

//稍微修改一下
int main() {
	char password[20] = { 0 };
	printf("请输入密码:");
	scanf("%s", password);

	getchar();//处理\n

	printf("请确认密码(Y/N):");
	int ch = getchar();
	if ('Y' == ch)
		printf("确认成功\n");
	else
		printf("确认失败\n");
	return 0;
}
#endif
//err
//这个如果输入 123456 abcdef\n也会弹不出printf("请确认密码(Y/N):");的，
//因为getchar也会直接拿后面的东西，直接给ch，所以我们要再改，用getchar处理一串东西才行
#if 0
int main() {
	char password[20] = { 0 };
	printf("请输入密码:");
	scanf("%s", password);

	//方法
	int tmp = 0;
	while ((tmp = getchar()) != '\n') {
		;//这样，\n之前的，包括\n的都会被处理掉了
	}

	printf("请确认密码(Y/N):");
	int ch = getchar();
	if ('Y' == ch)
		printf("确认成功\n");
	else
		printf("确认失败\n");
	return 0;
}
#endif


#if 0
//例子
int main() {
	int ch = 0;
	while ((ch = getchar()) != EOF) {
		if (ch < '0' || ch>'9')
			continue;
		putchar(ch);
	}
	return 0;
}
//作用：读取字符，但是只打印数字字符
#endif


//for循环
#if 0
int main() {
	int i = 0;
	for (i = 1; i <= 10; i++) {
		printf("%d ", i);
	}
	return 0;
}
#endif

//这里打印多少hehe?
#if 0
int main() {
	int i = 0;
	int j = 0;
	for (; i < 10; i++) {
		for (; j < 10; j++) {
			printf("hehe\n");
		}
	}
	return 0;
}
//这里只会打印10个，很多人会误以为是100个
//因为第二次进j循环的时候，j不会被初始化为0，还是10，所以内层循环后面一直都进不去了
#endif


#if 1
//两个循环变量控制
//但是非常少见
int main() {
	int x = 0;
	int y = 0;
	for (x = 0, y = 0; x < 2 && y < 5; ++x, y++) {
		printf("hehe\n");
	}
	return 0;
}
#endif