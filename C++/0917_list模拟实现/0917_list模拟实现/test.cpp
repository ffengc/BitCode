#define _CRT_SECURE_NO_WARNINGS 1

//总结：适配器的特点就是 -- 复用！！！

#include"MyList.h"

#if 0
// 正向打印链表
template < class T>
void PrintList(const yufc::list<T>&l)
{
	auto it = l.cbegin();
	while (it != l.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
// 测试List的构造
void TestList1()
{
	yufc::list<int> l1;
	yufc::list<int> l2(10, 5);
	PrintList(l2);
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	yufc::list<int> l3(array, array + sizeof(array) / sizeof(array[0]));
	PrintList(l3);
	yufc::list<int> l4(l3);
	PrintList(l4);
	l1 = l4;
	PrintList(l1);
	PrintListReverse(l1);
}
// PushBack()/PopBack()/PushFront()/PopFront()
void TestList2()
{
	// 测试PushBack与PopBack
	yufc::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	PrintList(l);
	l.pop_back();
	l.pop_back();
	PrintList(l);
	l.pop_back();
	cout << l.size() << endl;
	// 测试PushFront与PopFront
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);
	PrintList(l);
	l.pop_front();
	l.pop_front();
	PrintList(l);
	l.pop_front();
	cout << l.size() << endl;
}
void TestList3()
{
	int array[] = { 1, 2, 3, 4, 5 };
	bite::list<int> l(array, array + sizeof(array) / sizeof(array[0]));
	auto pos = l.begin();
	l.insert(l.begin(), 0);
	PrintList(l);

	++pos;
	l.insert(pos, 2);
	PrintList(l);
	l.erase(l.begin());
	l.erase(pos);
	PrintList(l);
	// pos指向的节点已经被删除，pos迭代器失效
	cout << *pos << endl;
	auto it = l.begin();
	while (it != l.end())
	{
		it = l.erase(it);
	}
	cout << l.size() << endl;
}
#endif


#if 0
int main() {
	//yufc::test();
	//yufc::test2();
	//yufc::test3();
	//yufc::test4();
	yufc::test5();
	return 0;
}
#endif



//forward_iterator
//bidirectional_iterator
//random_access_iterator
//其实它们是一种继承的关系
//双向是特殊的单向，随机是特殊的双向

//源码其实比我们写的版本还复杂得多
//很多版本控制
//迭代器萃取那些也可以了解一下
//萃取 -- 可以提高效率
//比如迭代器要相减
//萃取技术（很复杂的一个技术）可以萃取出迭代器的类型
//比如：如果是随机迭代器类型就直接相减，如果是双向迭代器就要不断++算距离
//萃取就提高了效率