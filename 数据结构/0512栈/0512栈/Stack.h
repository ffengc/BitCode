#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<memory.h>
#include<assert.h>

typedef int STDataType;
typedef struct Stack {
	STDataType* a;
	int top;
	int capacity;
}Stack;

void _StackInit(Stack* ps);
void _StackDestroy(Stack* ps);
void _StackPush(Stack* ps,STDataType x);
void _StackPop(Stack* ps);
STDataType _StackTop(Stack* ps);
bool _StackEmpty(Stack* ps);
int _StackSize(Stack* ps);