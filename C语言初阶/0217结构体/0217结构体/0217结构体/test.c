#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>


//结构体
#if 0
struct tag {
	//menber-list
	int _data;
}variable_list;


struct Stu {
	char name[20];
	int age;//年龄
	char sex[8];
	float score;
}s1,s2,s2;

int main() {


	return 0;
}
#endif


#if 0
typedef struct Stu {
	char name[20];
	int age;
	char sex[8];
	float score;
}Stu;
int main() {
	Stu s1;
	s1.age = 10;


	return 0;
}
#endif



struct Point {
	int x;
	int y;
}p1 = { 10,15 };
struct S {
	char c;
	struct Point sp;
	double d;
	char arr[20];
};
outputStruct_s(struct S* ps) {
	printf("%c {%d,%d} %.2f %s\n", ps->c, ps->sp.x, ps->sp.y, ps->d, ps->arr);
}
int main() {
	struct Point p = { 100,200 };
	struct S ss = { 'w',{100,200},5.5,"hello" };
	outputStruct_s(&ss);
	return 0;
}