#define _CRT_SECURE_NO_WARNINGS 1

#include"SeqList.h"

void _SeqListInit(SL* ps) {
	assert(ps);
	ps->a = NULL;
	ps->capacity = ps->size = 0;
}

void _SeqList_checkCapacity(SL* ps) {
	assert(ps);
	if (ps->size == ps->capacity) {
		int _newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		SLDdataType* tmp = (SLDdataType*)realloc(ps->a, _newCapacity * sizeof(SLDdataType));
		if (tmp == NULL) {
			perror("_SeqList_checkCapacity::realloc");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = _newCapacity;
	}
}

void _SeqListPrint(SL* ps) {
	assert(ps);
	for (int i = 0; i < ps->size; i++) {
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

void _SeqListPushBack(SL* ps, SLDdataType x) {
	assert(ps);
	//扩容
	_SeqList_checkCapacity(ps);
	ps->a[ps->size] = x;
	ps->size++;
}

void _SeqListPushFront(SL* ps, SLDdataType x) {
	assert(ps);
	//增容
	_SeqList_checkCapacity(ps);
	//挪动数据
	int end = ps->size - 1;
	while (end >= 0) {
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	ps->a[0] = x;
	ps->size++;
}

void _SeqListPopBack(SL* ps) {
	assert(ps);
	//尾删
	/*if (ps->size == 0) {
		printf("Empty List! err!\n");
	}*/
	//或
	assert(ps->size > 0);
	ps->size--;
}

void _SeqListPopFront(SL* ps) {
	assert(ps);
	assert(ps->size > 0);
	int begin = 1;
	while (begin < ps->size) {
		ps->a[begin - 1] = ps->a[begin];
		++begin;
	}
	ps->size--;
}

void _SeqListDestroy(SL* ps) {
	assert(ps);
	if (ps->a) {
		free(ps->a);
		ps->a = NULL;
		ps->capacity = ps->size = 0;
	}
}

void _SeqListInsert(SL* ps, int pos, SLDdataType x) {
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);
	_SeqList_checkCapacity(ps);
	int end = ps->size - 1;
	while (end >= pos) {
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[pos] = x;
	ps->size++;
}
//有了这个之后，我们要尾插头插都可以复用了

void _SeqListErase(SL* ps, int pos) {
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	int begin = pos;
	while (begin < ps->size - 1) {
		ps->a[begin] = ps->a[begin + 1];
		++begin;
	}
	ps->size--;
}

int _SeqListFind(SL* ps, SLDdataType x) {
	assert(ps);
	for (int i = 0; i < ps->size; i++) {
		if (ps->a[i] == x) {
			return i;//找到了
		}
	}
	return -1;//找不到
}


void _SeqListModify(SL* ps, int pos, SLDdataType x) {
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	ps->a[pos] = x;
}