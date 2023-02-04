#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>

//BC28 大小写转换
//格式
//输入：
//A
//B...
//输出
//a
//b...
int main() {
	int ch = 0;
	while ((ch = getchar()) != EOF) {
		if (ch >= 'A' && ch <= 'Z') {
			ch += 32;
		}
		printf("%c\n", ch);
		getchar();//去除输入时的\n，涉及到缓冲区的概念
	}
	return 0;
}