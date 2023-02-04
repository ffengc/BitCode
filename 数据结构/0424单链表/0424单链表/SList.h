#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<memory.h>

typedef int SLTDataType;
typedef struct SListNode {
	SLTDataType data;
	struct SListNode* next;
}SListNode;

SListNode* _CreatListNode(SLTDataType x);
void _SListPrint(SListNode* phead);
void _SListPushBack(SListNode** pphead, SLTDataType x);
void _SListPushFront(SListNode** pphead, SLTDataType x);
void _SListPopBack(SListNode** pphead);
void _SListPopFront(SListNode** pphead);
SListNode* _SListFind(SListNode* phead, SLTDataType x);
//在pos之前插入，删除pos的值
void _SListInsert(SListNode** pphead, SListNode* pos, SLTDataType x);
void _SListErase(SListNode** pphead, SListNode* pos);