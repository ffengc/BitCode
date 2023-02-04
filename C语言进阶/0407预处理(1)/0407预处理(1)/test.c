#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

/*1. 程序的翻译环境和执行环境
在ANSI C的任何一种实现中，存在两个不同的环境。
第1种是翻译环境，在这个环境中源代码被转换为可执行的机器指令。
第2种是执行环境，它用于实际执行代码
*/

//test.c-------test.exe-------运行结果
// 翻译环境（编译器）   执行环境（操作系统）


//翻译环境
//test.c----test.obj
//contact.c-----contact.obj
//每个源文件经过编译器生成对应的目标文件(.obj)文件之后
//加上链接库经过链接器---可执行程序(链接库：库函数等)

//编译（编译器）   链接（链接器）

#if 1
extern int Add(int, int);
int main() {
	int a = 10;
	int b = 20;
	int c = Add(a, b);
	int d = Sub(a, b);
	printf("%d\n", c);
	printf("%d\n", d);
	return 0;
}
#endif

//VS2022
//DEV C++
//CodeBlocks
//Clion
//集成开发环境-IDE
//继承了编辑，编译，链接，调试等功能

//编译器(cl.exe)
//链接器(link.exe)

//编译=预编译+编译+汇编
//最后生成.obj文件

//预编译（预处理）
//为了更好的观察每一个步骤，这里食用Linux gcc来演示
//gcc test.c -E （在预编译之后停下来
//再-o 放到test.i里面
//所以
//gcc test.c -E -o test.i
//打开来观察一下

//前面多了一大堆东西，是不是把stdio.h的东西放进来了呢
//我们可以看一下
//linux环境下，头文件放在/usr/include下面

//所以可以得到一个结论
//预编译的时候，完成了头文件的包含
//同时#define定义符号替换，也在这里完成
//注释同时删除


//编译
//指令：gcc test.i -S
//生成一个test.s文件
//所以在这时期：把C语言代码翻译成了汇编代码
//1.语法词法分析
//2.语义分析
//3.符号汇总

//汇编
//gcc test.s -c
//生成test.o文件
//windows环境下
//目标文件：xxx.obj
//linux环境下
//目标文件：xxx.o
//目标文件是二进制的---是看不懂的
//此过程：
//把汇编指令翻译成二进制指令
//完成的东西：
//形成符号表


//linux环境下
//test.o
//可执行程序的格式是：elf
//有一个工具：readelf
//我们可以-s看符号表
//每个符号所对应的地址
//这样我们在不同文件之间，可以通过符号的地址找到相对应符号



//链接：
//1.合并段表
//2.符号表的合并和重定位

//合并段表：就是把相同的东西合并在一起
//符号表的合并和重定位：
//当我们合并Add符号的时候，发现两个地址不一样
//所以链接的时候就把Add合并，形成一个新地址（test.c里面的Add没有有效地址，add.c里面才有
//如果我们把add.c里面的Add干掉，欸合并的时候，找不到有效地址，就会报链接错误


//《程序员的自我修养》


//linux 
//vim - 编辑器


#if 0
//预处理详解
//预处理符号
int main() {
	printf("%s\n", __FILE__);
	printf("%d\n", __LINE__);
	printf("%s\n", __DATE__);
	printf("%s\n", __TIME__);
	printf("%s\n", __FUNCTION__);
	//printf("%d\n", __STDC__);//说明vs2022不支持ANSIC
	//gcc是支持的
	return 0;
}
#endif