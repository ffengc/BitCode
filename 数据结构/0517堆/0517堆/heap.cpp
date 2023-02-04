#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

void _HeapInit(Heap* php) {
	assert(php);
	php->a = nullptr;
	php->size = php->capacity = 0;
}
void _HeapDestroy(Heap* php) {
	assert(php);
	free(php->a);
	php->a = nullptr;
	php->size = php->capacity = 0;
}
//向上调整算法
void _AdjustUp(HPDataType* a, int child) {
	int parent = (child - 1) / 2;
	//这个循环条件的终止条件要注意
	while (child > 0) {
		if (a[child] < a[parent]) {
			swap(a[child], a[parent]);
			//把父亲的下标给孩子
			child = parent;
			parent = (child - 1) / 2;
		}
		//此时直接break
		else {
			break;
		}
	}
}
void _HeapPush(Heap* php, HPDataType x) {
	assert(php);
	//扩容
	if (php->size == php->capacity) {
		int _newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(php->a, _newCapacity * sizeof(HPDataType));
		if (tmp == nullptr) {
			perror("_HeapPush::realloc");
			exit(-1);
		}
		php->a = tmp;
		php->capacity = _newCapacity;
	}
	php->a[php->size] = x;
	php->size++;
	//向上调整算法
	_AdjustUp(php->a, php->size - 1);
}
//删除堆顶的数据，继续保持删除后依然是小堆
//思路：和最后一个交换，--size
//再写一个向下调整算法

void _HeapPrint(Heap* php) {
	assert(php);
	for (int i = 0; i < php->size; i++) {
		cout<<php->a[i]<<" ";
	}
	cout << endl;
}
void _HeapPop(Heap* php) {
	//1.把头和尾交换一下
	//2.向下调整
	assert(php);
	assert(php->size > 0);
	swap(php->a[0], php->a[php->size - 1]);
	php->size--;
	//向下调整算法
	_AdjustDown(php->a, php->size, 0);
}
HPDataType _HeapTop(Heap* php) {
	assert(php);
	assert(php->size > 0);
	return php->a[0];
}
bool _HeapEmpty(Heap* php) {
	assert(php);
	return php->size == 0;
}
int _HeapSize(Heap* php) {
	assert(php);
	return php->size;
}
//向下调整算法
void _AdjustDown(HPDataType* a, int size, int parent) {
	int child = parent * 2 + 1;
	while (child < size) {
		//选出小的那个孩子节点
		if (child + 1 < size && a[child + 1] < a[child]) {
			++child;
		}
		if (a[child] < a[parent]) {
			//向下调整
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			//无需调整
			break;
		}
	}
}


