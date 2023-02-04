#define _CRT_SECURE_NO_WARNINGS 1

#include"List.h"
//如果想快速写出一个链表
//先写insert和erase

ListNode* _ListInit() {
	ListNode* phead = NULL;
	phead = _CreatListNode(-1);
	phead->next = phead;
	phead->prev = phead;
	return phead;
}


ListNode* _CreatListNode(LTDataType x) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) {
		perror("_CreatListNode::malloc_fail");
		exit(-1);
	}
	node->data = x;
	node->next = NULL;
	node->prev = NULL;
	return node;
}


void _ListPushBack(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* newNode = _CreatListNode(x);
	ListNode* tail = phead->prev;
	tail->next = newNode;
	newNode->prev = tail;
	newNode->next = phead;
	phead->prev = newNode;
}

void _ListPrint(ListNode* phead) {
	assert(phead);
	//不能打印空
	//注意循环的结束
	ListNode* cur = phead->next;
	while (cur != phead) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}


void _ListPushFront(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* newnode = _CreatListNode(x);
	ListNode* next = phead->next;
	phead->next = newnode;
	newnode->prev = phead;
	newnode->next = next;
	next->prev = newnode;
}

void _ListPopBack(ListNode* phead) {
	assert(phead);
	assert(!_ListEmpty(phead));//验空
	ListNode* tail = phead->prev;
	ListNode* tailPrev = tail->prev;
	free(tail);
	tailPrev->next = phead;
	phead->prev = tailPrev;
	//链表为空的情况要判断
}

void _ListPopFront(ListNode* phead) {
	assert(phead);
	assert(!_ListEmpty(phead));//验空
	//同样，非常简单，phead-first-second 把first free掉就可以了
	ListNode* first = phead->next;
	ListNode* second = first->next;
	phead->next = second;
	second->prev = phead;
	free(first);
	first = NULL;
}

bool _ListEmpty(ListNode* phead) {
	assert(phead);
	return phead->next == phead;
}

void _ListInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* prev = pos->prev;
	ListNode* newnode = _CreatListNode(x);
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}//头插尾插可以复用，pos给head就是尾插，给head->next就是头插


void _ListErase(ListNode* pos) {
	assert(pos);
	ListNode* prev = pos->prev;
	ListNode* next = pos->next;

	prev->next = next;
	next->prev = prev;
	free(pos);
}//头删尾删可以复用


void _ListSize(ListNode* phead) {//但是这是一个O(n)的接口
	assert(phead);
	ListNode* cur = phead;
	int size = 0;
	while (cur != phead) {
		++size;
		cur = cur->next;//简单的迭代问题
	}
	return size;
}
//有一种方法是在头节点的data里面存
//但是这样是错误的！
//因为链表里面存的不是int


void _ListDestroy(ListNode* phead) {
	assert(phead);
	ListNode* cur = phead->next;
	while (cur != phead) {
		ListNode* next = cur->next;
		_ListErase(cur);
		cur = next;
	}
	free(phead);
}