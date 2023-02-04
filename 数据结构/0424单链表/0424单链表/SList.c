#define _CRT_SECURE_NO_WARNINGS 1
#include"SList.h"

//二级指针可以断言，一级不能断言
//一级指针完全是可以为空的
//但是二级指针为空只能是错误

SListNode* _CreatListNode(SLTDataType x) {
	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
	assert(newNode);
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}

void _SListPrint(SListNode* phead) {
	SListNode* cur = phead;
	while (cur) {
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void _SListPushBack(SListNode** pphead, SLTDataType x) {
	assert(pphead);
	SListNode* newNode = _CreatListNode(x);
	//空链表的情况
	if (*pphead == NULL) {
		*pphead = newNode;
	}
	else {
		//找尾
		SListNode* tail = *pphead;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = newNode;
	}
}

void _SListPushFront(SListNode** pphead, SLTDataType x) {
	assert(pphead);
	SListNode* newNode = _CreatListNode(x);
	newNode->next = *pphead;
	*pphead = newNode;
}

void _SListPopBack(SListNode** pphead) {
	assert(pphead);
	assert(*pphead);//没有节点不用删
	if ((*pphead)->next == NULL) {//只有一个节点
		free(*pphead);
		*pphead = NULL;
	}
	else {//多个节点
		SListNode* tailPrev = NULL;//要保存前一个节点
		SListNode* tail = *pphead;
		while (tail->next != NULL) {
			tailPrev = tail;
			tail = tail->next;
		}
		free(tail);
		tailPrev->next = NULL;
	}
}

void _SListPopFront(SListNode** pphead) {
	assert(pphead);
	assert(*pphead);
	//要先保存下一个节点，否则free了就找不到了
	SListNode* next = (*pphead)->next;
	free(*pphead);
	*pphead = next;
}


//查找的附带作用就是修改
SListNode* _SListFind(SListNode* phead, SLTDataType x) {
	//查找不需要二级指针
	SListNode* cur = phead;
	while (cur) {
		if (cur->data == x) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}



void _SListInsert(SListNode** pphead, SListNode* pos, SLTDataType x) {
	assert(pos);
	assert(pphead);
	//头插
	if (pos == *pphead) {
		_SListPushFront(pphead, x);
	}
	else {
		SListNode* prev = *pphead;
		while (prev->next != pos) {
			prev = prev->next;
		}
		SListNode* newNode = _CreatListNode(x);
		prev->next = newNode;
		newNode->next = pos;
	}
}
void _SListErase(SListNode** pphead, SListNode* pos) {
	//删除某个位置的数据还是要知道前一个节点
	assert(pphead);
	assert(pos);
	if (*pphead == pos) {
		_SListPopFront(pphead);
	}
	else {
		//找到前一个
		SListNode* prev = *pphead;
		while (prev->next != pos) {
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
	}
}