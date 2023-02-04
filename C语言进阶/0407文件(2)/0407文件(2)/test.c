#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>



//文件的随机读写
#if 0
int main() {
	//打开文件
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL) {
		perror("fopen");
		exit(-1);
	}
	//随机读取
#if 0
	int ch = 0;
	ch = fgetc(pf);
	printf("%c\n", ch);
#endif
	//想跳过并往后读取，我们就要调整文件指针的位置
	//fseek
	//原型
	//int fseek(FILE*stream,long offset,int origin);
	// SEEK_CUR-文件指针当前的位置
	// SEEK_END-文件末尾的位置
	// SEEK_SET-文件开始的位置
	int ch = 0;
	ch = fgetc(pf);
	printf("%c\n", ch);

	ch = fgetc(pf);
	printf("%c\n", ch);

	fseek(pf, 2, SEEK_CUR);

	ch = fgetc(pf);
	printf("%c\n", ch);

	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif

#if 0
int main() {
	//打开文件
	FILE* pf = fopen("test.txt", "w");
	if (pf == NULL) {
		perror("fopen");
		exit(-1);
	}
	//随机读取

	fputc('a', pf);
	fputc('b', pf);
	fputc('c', pf);
	fputc('d', pf);
	fseek(pf, -3, SEEK_CUR);
	fputc('w', pf);
	//awcd

	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif

//ftell返回文件指针相对于起始位置的偏移量
//rewind让文件指针的位置返回到起始位置
#if 0
int main() {
	//打开文件
	FILE* pf = fopen("test.txt", "w");
	if (pf == NULL) {
		perror("fopen");
		exit(-1);
	}
	//随机读取

	fputc('a', pf);
	fputc('b', pf);
	fputc('c', pf);
	fputc('d', pf);
	fseek(pf, -3, SEEK_CUR);
	fputc('w', pf);
	//awcd

	long pos = ftell(pf);
	printf("%d\n", pos);

	rewind(pf);
	pos = ftell(pf);
	printf("%d\n", pos);


	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif


//文本文件和二进制文件
#if 0
int main() {
	int a = 10000;
	FILE* pf = fopen("test3.txt", "wb");
	if (pf == NULL) {
		perror("fopen");
		return 1;
	}
	fwrite(&a, 4, 1, pf);
	fclose(pf);
	pf = NULL;
	//用二进制编译器打开test3.txt
	//10 27 00 00
	return 0;
}
#endif




//文件读取结束的判定
//被错误使用的feof
/*
* 牢记：再文件读取过程中，不能用feof函数的返回值直接用来判断文件是否读取结束
* 而是用于文件读取结束之后，判断是读取失败结束，还是遇到文件尾结束
*/
//
/*
* 1. 文本文件读取是否结束，判断返回值是否为 EOF （ fgetc ），或者 NULL （ fgets ）
例如：
fgetc 判断是否为 EOF .
fgets 判断返回值是否为 NULL .
2. 二进制文件的读取结束判断，判断返回值是否小于实际要读的个数。
例如：
fread判断返回值是否小于实际要读的个数。
*/
#include<stdlib.h>
#if 0
int main(){
	int c; // 注意：int，非char，要求处理EOF
	FILE* fp = fopen("test.txt", "r");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	//fgetc 当读取失败的时候或者遇到文件结束的时候，都会返回EOF
	while ((c = fgetc(fp)) != EOF) // 标准C I/O读取文件循环
	{
		putchar(c);
	}
		//判断是什么原因结束的
		if (ferror(fp))
			puts("I/O error when reading");
		else if (feof(fp))
			puts("End of file reached successfully");
	fclose(fp);
}
#endif

#if 0
enum { SIZE = 5 };
int main(void)
{
	double a[SIZE] = { 1.,2.,3.,4.,5. };
	FILE* fp = fopen("test.bin", "wb"); // 必须用二进制模式
	fwrite(a, sizeof * a, SIZE, fp); // 写 double 的数组
	fclose(fp);
	double b[SIZE];
	fp = fopen("test.bin", "rb");
	size_t ret_code = fread(b, sizeof * b, SIZE, fp); // 读 double 的数组
	if (ret_code == SIZE) {
		puts("Array read successfully, contents: ");
		for (int n = 0; n < SIZE; ++n) printf("%f ", b[n]);
		putchar('\n');
	}
	else { // error handling
		if (feof(fp))
			printf("Error reading test.bin: unexpected end of file\n");
		else if (ferror(fp)) {
			perror("Error reading test.bin");
		}
	}
	fclose(fp);
}
#endif



//文件缓冲区
/*
ANSIC 标准采用“缓冲文件系统”处理的数据文件的，所谓缓冲文件系统是指系统自动地在内存中为程序
中每一个正在使用的文件开辟一块“文件缓冲区”。从内存向磁盘输出数据会先送到内存中的缓冲区，装
满缓冲区后才一起送到磁盘上。如果从磁盘向计算机读入数据，则从磁盘文件中读取数据输入到内存缓
冲区（充满缓冲区），然后再从缓冲区逐个地将数据送到程序数据区（程序变量等）。
缓冲区的大小根据C编译系统决定的。
*/

#include <windows.h>
//VS2013 WIN10环境测试
int main()
{
	FILE* pf = fopen("test.txt", "w");
	fputs("abcdef", pf);//先将代码放在输出缓冲区
	printf("睡眠10秒-已经写数据了，打开test.txt文件，发现文件没有内容\n");
	Sleep(10000);
	printf("刷新缓冲区\n");
	fflush(pf);//刷新缓冲区时，才将输出缓冲区的数据写到文件（磁盘）
	//注：fflush 在高版本的VS上不能使用了
	printf("再睡眠10秒-此时，再次打开test.txt文件，文件有内容了\n");
	Sleep(10000);
	fclose(pf);
	//注：fclose在关闭文件的时候，也会刷新缓冲区
	pf = NULL;
	return 0;
}
