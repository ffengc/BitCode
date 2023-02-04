#define _CRT_SECURE_NO_WARNINGS 1

//指针进阶2

#include<stdio.h>

int(*parr3[10])[5];
//parr3是一个数组，数组有10个元素，每个元素的类型是int(*)[5],即一些数组的地址

//一维数组传参
#if 0
void test(int arr[10]) {};//ok,10没有意义
void test(int arr[]) {};//ok
void test(int* arr) {};
void test2(int* arr[20]) {};
void test2(int** arr) {};
int main() {
	int arr[10] = { 0 };
	int* arr2[20] = { 0 };
	test(arr);
	test2(arr2);
	return 0;
}
#endif 



//二维数组传参
#if 0
void test(int* arr);//不ok
void test(int* arr[5]);//不ok
void test(int(*arr)[5]);//ok
void test(int** arr);//ok
int main() {
	int arr[3][5] = { 0 };
	test(arr);
	return 0;
}
#endif


#if 0
//函数指针
int Add(int x, int y) {
	return x + y;
}
int main() {
	printf("%p\n", &Add);
	printf("%p\n", Add);
	//Add和&Add是完全一样的
	//这个和数组有差别
	//Add和&Add是完全一样的
	int(*pf)(int, int) = Add;
	//这里的pf就是函数指针变量

	//函数指针的使用
	int ret1 = (*pf)(2, 3);
	int ret2 = pf(2, 3);
	//我们发现*和不加*都可以
	//*只是摆设而已
	//但是加上*，方便理解，更符合语法
	//但是如果要加*，就一定要括起来
	printf("%d\n", ret2);
	return 0;
}
#endif

//两段有趣的代码
#if 0
int main() {
	(*(void(*)())0)();
	//void(*)()是一个函数指针类型
	//这个类型放到了括号里面
	//类型放到括号里面代表强制类型转换
	//(void(*)())0,对0进行强制类型转换成一个函数指针
	//然后再调用这个函数
	//所以
	//1.把0强转成一个函数指针，这就一位这0地址处放一个返回类型是void，无参的一个函数
	//2.调用0地址处的这个函数



	void(*signal(int, void(*)(int)))(int);
	//signal(int, void(*)(int))说明
	//signal是个函数，第一个参数是int，第二个参数是函数指针类型
	//然后把它去掉，就剩下
	//void(*)(int)，也就是函数的返回类型
	//综上：
	//signal是一个函数，第一个参数是int，第二个参数是函数指针类型
	//signal的返回值是一个函数指针
	//所以这句话是一个函数声明

	//我们此时发现，第二个参数和返回值类型是一样的
	typedef void(*pf_t)(int);//将void(*)(int)重新起名叫：pf_t
	//所以
	pf_t signal(int, pf_t);
}
#endif


#if 0
//函数指针数组
int Add(int x, int y) {
	return x + y;
}
int Sub(int x, int y) {
	return x - y;
}
int Mul(int x, int y) {
	return x * y;
}
int Div(int x, int y) {
	return x / y;
}
int main() {
#if 0
	//函数指针
	int(*pf1)(int, int) = Add;
	int(*pf2)(int, int) = Sub;
	int(*pf3)(int, int) = Mul;
	int(*pf4)(int, int) = Div;
#endif
	//函数指针数组
	int(*pf[4])(int, int) = { Add, Sub, Mul, Div };

	int i = 0;
	for (i = 0; i < 4; i++) {
		int ret = pf[i](8, 2);
		printf("%d\n", ret);
	}
	return 0;
}
#endif



//实现一个计算器
#if 0
int Add(int x, int y) {
	return x + y;
}
int Sub(int x, int y) {
	return x - y;
}
int Mul(int x, int y) {
	return x * y;
}
int Div(int x, int y) {
	return x / y;
}
void menu() {
	printf("-----------\n");
	printf("   1.Add   \n");
	printf("   2.Sub   \n");
	printf("   3.Mul   \n");
	printf("   4.Div   \n");
	printf("   9.exit  \n");
	printf("-----------\n");
}
int main() {
	int input = 0;
	int x = 0;
	int y = 0;
	do {
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		int ret = 0;
		switch (input) {
		case 1:
			printf("请输入两个操作数：");//这两句就冗余了
			scanf("%d %d", &x, &y);
			ret = Add(x, y);
			printf("结果是:%d\n", ret);
			break;
		case 2:
			printf("请输入两个操作数：");
			scanf("%d %d", &x, &y);
			ret = Sub(x, y);
			printf("结果是:%d\n", ret);
			break;
		case 3:
			printf("请输入两个操作数：");
			scanf("%d %d", &x, &y);
			ret = Mul(x, y);
			printf("结果是:%d\n", ret);
			break;
		case 4:
			printf("请输入两个操作数：");
			scanf("%d %d", &x, &y);
			ret = Div(x, y);
			printf("结果是:%d\n", ret);
			break;
		case 0:
			printf("退出计算器\n");
			break;
		default:
			printf("err,请重新选择");
			break;
		}
	} while (input);
	return 0;
}
#endif



//改进
int Add(int x, int y) {
	return x + y;
}
int Sub(int x, int y) {
	return x - y;
}
int Mul(int x, int y) {
	return x * y;
}
int Div(int x, int y) {
	return x / y;
}
void menu() {
	printf("-----------\n");
	printf("   1.Add   \n");
	printf("   2.Sub   \n");
	printf("   3.Mul   \n");
	printf("   4.Div   \n");
	printf("   9.exit  \n");
	printf("-----------\n");
}
int main() {
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;
	int (*pfArr[5])(int, int) = { NULL,Add,Sub,Mul,Div };
	do {
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		if (input == 0) {
			printf("退出计算器\n");
		}
		else if (input >= 1 && input <= 4) {
			printf("请输入两个操作数：");//这两句就冗余了
			scanf("%d %d", &x, &y);
			ret = pfArr[input](x, y);
			printf("结果为：%d\n", ret);
		}
		else {
			printf("err\n");
		}
		
		
	} while (input);
	return 0;
}
//函数指针其实就有跳板的作用
//这个函数指针的使用叫转移表