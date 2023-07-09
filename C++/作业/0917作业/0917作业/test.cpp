#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;

//1.程序会崩溃
int main()
{
	int ar[] = { 1,2,3,4,0,5,6,7,8,9 };
	int n = sizeof(ar) / sizeof(int);
	vector<int> v(ar, ar + n);//用迭代器区间构造
	vector<int>::iterator it = v.begin();
	//1 2 3 4 6 7 8 9 
	while (it != v.end())
	{
		if (*it != 0) {
			cout << *it;
		}
		else {
			v.erase(it);
		}
		it++;
	}
	return 0;
}
//此时针对一个已经失效的迭代器在进行++,会导致程序崩溃