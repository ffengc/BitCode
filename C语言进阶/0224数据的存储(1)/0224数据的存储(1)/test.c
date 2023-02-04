#define _CRT_SECURE_NO_WARNINGS 1



#include<stdio.h>


//整型家族
//char--unsigned char--signed char
//short--...
//int--...
//long--...



//short--2byte--16bit
//0000000000000001--1
//最高位
//如果是signed的
//最高位表示符号位


//浮点型家族


//指针类型

//自定义类型


//原反补
#if 0
int main() {
	int a = 10;

	int b = -10;
	//原反补
	//补：
	//1111 1111 1111 1111 1111 1111 1111 0110
	//  f   f    f    f    f    f    f    6
	//0xff ff ff f6

	return 0;
}


int main() {
	//1-1
	//1+(-1)
	//CPU只有加法器

	//00000000000000000000000000000001
	//10000000000000000000000000000001
	//使用原码计算是错误的
	//00000000000000000000000000000001
	//11111111111111111111111111111111
	//100000000000000000000000000000000
	//-->
	//00000000000000000000000000000000---答案就是0
	//符号位也参与运算
	return 0;
}
#endif

//char类型的变量
//char存放的范围是什么呢
//
//-128~127
//
#if 0
int main() {
	char a = 130;
	printf("%d\n", a);
	//

	unsigned int ch = -10;
	//10000000 00000000 00000000 00001010
	//11111111 11111111 11111111 11110101
	//11111111 11111111 11111111 11110110

	printf("%u\n", ch);//%u是打印无符号数，意思是你要我打印的一定是无符号数，不是无符号数，我也认为是无符号数
	printf("%d\n", ch);//%d是打印有符号数，意思是你要我打印的一定是有符号数，不是有符号数，我也认为是有符号数

	unsigned char ch2 = -10;
	//10001010
	//11110101
	//11110110--246
	printf("%d\n", ch2);
	return 0;
}
#endif



//short
//用同样的方法确定范围
//-32768~32767

//无符号short
//0~65535
#include<limits.h>
#if 0
int main() {
	INT_MAX;
	return 0;
}
#endif


//大小端
//0x11223344
#if 0
int main() {
	int a = 0x11223344;
	//大小端字节序存储
//低                           高
//11 22 33 44---大端
//44 33 22 11---小端

	//低放低叫小端
	//高放低叫大端
	return 0;
}
#endif

//判断大小端
#if 0
int check_sys() {
	int a = 1;
	return *(char*)&a;
}
int main() {
	int ret = check_sys();
	if (ret == 1)printf("小端\n");
	if (ret == 0)printf("大端\n");
	return 0;
}
#endif


//练习
int main() {
	char a = -1;
	signed char b = -1;
	unsigned char c = -1;
	printf("a=%d,b=%d,c=%d", a, b, c);
	//-1 -1 255
	return 0;
}