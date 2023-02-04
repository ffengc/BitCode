#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//#define
//1.定义标识符常量
//2.定义宏

#if 0
#define NUM 100
#define STR "abcdef"
int main() {
	int num = NUM;
	char name[] = STR;

	return 0;
}
#endif
//把项目属性 预处理 预处理到文件打开改为是，编译就会产生一个test.i文件在后台
//打开，就可以发现，完全替换了


//因为是完全替换
//所以还可以替换比较长的关键字
#if 0
#define reg register
int main() {
	int reg num = 100;
	return 0;
}



// 如果定义的 stuff过长，可以分成几行写，除了最后一行外，每行的后面都加一个反斜杠(续行符)。
#define DEBUG_PRINT printf("file:%s\tline:%d\t \
                          date:%s\ttime:%s\n" ,\
__FILE__,__LINE__ ,       \
__DATE__,__TIME__ )  
#endif



//#define 定义宏
/*#define 机制包括了一个规定，允许把参数替换到文本中，这种实现通常称为宏（macro）或定义
宏（define macro）。
*/


#if 0
#define MAX(x,y) (x>y?x:y)
int main() {
	int a = 10;
	int b = 20;
	printf("%d\n", MAX(a, b));
	return 0;
}
#endif


//写宏的时候要注意
#if 0
#define SQUARE(x) x*x
#define SQUARE2(x) ((x)*(x))
//尽量都把括号带上
int main() {
	int a = 9;
	int r = SQUARE(a+1);
	int r2 = SQUARE2(a + 1);
	//int r=a+1*a+1
	printf("%d %d", r,r2);
	return 0;
}
#endif


//#define替换规则
/*在程序中扩展#define定义符号和宏时，需要涉及几个步骤。
1. 在调用宏时，首先对参数进行检查，看看是否包含任何由#define定义的符号。如果是，它们首先
被替换。
2. 替换文本随后被插入到程序中原来文本的位置。对于宏，参数名被他们的值所替换。
3. 最后，再次对结果文件进行扫描，看看它是否包含任何由#define定义的符号。如果是，就重复上
述处理过程。
注意：
1. 宏参数和#define 定义中可以出现其他#define定义的符号。
   但是对于宏，不能出现递归。
2. 当预处理器搜索#define定义的符号的时候，字符串常量的内容并不被搜索。
*/
#if 0
#define M 100
int main() {
	printf("M is %d\n", M);
	//这里面的M是不被替换的
	return 0;
}
#endif


//#和##
#if 0
#define PRINT(N) printf("the value of "#N" is %d\n",N)
//                会把a不做任何替换，直接转化成字符串，插入进去
int main() {
	/*
	int a = 10;
	printf("the value of a is %d\n", a);
	int b = 10;
	printf("the value of b is %d\n", b);
	*/
	//有些东西是重复的
	//想封装成函数是很难的
	//宏是可以做到了
	int a = 10;
	PRINT(a);
	int b = 20;
	PRINT(b);
	return 0;
}

#endif
#if 0
int main() {
	printf("hello bit\n");
	printf("hello ""bit\n");
	//这是一样的
	return 0;
}
#endif

#if 0
#define PRINT(N,format) \
printf("the value of "#N" is "format"\n",N)
int main() {
	int a = 20;
	double pai = 3.14;
	PRINT(a, "%d");
	PRINT(pai, "%lf");
	return 0;
}
#endif


//##的作用
/*##可以把位于它两边的符号合成一个符号。
它允许宏定义从分离的文本片段创建标识符*/
#if 0
#define CAT(name,num) name##num
int main() {
	int _class105 = 105;
	printf("%d\n", CAT(_class, 105));
	return 0;
}
#endif


//带有副作用的宏参数
//x+1;//不带副作用
//x++;//带有副作用
/*当宏参数在宏的定义中出现超过一次的时候，如果参数带有副作用，那么你在使用这个宏的时候就可能
出现危险，导致不可预测的后果。副作用就是表达式求值的时候出现的永久性效果。
*/
#if 0
int main() {
	int a = 2;
	//int b = a + 1;
	int b = ++a;//对a产生了副作用
	return 0;
}
#endif


#if 0
#define MAX(x,y) ((x)>(y)?(x):(y))
int main() {
	int a = 5;
	int b = 8;
	int c = MAX(a++, b++);
	//int c=((a++)>(b++)?(a++):(b++))
	printf("%d\n", c);//9
	printf("%d\n", a);//6
	printf("%d\n", b);//10
	return 0;
}
#endif


//宏和函数的对比
/*
宏通常被应用于执行简单的运算。
比如在两个数中找出较大的一个。
那为什么不用函数来完成这个任务？
原因有二：
1. 用于调用函数和从函数返回的代码可能比实际执行这个小型计算工作所需要的时间更多。
所以宏比函数在程序的规模和速度方面更胜一筹。
2. 更为重要的是函数的参数必须声明为特定的类型。
所以函数只能在类型合适的表达式上使用。反之这个宏怎可以适用于整形、长整型、浮点型等可以
用于>来比较的类型。
宏是类型无关的。
宏的缺点：当然和函数相比宏也有劣势的地方：
1. 每次使用宏的时候，一份宏定义的代码将插入到程序中。除非宏比较短，否则可能大幅度增加程序
的长度。
2. 宏是没法调试的。
3. 宏由于类型无关，也就不够严谨。
4. 宏可能会带来运算符优先级的问题，导致程容易出现错。
宏有时候可以做函数做不到的事情。比如：宏的参数可以出现类型，但是函数做不到。
*/

#if 0
#include<stdlib.h>
#define MALLOC(num,type) (type*)malloc(num*sizeof(type))
int main() {
	int* p = (int*)malloc(10 * sizeof(int));
	//如果这样写嫌麻烦
	//如果能这样写就好了--用宏
	int* p2 = MALLOC(10, int);
	return 0;
}
#endif

//C99 inline 内联
//内联函数 - 结合了函数的优点和宏的优点



/*命名约定
一般来讲函数的宏的使用语法很相似。所以语言本身没法帮我们区分二者。
那我们平时的一个习惯是：
把宏名全部大写
函数名不要全部大写
*/
//当然也有特例 - offsetof等


//#undef - 移除一个宏定义
#if 0
#include<stdlib.h>
#define MALLOC(num,type) (type*)malloc(num*sizeof(type))
int main() {
	int* p = (int*)malloc(10 * sizeof(int));
	//如果这样写嫌麻烦
	//如果能这样写就好了--用宏
	int* p2 = MALLOC(10, int);
#undef MALLOC
	//MALLOC
	return 0;
}
#endif


//命令行定义
//命令行在vs上无法演示
/*
许多C 的编译器提供了一种能力，允许在命令行中定义符号。用于启动编译过程。
例如：当我们根据同一个源文件要编译出不同的一个程序的不同版本的时候，这个特性有点用处。（假
定某个程序中声明了一个某个长度的数组，如果机器内存有限，我们需要一个很小的数组，但是另外一
个机器内存大写，我们需要一个数组能够大写。）
*/
//在linux上演示
#if 0
#include <stdio.h>
int main()
{
	int array[ARRAY_SIZE];
	int i = 0;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = i;
	}
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
#endif
//一个源文件弄出不同的版本，就可以这样用



//条件编译
#if 0
int main() {
	int arr[10] = { 0 };
	int i = 0;
	for (i = 0; i < 10; i++) {
		arr[i] = i;
#if 0
		printf("%d ", arr[i]);
#endif
	}
	return 0;
}
#endif
//#if 后面一定是常量表达式
//多分支也一样，和条件语句很相似的
#if 0
#define NUM 3
int main() {
#if NUM==1
	printf("hehe\n");
#elif NUM==2
	printf("haha\n");
#else 
	printf("heihei\n");
#endif
	return 0;
}
#endif



#if 0
#define MAX 1
int main() {
#if defined MAX
	printf("hehe\n");
#endif
	//或者
#ifdef MAX
	printf("heihei\n");
#endif
	//这两种写法是一样的


	//写反面也是一样的
#if !defined MAX
	printf("hehe\n");
#endif
#ifndef MAX
	printf("hehe\n");
#endif
	//这两种也是一样的

	//条件编译嵌套也是可以的
	return 0;
}
#endif



//文件包含
//#include<>
//#include""
/*查找策略：先在源文件所在目录下查找，
如果该头文件未找到，编译器就像查找库函数头文件一样在标
准位置查找头文件。
如果找不到就提示编译错误。
*/
//Linux /usr/include


//如果被包含了三次，就会重复了
//如果嵌套包含的时候，就会容易出现重复包含的情况，可以用linux调试看出来
//所以用这种方式
//头文件里面这样写
#ifndef _TEST_H_
#define _TEST_H_
//...
#endif
//当让还有一种方式
//直接写，现代一点的写法
#pragma once
//也可以


#if 0
//其它预处理指令《C语言深度解剖》
#line
#error
//等等
#endif