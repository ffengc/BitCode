#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

//string -- 动态增长的char字符数组

//string
//wstring
//u16string
//u32string

//其实这四种是编码的区别
//中文的编码常见的有两种系列 gbk utf-8
int main() {
	char a1[] = "hello";
	char a2[] = "比特";
	char a3[] = { -79,-56,-52,-40,0 };
	cout << a3 << endl;

	a3[3]++;
	cout << a3 << endl;

	a3[3]++;
	cout << a3 << endl;	

	a3[3]++;
	cout << a3 << endl;

	//其实是把同音字编到一起的

	//有什么好处呢？
	//净网
	//不要在网上发国粹
	//怎么办 -- 国粹的词库
	//如果在词库里面 -- 变成****
	//同音字怎么办 -- 这种编码就很方便了
	return 0;
}