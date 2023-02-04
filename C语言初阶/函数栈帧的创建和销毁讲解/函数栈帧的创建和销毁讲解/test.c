#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

//函数的栈帧的创建和销毁


//不要使用太高级的编译器，越高级的编译，越不容易学习和观察。
//同时在不同的编译器下，函数调用过程中栈帧的创建是略有差异的，具体细节取决于编译器的实现


//寄存器
//eax ebx ecx edx
//ebp esp


//要理解函数栈帧就必须理解好ebp，esp这两个寄存器
//这两个寄存器中存放的是地址
//这两个地址是用来维护函数栈帧的

//每一个函数调，都要创建一个空间

//stack区 heap区(动态开辟)


int Add(int x, int y) {
	int z = 0;
	z = x + y;
	return z;
}
int main() {
	int a = 10;
	int b = 20;
	int c = 0;
	c = Add(a, b);
	printf("%d\n", c);
	return 0;
}


//假设main()开辟一块栈帧
//怎么维护呢
//ebp存了main()的高地址--栈底指针
//esp存了main()的低地址--栈底指针

//在vs2013中
//main()也是被别人调用的
//mainCRTStartup()调用__tmainCRTStartup()
//再调用main(argc,argv,envp)
//最后return的值放回mainret里面去了


//Add()的时候，在栈的上面再分配空间


//lea
//load effective address

//为a,b,c开辟好之后
//开始传参
//发现先传b



//形式参数根本就不在Add的栈帧里面
//是在Add的下面
//也就是高地址的地方
//隔着4个字节