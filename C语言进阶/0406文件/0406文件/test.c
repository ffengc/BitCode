#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//本章重点
/*
* 1.为什么使用文件
* 2.什么是文件
* 3.文件的打开和关闭
* 4.文件的顺序读写
* 5.文件的随机读写
* 6.文本文件和二进制文件
* 7.文件读取结束的判定
* 8.文件缓冲区
*/


//文件一般有两种：程序文件、数据文件
/*
* 程序文件：
* 源程序文件(后缀为.c)，目标文件(windows环境后缀为.obj)，可执行程序(window环境后缀为.exe)
*/
/*
* 数据文件：
* 文件的内容不一定是程序，而是程序运行时读写的数据，比如程序运行需要从中读取数据的文件，或者输出内容的文件
*/


//文件的打开和关闭
#if 0
int main() {
	//写绝对路径的时候，\记得要多写一个
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL) {
		perror("fopen");
		exit(-1);
	}
	//读文件
	///...

	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;;
}
#endif


///写文件
#if 0
int main() {
	FILE* pf = fopen("test.txt","w");
	if (pf == NULL) {
		perror("fopen");
		return 1;
	}
#if 0
	fputc('a', pf);
	fputc('b', pf);
	fputc('c', pf);
	fputc('d', pf);
	fputc('e', pf);
	fputc('f', pf);
	fputc('g', pf);
	fputc('h', pf);
	fputc('i', pf);
	fputc('j', pf);
#endif
	char ch = 'a';
	/// 这个是按照一定的顺序写的
	for (ch = 'a'; ch <= 'z'; ch++) {
		fputc(ch, pf);
	}
	fclose(pf);
	return 0;
}
#endif



//读文件
#if 0
int main() {
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL) {
		perror("fopen");
		exit(-1);
	}
	//读文件
	int ch = 0;
	while ((ch = fgetc(pf))!= EOF) {
		printf("%c\n", ch);
	}
	printf("\n");
	fclose(pf);
	return 0;
}
#endif





///流
///
/// 文件流
/// 标准输入流 stdin
/// 标准输入流 stdout
/// 标准错误流 stderr
/// 三个流的类型都是FILE*
/// 只要c程序跑起来，上面三个流就是默认打开的
#if 0
int main() {
	//stream
	int ch = fgetc(stdin);
	printf("%c\n", ch);
	fputc(ch, stdout);
	return 0;
}
#endif


#if 0
int main() {
	FILE* pf = fopen("test.txt", "w");
	if (pf == NULL) {
		exit(-1);
	}
	//写文件
	//fputs,fgets
	//以写的形式打开，里面原来的就没了
	fputs("qwertyuiop",pf);
	fputs("xxxxxxxxxx", pf);
	//两个字符串是不会换行的
	// //后面加上\n就有换行了

	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif


#if 0
int main() {
	FILE* pf = fopen("test.txt", "r");
	if (pf == NULL) {
		exit(-1);
	}
	//读文件-读一行
	char arr[256] = { 0 };
	//fgets(arr, 255, pf);
	//printf("%s", arr);
	//fgets(arr, 255, pf);
	//printf("%s", arr);

	fgets(arr, 4, pf);//其实这里只读三个字符，留一个给\0了
	printf("%s", arr);
	//其实fgets的返回值是有讲究的，如果正常读，会返回string的地址
	//如果发生错误，就会返回空指针
	//所以如果我们不知道到底有几行的时候怎么读？
	while (fgets(arr, 256, pf) != NULL) {
		printf("%s", arr);
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif

//fprintf
#if 0
struct S {
	char name[20];
	int age;
	double d;
};
int main() {
	struct S s = { "张三",20,5.5 };
	//写到文件里
	FILE* pf = fopen("test2.txt", "w");
	if (pf == NULL) {
		exit(-1);
	}
	//写文件
	fprintf(pf, "%s %d %lf", s.name, s.age, s.d);
	//关闭文件
	fclose(pf);
	return 0;
}
#endif


//fscanf
#if 0
struct S {
	char name[20];
	int age;
	double d;
};
int main() {
	struct S s = { 0 };
	//写到文件里
	FILE* pf = fopen("test2.txt", "r");
	if (pf == NULL) {
		exit(-1);
	}
	//读文件
	fscanf(pf, "%s %d %lf", s.name, &(s.age), &(s.d));
	fprintf(stdout,"%s %d %lf", s.name, s.age, s.d);
	
	//关闭文件
	fclose(pf);
	return 0;
}
#endif

//scanf-格式化的输入函数
//printf-格式化的输出函数
//fscanf-针对所有输入流的格式化的输入函数
//fprintf-针对所有输出流的格式化的输出函数

//sprintf，sscanf
#if 0
struct S {
	char name[20];
	int age;
	double d;
};
int main() {
	struct S s = { "zhangsan",20,95.5 };
	struct S tmp = { 0 };
	char buf[256] = { 0 };
	sprintf(buf, "%s %d %lf", s.name, s.age, s.d);
	printf("%s\n", buf);
	//从buf里面提取结构体的数据
	sscanf(buf, "%s %d %lf", tmp.name, &(tmp.age), &(tmp.d));
	printf("%s %d %lf", tmp.name, tmp.age, tmp.d);
	return 0;
}
#endif
//sprintf-把一个格式化的数据转换成字符串
//sscanf-把一个字符串里面转化成格式化数据



//文件的二进制读写
//fread fwrite -只针对文件
//二进制写文件
#if 0
struct S {
	char name[20];
	int age;
	double d;
};
int main() {
	struct S s = { "张三",20,95.5 };
	FILE* pf = fopen("test3.txt", "wb");//二进制的方式写
	if (pf == NULL) {
		exit(-1);
	}
	//二进制的方式写
	fwrite(&s, sizeof(struct S), 1, pf);

	//
	fclose(pf);
	pf = NULL;

	return 0;
}
#endif

struct S {
	char name[20];
	int age;
	double d;
};
int main() {
	struct S s = { 0 };
	FILE* pf = fopen("test3.txt", "rb");//二进制的方式写
	if (pf == NULL) {
		exit(-1);
	}
	//二进制的方式读
	fread(&s, sizeof(struct S), 1, pf);
	printf("%s %d %lf", s.name, s.age, s.d);

	//
	fclose(pf);
	pf = NULL;

	return 0;
}
//怎么放进去怎么读出来