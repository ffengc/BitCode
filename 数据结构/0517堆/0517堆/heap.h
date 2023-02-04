#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

typedef int HPDataType;
typedef struct Heap {
	HPDataType* a;
	int size;
	int capacity;
}Heap;

//打印堆
void _HeapPrint(Heap* php);
//初始化堆
void _HeapInit(Heap* php);
//销毁堆
void _HeapDestroy(Heap* php);
//增加一个元
void _HeapPush(Heap* php, HPDataType x);
//删除一个元素
void _HeapPop(Heap* php);
//取堆顶元素
HPDataType _HeapTop(Heap* php);
//堆判空
bool _HeapEmpty(Heap* php);
//堆大小
int _HeapSize(Heap* php);
//向上调整算法
void _AdjustUp(HPDataType* a, int child);
//向下调整算法
void _AdjustDown(HPDataType* a, int size, int parent);