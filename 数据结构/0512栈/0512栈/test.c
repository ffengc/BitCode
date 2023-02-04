#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

//数组还是链表
//尾插尾删效率很高，所以用数组好

void Test1() {
	Stack st;
	_StackInit(&st);
	_StackPush(&st, 1);
	_StackPush(&st, 2);
	_StackPush(&st, 3);
	_StackPush(&st, 4);
	_StackPush(&st, 5);
	while (!_StackEmpty(&st)) {
		printf("%d ", _StackTop(&st));
		_StackPop(&st);
	}
	_StackDestroy(&st);
}
int main() {
	Test1();
	return 0;
}