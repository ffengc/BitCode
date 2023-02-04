#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>


//2.
#if 0
int main() {
	int x = 1;
	do {
		printf("%2d\n", x++);
	} while (x--);
	return 0;
}
#endif

//3.
#if 0
int main() {
	char* p[] = { "shanghai","beijing","hongkong" };
	printf("%c\n", *(p[1] + 3));

	return 0;
}
#endif


//5.
//2-10


//6.
#if 0
int main() {
	int p[][4] = { {1},{3,2}, {4,5,6},{0} };
	printf("%d\n", p[1][2]);
	return 0;
}
#endif



//7.
#if 0
#pragma pack(8)
struct One {
	double d;
	char c;
	int i;
};
struct Two {
	char c;
	double d;
	int i;
};
#pragma pack()
int main() {
	printf("%d\n", sizeof(struct One));
	printf("%d\n", sizeof(struct Two));
	return 0;
}
#endif


//8.
#if 0
int f(int x) {
	return ((x > 2) ? x * f(x - 1) : 3);
}
int main() {
	int i = 0;
	i = f(f(2));
	printf("%d\n", i);
	return 0;
}
#endif

//9.
#include<stdlib.h>
#if 0
void main() {
	int a = -3;
	unsigned int b = 2;
	long c = a + b;
	printf("%ld\n", c);
	//用二进制的方式去算，保证算出来是对的
}
#endif

#if 0
int main() {
	char a = 1;
	int b = 2;
	float c = 3.55;
	double d = 4.324342;
	cout << a * b + d - c << endl;
	return 0;
}
#endif



#if 0
#define N 3+1
#define Y(n) ((N+1)*n)
int main() {
	int ret = 2 * (N + Y(5 + 1));
	//2*(3+1+((3+1+1)*5+1)
	//
	printf("%d\n", ret);
}
#endif



#if 0
//1abcedf2df
int main() {
	char a = 0, ch;
	while ((ch = getchar()) != '\n') {
		if (a % 2 != 0 && (ch >= 'a' && ch <= 'z'))
			ch = ch - 'a' + 'A';
		    //ch=ch-32//其实就是小写转大写
		a++;
		putchar(ch);
	}
	printf("\n");
	return 0;
}
#endif


#if 0
int fun(int a) {
	a ^= (1 << 5) - 1;
	//00100000
	//00011111
	//00010101
	//00001010
	return a;
}
int main() {
	printf("%d\n", fun(21));
	//10101
	return 0;
}
#endif


#if 0
int main() {
	unsigned char i = 7;
	int j = 0;
	//7 4 1 -2
	//-2
	//10000000000000000000000000000010
	//11111111111111111111111111111101
	//11111111111111111111111111111110
	//11111110
	//254
	//7 4 1 254 251 248 ... 5 2 255 252 249....6 3 0
	//3+85+85
	for (; i > 0; i -= 3) {
		j++;
	}
	printf("%d\n", j);
	return 0;
}
#endif

#if 0
int fib(m) {
	if (m <= 2) {
		return 1;
	}
	else {
		return fib(m - 1) + fib(m - 2);
	}
}
void find_steps(int x) {
	int i = 0;
	for (i = 0;; i++) {
		if (fib(i) <= x && fib(i + 1) >= x) {
			break;
		}
	}
	printf("%d\n", (x - fib(i)) < (fib(i + 1) - x) ? (x - fib(i)) : (fib(i + 1) - x));
}
int main() {
	int n = 0;
	scanf("%d", &n);//输入一个数字
	find_steps(n);
	return 0;
}
#endif



#include <string.h>
#if 0
//Happy new year
//Happy%20new%20year
void _move_for_twice(char* p) {//挪动字符串
	int len = strlen(p);
	char* start = p + len - 1;
	while (start >= p) {
		*(start + 2) = *start;
		start--;
	}
}
void replaceSpace(char* str, int length) {
	char* start = str;
	int len = strlen(str);
	char* end = str + len - 1;
	while (start < end) {
		if (*start == ' ') {
			_move_for_twice(start);//让字符串往后挪两个位置
			end += 2;
			*start++ = '%';
			*start++ = '2';
			*start = '0';
			start -= 3;
		}
		start++;
	}
}
int main() {
	char arr[20] = "   ";
	replaceSpace(arr, 20);
	printf("%s\n", arr);
	return 0;
}
#endif

//题解
#if 0
void replaceSpace(char* str, int length) {
	int spacecnt = 0;
	char* p = str;
	while (*p) {
		if (*p == ' ') {
			spacecnt++;
		}
		p++;
	}
	int newlen = length + 2 * spacecnt;
	int end1 = length - 1;
	int end2 = newlen - 1;
	while (end1 != end2) {
		if (str[end1] != ' ') {
			str[end2--] = str[end1--];
		}
		else {
			str[end2--] = '0';
			str[end2--] = '2';
			str[end2--] = '%';
			end1--;
		}
	}
}
#endif


//全局变量不要放在头文件里面去定义
//否则容易产生重定义的问题