#pragma once


#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int QDataType;
typedef struct QueueNode {
	struct QueueNode* next;
	QDataType data;
}QNode;

typedef struct Queue {
	QNode* head;
	QNode* tail;
}Queue;

void _QueueInit(Queue* pq);
void _QueueDestroy(Queue* pq);
void _QueuePush(Queue* pq, QDataType x);
void _QueuePop(Queue* pq);
QDataType _QueueFront(Queue* pq);
QDataType _QueueBack(Queue* pq);
bool _QueueEmpty(Queue* pq);
int _QueueSize(Queue* pq);