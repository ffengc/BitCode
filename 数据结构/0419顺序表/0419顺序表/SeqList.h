#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


//动态顺序表
typedef int SLDdataType;
typedef struct SeqList {
	SLDdataType* a;
	size_t size;//数据个数
	size_t capacity;//容量
}SL;


void _SeqListInit(SL* ps);//初始化
void _SeqListPrint(SL* ps);
void _SeqList_checkCapacity(SL* ps);
void _SeqListPushBack(SL* ps, SLDdataType x);//尾插
void _SeqListPopBack(SL* ps);//尾删
void _SeqListPushFront(SL* ps, SLDdataType x);//头插
void _SeqListPopFront(SL* ps);//头删
void _SeqListDestroy(SL* ps);
void _SeqListInsert(SL* ps, int pos, SLDdataType x);
void _SeqListErase(SL* ps, int pos);
int _SeqListFind(SL* ps, SLDdataType x);
void _SeqListModify(SL* ps, int pos, SLDdataType x);