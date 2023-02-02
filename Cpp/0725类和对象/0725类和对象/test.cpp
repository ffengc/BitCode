#define _CRT_SECURE_NO_WARNINGS 1

#include"Date.h"


void TestDate1() {
	Date d1(2022, 11, 1);
	d1 -= 100;
	d1.Print();
	Date d2 = d1 - 100;
	d2.Print();
}
void TestDate2() {
	Date d1(2022, 7, 25);
	Date d2(2023, 2, 15);
	//swap(d1, d2);
	cout << (d2 - d1) << endl;
}
void TestDate3() {
	Date d1(2022, 2, 29);
}
void TestDateIO() {
	Date d1(2022, 2, 10);
	Date d2(2022, 2, 13);
#if 0
	d1.operator<<(cout);//这样可以成功调用，那为什么cout<<d1不行呢？
	//因为d1应该是左操作数，cout应该是右操作数！ -- 因为this抢占了第一个参数
	d1 << cout;//这样就可以跑起来了
	//那怎么解决这个问题，我们不能让this抢占第一个参数的位置，我们要改变一下
	//所以我们的<<重载函数不能写成成员函数了，写到外面去，我们就能改变this的位置了（当然，在外面的话没有this了）
#endif
	//把函数放到类外面之后，调整一下参数顺序，然后用一下友元
	cout << d1 << d2 << endl;
	cin >> d1;
	cout << d1 << endl;
}
int main() {
	//TestDate1();
	//TestDate2();
	//TestDate3();
	TestDateIO();
	return 0;
}

//写到这里，我不再想用d1.Print()的Print()了，我想直接用<<,>>!