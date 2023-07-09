#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cassert>
using namespace std;

//insert
void test_string1() {
	string str("wo lai le");
	//每个空格的位置插入一个%
	//可以用insert，但是效率低，不建议用
	//需要用的插入一下文档就行
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			str.insert(i, "%20");//这样是死循环的，因为i的意义变了，就一直插入了
			i += 3;
		}
	}
	cout << str << endl;

	//空格改成%20
	//把空格erase掉
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			str.erase(i, 1);
		}
	}
	cout << str << endl;


	//也可以用.replace() -- 替换
	//不会的时候直接查文档就行了
}

//c_str 兼容C
void test_string2() {
	string filename("hello world");
	//用C去读文件

	FILE* pf = fopen(filename.c_str(), "r");
	assert(pf);

	//这两者的意义不是一样的
	cout << filename << endl;
	cout << filename.c_str() << endl;
}

void test_string3() {
	string filename("hello world");
	cout << filename << endl;
	cout << filename.c_str() << endl;

	filename += '\0';
	filename += "Hello Linux";
	cout << filename << endl;//string对象以size为准
	cout << filename.c_str() << endl;//以\0为准
}

//find系列
void test_string4() {
#if 0
	string filename("test.cpp");
	//找后缀
	size_t pos = filename.find('.');
	if (pos != string::npos) {//npos是静态的 -- 所以string::npos这样取
		string suff = filename.substr(pos,filename.size() - pos);
		//第二个参数不写也行，反正找到结束 -- 最大就是npos
		cout << suff << endl;
	}
#endif
	//此时的问题是
	//在Linux下经常有这种文件名
	//test.bak.cpp.txt
	//我们要取真的后缀怎么办？（虽然后缀在Linux下不是决定文件类型的东西）
	//rfind
	string filename("test.cpp.bak.txt");
	//找后缀
	size_t pos = filename.rfind('.');//从尾开始找，倒着找
	if (pos != string::npos) {//npos是静态的 -- 所以string::npos这样取
		string suff = filename.substr(pos, filename.size() - pos);
		//第二个参数不写也行，反正找到结束 -- 最大就是npos
		cout << suff << endl;
	}
}

//find的其它用法
void Deal(string url) {
	size_t pos1 = url.find("://");
	if (pos1 == string::npos) {
		cout << "非法url" << endl;
		exit(-1);
	}
	//取协议
	string protocol = url.substr(0, pos1);
	cout << protocol << endl;
	//取域名
	size_t pos2 = url.find("/", pos1 + 3);//从pos1+3的位置开始找
	if (pos2 == string::npos) {
		cout << "非法url" << endl;
		exit(-1);
	}
	string domain = url.substr(pos1 + 3, pos2 - pos1 - 3);
	cout << domain << endl;
	//取其它
	string uri = url.substr(pos2 + 1);
	cout << uri << endl;
}
void test_string5() {
	string url1 = "https://cplusplus.com/string/string";
	string url2 = "https://leetcode.cn/problemset/all/";
	//所有网址的三部分
	//1.协议
	//2.域名
	//3.其余动作请求
	//现在想要切割成三部分
	Deal(url1);
}

void test_string6() {
	//整型转字符串
	int ival = 10;
	double dval = 10.11;
	string istr = to_string(ival);
	string dstr = to_string(dval);
	cout << istr << endl;
	cout << dstr << endl;
	//字符串转数字
	istr = "9999";
	dstr = "9999.99";
	ival = stoi(istr);
	dval = stod(dstr);
	cout << ival << " " << dval << endl;
	//其它的查文档就行 -- 不用记住
}
int main() {
	//test_string1();
	//test_string2();
	//test_string3();
	//test_string4();
	//test_string5();
	test_string6();
	return 0;
}