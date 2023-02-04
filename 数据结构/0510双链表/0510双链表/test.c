#define _CRT_SECURE_NO_WARNINGS 1

//链表为空的时候是要有一个节点的

//带头循环双向链表的对比
//顺序表：（vector）
//优点：支持下标随机访问、CPU高速缓存命中率高，高速加载的时候可以很好的命中-因为链表地址之间没有关系，所以基本上都命中不了
//缺点：头部或者中间的插入删除效率低、扩容（有一定程度性能的消耗-为什么-realloc的时候，
//如果位置够还好，如果位置不够，要开新空间，要拷贝数据，这个对效率是非常不友好的，非常非常费时间！）
//、可能存在空间浪费
//

//带头双向循环链表（list）
//优点：在任意位置插入删除O(1),按需申请释放
//缺点：不支持下标随机访问

#include"List.h"
void Test1() {
	ListNode* plist = _ListInit();
	_ListPushBack(plist, 1);
	_ListPushBack(plist, 2);
	_ListPushBack(plist, 3);
	_ListPushBack(plist, 4);
	_ListPushBack(plist, 5);
	_ListPrint(plist);

	_ListPushFront(plist, 0);
	_ListPushFront(plist, -1);
	_ListPrint(plist);

	_ListPopBack(plist);
	_ListPopBack(plist);
	_ListPopBack(plist);
	_ListPrint(plist);

	_ListPopFront(plist);
	_ListPopFront(plist);
	_ListPrint(plist);

}
int main() {
	Test1();
	return 0;
}