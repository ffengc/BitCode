#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//结构体2

//结构体内存对齐
#if 1
struct S1 {
	char c1;
	int i;
	char c2;
};
//顺序换一下
struct S2 {
	char c1;
	char c2;
	int i;
};
int main() {
	struct S1 s1;
	struct S2 s2;
	printf("%d\n", sizeof(s1));
	printf("%d\n", sizeof(s2));
	return 0;
}
#endif
//结构体内存对齐规则
/*
* 1.第一个成员在结构体变量偏移量尾0的地址处
* 2.其它成员变量要对齐到某个数字(对齐数)的整数倍的地址处
*    对齐数=编译器默认对齐数与该成员大小的较小值
* 3.结构体总大小为最大对齐数(每个成员变量都有一个对齐数)的整数倍
* 4.如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，
*   结构体的整体大小就是所有最大对齐数(含嵌套结构体的对齐数)的整数倍
*/


//VS编译器默认对齐数是-8
//linux环境下没有默认对齐数---没有默认对齐数时，自身大小就是对齐数

//练习3
#include<stddef.h>
#if 0
struct S3 {
	double d;//偏移量为0
	char c;//偏移量为8
	int i;//偏移量为12
};
struct S4 {
	char c1;//占1
	struct S3 s3;//占16---要对齐s3里面三个成员的最大对齐数的整数倍数，也就是8
	double d;//占8
};
int main() {
#if 0
	struct S3 s3;
	printf("%d\n", sizeof(s3));//16
	printf("\n");
	printf("%u\n", offsetof(struct S3, d));
	printf("%u\n", offsetof(struct S3, c));
	printf("%u\n", offsetof(struct S3, i));
#endif
	printf("%d\n", sizeof(struct S4));//32
	return 0;
}
#endif
//offsetof - 宏
//可以计算结构体成员相对于起始位置的偏移量


//为什么存在内存对齐
/*
* 1.平台原因(移植原因)
* 不是所有的硬件平台都可以访问任意地址上的任意数据的，某些硬件平台只能在某些
* 地址处取某些特定类型的数据，否则抛出硬件异常
* 2.性能原因
* 数据结构(尤其是栈)应该尽可能地在自然边界上对齐
* 原因在于，为了访问未对齐的内存，处理器需要做两次内存访问；而对齐的内存访问只需要一次访问
*/
//总体来说：
//结构体的内存对齐时拿空间来换取时间的做法


//因此我们在设计结构体的时候
//我们要满足对齐，又要节省空间，如何做到呢？
//-----将占空间小的成员尽量放在一起


//修改默认对齐数
#if 0
#pragma pack(4)
struct S {
	char c;
	double d;
};
#pragma pack()
int main() {
	struct S s;
	printf("%d\n", sizeof(s));
	return 0;
}
#endif



//结构体传参
//传地址是最好的



//位段
/*
* 位段的声明和结构是类似的，有两个不同：
* 1.位段的成员必须是int,unsigned int或者signed int（char也是可以的）
* 2.位段的成员名后边有一个冒号和一个数字
*/
#if 0
struct A {
	int _a : 2;//_a这个成员只占两个bit位
	int _b : 5;//同理
	int _c : 10;
	int _d : 30;
};
int main() {
	printf("%d\n", sizeof(struct A));
	return 0;
}
#endif
//位段是为了节省空间的，而内存对齐是会浪费空间，两者冲突
//所以位段不存在内存对齐



/*
* 1.位段的成员可以是int,unsigned int,signed int或者是char类型
* 2.位段的空间上是按照需要以4个字节(int)或者1个字节(char)的方式来开辟的
* 3.位段涉及很多不确定因素，位段是不跨平台的，注重可移植程序应该避免使用位段
*/

//这个代码很巧妙-画出内存来分析
#if 0
struct S {
	char a : 3;
	char b : 4;
	char c : 5;
	char d : 4;
};
int main() {
	struct S s = { 0 };
	printf("%d\n", sizeof(s));
	s.a = 10;
	s.b = 12;
	s.c = 3;
	s.d = 4;
	return 0;
}
#endif
//00000000  00000000  00000000
//假设从高位往低位放  即:<--
//00000000
//     ^^^--放a  10是1010 所以只能放010
//00000010
// ^^^^---这些是b的 b是1100 正好可以放进去
//01100010 00000000  00000000
//            ^^^^^---这些是c的 放00011
//01100010 00000010  00000000
//                       ^^^^----这些是d的
//01100010 00000010  00000100
// 6    2    0   3     0    4
//在vs底下的案例


//位段的跨平台问题
/*
* 1.int位段被当成符号数还是无符号数是不确定的
* 2.位段中最大位的数目不能确定【16位及其最大16，32位机器最大32，写成27，在16位机器会出问题】
* 3.位段中的成员在内存中从左向右分配，还是从右想做分配标准尚未定义
* 4.当一个结构包含两个位段，第二个位段成员比较大，无法容纳于第一个位段剩余位时，是舍弃剩余的位还是利用，这是不确定的
*/
//总结：
//跟结构体相比，位段可以达到同样的效果，而且可以很好的节省空间，但是具有跨平台问题存在


//大小端讨论的是字节之间的存储顺序，而这个是字节内部的顺序，是不一样的



//枚举
#if 0
enum Sex {
	MALE,
	FEMALE,
	SECRET
};
enum Day {
	Mon,
	Tues,
	Wed,
	Thur,
	Fri,
	Sat,
	Sun
};
int main() {
	enum Sex s = MALE;
	enum Sex s2 = FEMALE;
	return 0;
}
//不初始化默认从0开始，初始化也可以，后面默认顺着走
enum Color {
	RED = 5,//5
	GREEN = 8,//8  这里面的数据是常量，不能赋值，这里'='不是赋值，而是初始化
	               //外面是改不了的
	BLUE//9
};
#endif
//用枚举可以让代码的可读性更高



//联合体(共用体)
#if 0
union Un {
	char c;
	int i;
};
int main() {
	union Un u;
	printf("%d\n", sizeof(u));
	printf("%p\n", &u);
	printf("%p\n", &(u.c));
	printf("%p\n", &(u.i));
	//三个地址是一样的

	//所以，我们改c的时候i也改了，改i的时候c也改了
	//所以我们只用一个，用c不用i，用i不用c

	u.c = 55;
	u.i = 0;
	return 0;
}
#endif
//联合的成员公用同一块内存空间，这样一个联合体变量的大小，至少是最大成员的大小
//因为联合至少得有能力保存最大的那个成员

//判断大小端
#if 0
int check_sys() {
	union Un {
		char c;
		int i;
	}u;
	u.i = 1;
	return u.c;
}
int main() {
	if (1 == check_sys()) {
		printf("小端\n");
	}
	else {
		printf("大端\n");
	}
	return 0;
}

union Un {
	char arr[5];//这里相当于放了5个char
	int i;
};
int main() {
	printf("%d\n", sizeof(union Un));
	return 0;
}
#endif
