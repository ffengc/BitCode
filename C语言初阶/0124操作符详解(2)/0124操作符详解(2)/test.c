#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>


//求一个整数存储在内存中二进制中1的个数
#if 0
int count_bit(int x) {
	int count = 0;
	//按位与一个1
	//得到1说明最低位是1，得到0说明最低位是0
	for (int i = 0; i < 32; i++) {
		if ((x >> i) & 1) {
			count++;
		}
	}
	return count;
}
int main() {
	int input = 0;
	scanf("%d", &input);
	int ret = count_bit(input);
	printf("%d\n", ret);
	return 0;
}
#endif
//-1 -- 32
//-1的补码是32个1




#include<stdbool.h>
bool fun(int x);



//sizeof()是一个操作符不是函数

#if 0
int main() {
	int a = 10;
	short s = 0;
	printf("%d\n", sizeof(s = a + 2));//2
	printf("%d\n", s);//0
	//sizeof()里面的表达式是没有参加计算的
	//我只需要知道最后的s是什么类型就可以了
	return 0;
}
#endif



//sizeof和数组
#if 0
void test1(int* arr) {
	printf("%d\n", sizeof(arr));//4
}
void test2(char* ch) {
	printf("%d\n", sizeof(ch));//4
}
int main() {
	int arr[10] = { 0 };
	char ch[10] = { 0 };
	printf("%d\n", sizeof(arr));//40
	printf("%d\n", sizeof(ch));//10
	test1(arr);
	test2(ch);
	return 0;
}
#endif


//~ 对一个数字的二进制位按位取反
#if 0
int main() {
	int a = 0;
	//00000000000000000000000000000000
	//11111111111111111111111111111111
	//11111111111111111111111111111110
	//10000000000000000000000000000001--1
	printf("%d\n", ~a);

	return 0;
}
#endif



//想对13 的1011中间的0改成1
#if 0
int main() {
	int a = 11;
	//00001011
	//00000100--或上一个4即可
	//4怎么得到？
	//00000001左移两位
	a |= (1 << 2);
	//怎么改回来
	//只要00001111
	//与上一个
	//   11111011即可
	a &= (~(1 << 2));
	printf("%d\n", a);
	return 0;
}
#endif



//为什么while(~scanf("%d",&n))可以终止循环
//本来是!=EOF
//EOF=-1
//-1按位取反
//10000000000000000000000000000001--1的原码
//11111111111111111111111111111110--1的反码
//11111111111111111111111111111111--1的补码
//~(-1)=
//00000000000000000000000000000000--->0
//所以括号内为假



//注意，||两边只要有一个真的，后面的就不算了
#if 0
int main() {
	int i = 0, a = 0, b = 2, c = 3, d = 4;
	i = a++ || ++b || d++;
	printf("%d %d %d %d", a, b, c, d);
	//1 3 3 4
	return 0;
}
#endif




//逗号表达式
#if 0
int main() {
	int a = 0;
	//a = get_val();
	//count_val(a);
	//while (a > 0) {
	//	//业务处理
	//	a = get_val();
	//	count_val(a);
	//}

	//上面那种写法，代码有冗余，有重复，使用逗号表达式的话就可以写成：
	while (a = get_val(), count_val(a), a > 0) {

	}
	return 0;
}
#endif


//下标引用操作符
#if 0
int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("%d\n", arr[5]);
	printf("%d\n", 5[arr]);
	printf("%d\n", *(arr + 5));
	return 0;
}
#endif 


//函数调用操作符
#if 0
int getMax(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int a = 10;
	int b = 20;
	int max = getMax(10, 20);
	//()就是函数调用操作符
	printf("%d\n", max);
	return 0;
}
#endif
//函数操作符至少一个操作数:即函数名



//结构体成员访问操作符
//"->","."





//表达式求值
//隐式类型转换
//整型提升

/*
* C的整型算数运算总是至少以缺省整型类型的精度来进行的
* 为了获得这个精度，表达式中的字符和短整型操作数在使用之前被转换为
* 普通整型，这种转换称为整型提升
*/
#if 0
int main() {
	char c1 = 3;
	//00000011-3
	//00000000000000000000000000000011
	//但是char只能存八个
	//所以00000011
	char c2 = 127;
	//01111111---c2只能存这些
	char c3 = c1 + c2;
	//要相加的时候，要把两个整型进行提升才行
	//补回去
	//00000000000000000000000000000011和
	//00000000000000000000000001111111
	//相加
	//00000000000000000000000010000010
	//截断
	//10000010-c3
	//要打印整型
	//提升
	//11111111111111111111111110000010-看作补码
	//11111111111111111111111110000001
	//10000000000000000000000001111110-原码-(-126)
	printf("%d\n", c3);//-126
	return 0;
}
#endif
//都要先转换成整型才进行计算
//整型提升的方法
/*
* 负数的整型提升：
* 高位补符号位，即1
* 正数的整型提升：
* 高位补0
* 无符号整型的提升
* 高位补0
*/


//char是
//signed char还是unsigned char是取决于编译器的


//整型提升的案例1
#if 0
int main() {
	char a = 0xb6;
	short b = 0xb600;
	int c = 0xb6000000;
	if (a == 0xb6)//整型提升后就不是0xb6了
		printf("a");
	if (b == 0xb600)//同样
		printf("b");
	if (c == 0xb6000000)
		printf("c");//只打印这个
	return 0;
}
#endif



//整型提升案例2
#if 0
int main() {
	char c = 1;
	printf("%u\n", sizeof(c));//1
	printf("%u\n", sizeof(+c));//4
	printf("%u\n", sizeof(-c));//4
	//后两个参与了计算，所以被提升了
	return 0;
}
#endif




