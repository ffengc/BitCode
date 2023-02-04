#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>


#if 0
int main() {
	int aa[2][5] = { 1,2,3,4,5,6,7,8,9,10 };
	//1 2 3 4 5
	//6 7 8 9 10
	int* ptr1 = (int*)(&aa + 1);
	int* ptr2 = (int*)(*(aa + 1));
	printf("%d %d", *(ptr1 - 1), *(ptr2 - 1));
	                     //10      5
	return 0;
}
#endif


#if 0
int main() {
	char* a[] = { "work","at","alibaba" };
	//&w &a &a
	char** pa = a;
	//pa->w的地址
	pa++;
	printf("%s\n", *pa);
	return 0;
}
#endif


//画图分析才行
int main() {
	char* c[] = { "ENTER","NEW","POINT","FIRST" };
	char** cp[] = { c + 3,c + 2,c + 1 };
	char*** cpp = cp;
	printf("%s\n", **++cpp);                         //POINT
	printf("%s\n", *-- * ++cpp + 3);                 //INT
	printf("%s\n", *cpp[-2] + 3);                    //ST
	printf("%s\n", cpp[-1][-1] + 1);                 //EW
	return 0;
}