#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"
void _TestSeqList1() {
	SL _SList_1;
	//初始化
	_SeqListInit(&_SList_1);

	_SeqListPushBack(&_SList_1, 1);
	_SeqListPushBack(&_SList_1, 2);
	_SeqListPushBack(&_SList_1, 3);
	_SeqListPushBack(&_SList_1, 4);
	_SeqListPushBack(&_SList_1, 5);

	_SeqListPrint(&_SList_1);

	_SeqListPushFront(&_SList_1, 6);
	_SeqListPushFront(&_SList_1, 7);
	_SeqListPushFront(&_SList_1, 8);
	_SeqListPushFront(&_SList_1, 9);
	_SeqListPushFront(&_SList_1, 10);


	_SeqListPrint(&_SList_1);

}
void _TestSeqList2() {
	SL _SList_1;
	//初始化
	_SeqListInit(&_SList_1);

	_SeqListPushBack(&_SList_1, 1);
	_SeqListPushBack(&_SList_1, 2);
	_SeqListPushBack(&_SList_1, 3);
	_SeqListPushBack(&_SList_1, 4);
	_SeqListPushBack(&_SList_1, 5);
	_SeqListPrint(&_SList_1);

	_SeqListPopBack(&_SList_1);
	_SeqListPopFront(&_SList_1);
	_SeqListPrint(&_SList_1);

	_SeqListInsert(&_SList_1, 0, 100);
	_SeqListPrint(&_SList_1);
	_SeqListErase(&_SList_1, 1);
	_SeqListPrint(&_SList_1);

#if 0
	int x = 0;
	printf("请输入要删除的数字:");
	scanf("%d", &x);
	int pos = _SeqListFind(&_SList_1, 3);
	if (pos != -1) {
		_SeqListErase(&_SList_1, pos);
	}
#endif
	int x = 0;
	int y = 0;
	printf("请输入要被修改的数字和修改之后的数字:");
	scanf("%d %d", &x, &y);
	int pos = _SeqListFind(&_SList_1, 3);
	if (pos != -1) {
		_SeqListModify(&_SList_1, pos, y);
	}

	_SeqListDestroy(&_SList_1);
}
int main() {
	//_TestSeqList1();
	_TestSeqList2();
	return 0;
}