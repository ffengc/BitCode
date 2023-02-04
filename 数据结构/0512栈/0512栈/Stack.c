#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void _StackInit(Stack* ps) {
	assert(ps);
	ps->a = NULL;
	ps->top = 0;
	ps->capacity = 0;
}
void _StackDestroy(Stack* ps) {
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}
void _StackPush(Stack* ps, STDataType x) {
	assert(ps);
	if (ps->capacity == ps->top) {
		int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * newCapacity);
		if (tmp == NULL) {
			perror(" ");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newCapacity;
	}

	ps->a[ps->top++] = x;
}
void _StackPop(Stack* ps) {
	assert(ps);
	assert(!_StackEmpty(ps));
	ps->top--;
}
STDataType _StackTop(Stack* ps) {
	assert(ps);
	assert(!_StackEmpty(ps));
	return ps->a[ps->top - 1];
}
bool _StackEmpty(Stack* ps) {
	assert(ps);
	return ps->top == 0;
}
int _StackSize(Stack* ps) {
	assert(ps);
	return ps->top;
}