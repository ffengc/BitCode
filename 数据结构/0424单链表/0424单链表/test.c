#define _CRT_SECURE_NO_WARNINGS 1


#include"SList.h"

void _TestSList1() {
	SListNode* plist = NULL;
	_SListPushBack(&plist, 1);
	_SListPushBack(&plist, 2);	
	_SListPushBack(&plist, 3);
	_SListPushBack(&plist, 4);
	_SListPushBack(&plist, 5);
	_SListPrint(plist);

	_SListPushFront(&plist, 0);
	_SListPushFront(&plist, -1);
	_SListPushFront(&plist, -2);
	_SListPrint(plist);

	_SListPopFront(&plist);
	_SListPopFront(&plist);
	_SListPrint(plist);

	_SListPopBack(&plist);
	_SListPopBack(&plist);
	_SListPopBack(&plist);
	_SListPopBack(&plist);
	_SListPopBack(&plist);
	_SListPopBack(&plist);
	_SListPrint(plist);

}
void _TestSList2() {
	SListNode* plist = NULL;
	_SListPushBack(&plist, 1);
	_SListPushBack(&plist, 2);
	_SListPushBack(&plist, 3);
	_SListPushBack(&plist, 4);
	_SListPushBack(&plist, 5);
	_SListPrint(plist);

	SListNode* ret = _SListFind(plist, 3);
	if (ret) {
		printf("找到了\n");
		ret->data = 30;
	}
	_SListPrint(plist);

	/*SListNode* pos = _SListFind(plist, 4);
	if (pos) {
		_SListInsert(&plist, pos, 40);//在4之前插入一个40
	}
	_SListPrint(plist);*/

	SListNode* pos = _SListFind(plist, 5);
	if (pos) {
		_SListErase(&plist, pos);
	}
	_SListPrint(plist);
}
int main() {
	//_TestSList1();
	_TestSList2();
	return 0;
}