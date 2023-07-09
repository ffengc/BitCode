#define _CRT_SECURE_NO_WARNINGS 1


#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include<list>
#include<stack>
#include<queue>
using namespace std;


#if 0
//0917
//list的特性及使用等
int main()
{
	int ar[] = { 0,1,2,3,4,5,6,7,8,9 };
	int n = sizeof(ar) / sizeof(int);
	list<int> mylist(ar, ar + n);
	list<int>::iterator pos = find(mylist.begin(), mylist.end(), 5);
	reverse(mylist.begin(), pos);
	//4 3 2 1 0 5 6 7 8 9
	reverse(pos, mylist.end());
	//4 3 2 1 0 9 8 7 6 5
	list<int>::const_reverse_iterator crit = mylist.crbegin();
	while (crit != mylist.crend())
	{
		cout << *crit << " ";
		++crit;
	}
	//5 6 7 8 9 0 1 2 3 4 
	cout << endl;
}



template<typename T>
void removeDuplicates(list<T>& aList)
{
	T curValue;
	list<T>::iterator cur, p;
	cur = aList.begin();
	while (cur != aList.end())
	{
		curValue = *cur;
		p = ++cur;
		//空白行 1
		while (p != aList.end())
		{
			if (*p == curValue)
			{
				//空白行 2
				p == cur ? cur = p = aList.erase(p) : p = aList.erase(p);
			}
			else
			{
				p++;
			}
		}
	}
}


//0924 list迭代器失效问题
int main()
{
	int array[] = { 1, 2, 3, 4, 0, 5, 6, 7, 8, 9 };
	int n = sizeof(array) / sizeof(int);
	list<int> mylist(array, array + n);
	//1 2 3 4 0 5 6 7 8 9
	auto it = mylist.begin(); 
	while (it != mylist.end())
	{
		if (*it != 0)
			cout << *it << " ";
		else
			it = mylist.erase(it);
		++it;
	}
	return 0;
}



void  main()
{
	stack<char> S;
	char x, y;
	x = 'n'; y = 'g';
	//n
	S.push(x); S.push('i'); S.push(y);
	S.pop(); S.push('r'); S.push('t'); S.push(x);
	S.pop(); S.push('s');
	while (!S.empty())
	{
		x = S.top();
		S.pop();
		cout << x;
	};
	cout << y;
}



int main()
{
	queue<char> Q;
	char x, y;
	x = 'n'; y = 'g';
	Q.push(x); Q.push('i'); Q.push(y);
	Q.pop(); Q.push('r'); Q.push('t'); Q.push(x);
	Q.pop(); Q.push('s');
	while (!Q.empty())
	{
		x = Q.front();
		Q.pop();
		cout << x;
	}
	cout << y;
	return 0;
}
#endif

//2022-09-24_stack和queue OJ题等_作业
int main()
{
	priority_queue<int> a;
	priority_queue<int, vector<int>, greater<int> > c; //greater代表小堆
	priority_queue<string> b;
	for (int i = 0; i < 5; i++)
	{
		a.push(i);
		c.push(i);
	}
	while (!a.empty())
	{
		cout << a.top() << ' ';
		//5 4 3 2 1
		a.pop();
	}
	cout << endl;
	while (!c.empty())
	{
		cout << c.top() << ' ';
		//1 2 3 4 5
		c.pop();
	}
	cout << endl;
	b.push("abc");
	b.push("abcd");
	b.push("cbd");
	while (!b.empty())
	{
		cout << b.top() << ' ';
		//cbd abcd abc
		b.pop();
	}
	cout << endl;
	return 0;
}