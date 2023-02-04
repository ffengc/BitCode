#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//请问循环多少次
#if 0
int main() {
	int i = 0;
	int k = 0;
	for (i = 0, k = 0; k = 0; i++, k++) {
		k++;
	}
	return 0;
}
//0次，因为k=0恒为假
#endif

//求结果
#if 0
int main() {
	//1~10
	int i = 1;
	do {
		if (i == 5)
			continue;
		printf("%d ", i);
		i++;
	} while (i <= 10);
	return 0;
}
//死循环 1 2 3 4
#endif



//字符向中间汇聚
#if 0
#include<string.h>
#include<windows.h>
#include<stdlib.h>
int main() {
	char arr1[] = "welcome to bit!!!!!!";
	char arr2[] = "####################";
	int left = 0;
	int right = strlen(arr1) - 1;
	while (left <= right) {
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		printf("%s\n", arr2);
		Sleep(1000);//睡眠一秒(单位是毫秒)
		system("cls");//(清屏)
		left++;
		right--;
	}
	return 0;
}
#endif

#if 0
//猜数字游戏
//1.电脑随机生成一个数字(1~100)
//2.玩家猜数字
//  玩家猜小了，就告知猜小了
//  玩家猜大了，就告知猜大了
//  直到猜对位置
//3.游戏可以一直玩
#include<stdlib.h>
#include<time.h>
void menu() {
	printf("******************************\n");
	printf("*******    1.play   **********\n");
	printf("*******    2.exit   **********\n");
	printf("******************************\n");
}
//RAND_MAX;
//时间戳
//C语言提供了一个函数time，可以返回一个时间戳
void game() {
	int guess = 0;
	//1.生成一个随机数
	// 调用rand()函数
	int ret = rand() % 100 + 1;//把随机数控制在1-100之间
	//2.猜数字
	while (1) {
		printf("猜数字:>");
		scanf("%d", &guess);
		if (guess < ret)
			printf("猜小了\n");
		else if (guess > ret)
			printf("猜大了\n");
		else {
			printf("恭喜你猜对了\n");
			break;
		}
	}
}
int main() {
	int input = 0;
	srand((unsigned int)time(NULL));//此处不需要把time函数的返回值存起来，只需要返回的那个数就行了
	//这个srand()在整个程序中只需要调用一次即可
	do {
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input) {
		case 1:			
			game();
			break;
		case 0:
			printf("退出游戏!\n");
			printf("------------------------------\n");
			break;
		default:
			printf("选择错误，请重新选择!\n");
			printf("------------------------------\n");
			break;
		}
	} while (input);

	return 0;
}
#endif


//time函数
#include<windows.h>
#include<time.h>
#if 0
int main() {
	//获取时间戳
	time_t t1 = time(NULL);
	//或
	Sleep(10000);
	time_t t2;
	time(&t2);
	printf("%d\n", t1);
	printf("%d\n", t2);
	return 0;
}
#endif

//goto语句
//跳到标签
//但是不能跨函数跳
//作用：用时候要跳出多层循环的时候用，不用写太多break了



//关机程序
//只要程序运行起来，电脑就在1分钟内关机，如果输入：我是猪，就取消关机。
//在电脑命令行里面输入 shutdown -s -t 60
//就是60s关机
//shut -a 取消关机
//在system()函数里面执行命令和在windows命令行里面执行命令是一样的
int main() {
	char input[20] = { 0 };
	system("shutdown  -s -t 60");//system是一个库函数，是用来执行系统命令的
again:
	printf("请注意，你的电脑在一分钟内关机，如果输入：我是猪，就取消关机\n");
	scanf("%s", input);
	if (strcmp(input, "我是猪") == 0) {
		system("shutdown -a");//取消关机
	}
	else {
		goto again;
	}
	return 0;
}