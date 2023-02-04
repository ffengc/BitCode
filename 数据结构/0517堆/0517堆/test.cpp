#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

void _TestHeapSort() {
	//升序打印-比较简单的-直接打印就行了-小堆
	Heap hp;
	_HeapInit(&hp);
	vector<int>a = { 27,15,19,18,28,34,65,49,25,37 };
	//插入
	for (int i = 0; i < a.size(); i++) {
		_HeapPush(&hp, a[i]);
	}
	
	while (!_HeapEmpty(&hp)) {
		cout << _HeapTop(&hp)<<" ";
		_HeapPop(&hp);
	}
	cout << endl;

	//如果要改大堆，只需要变的：向上调整、向下调整即可
	// 
	//如果要让数组的值有序呢
}



void _heapSort1(int* a, int size) {
	Heap hp;
	_HeapInit(&hp);
	for (int i = 0; i < size; i++) {
		_HeapPush(&hp, a[i]);
	}
	int i = 0;
	while (!_HeapEmpty(&hp)) {
		a[i++] = _HeapTop(&hp);
		_HeapPop(&hp);
	}
}
//创建一个堆

#if 0
int main() {
#if 0
	Heap hp;
	_HeapInit(&hp);
	vector<int>a = { 27,15,19,18,28,34,65,49,25,37 };
	//插入
	for (int i = 0; i < a.size(); i++) {
		_HeapPush(&hp, a[i]);
	}
	_HeapPrint(&hp);
	_HeapPush(&hp,10);
	_HeapPrint(&hp);
	
	_HeapPop(&hp);
	_HeapPrint(&hp);
	_HeapPop(&hp);
	_HeapPrint(&hp);
	_HeapPop(&hp);
	_HeapPrint(&hp);
#endif
	//_TestHeapSort();//有序打印
	int arr[] = { 27,15,19,18,28,34,65,49,25,37 };
	int size = sizeof(arr) / sizeof(arr[0]);
	_heapSort1(arr, size);//堆排序
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
#endif

//这样写的堆排序的问题
//1.要先写一个堆-太麻烦了
//2.有O(n)的空间复杂度
//真正的堆排序不用这么麻烦，见另外一个工程


//topk问题
//1.排序 O(nlogn)
//2.建N个数大堆，top/pop k次 O(N+logN*k)
//但是如果N非常大，比如N是100亿，K比较小，K是100，如何求解？

//K个数的小堆
//1.前k个数建立小堆
//2.剩下的N-K给依次和堆顶数据比较，如果比堆顶的数据大，就替换堆顶的数据进堆
//进完之后，堆里面的K个数，就是最大的前K个
//O(k+(n-k)logk))

#include<time.h>
void PrintTopK(int* a, int n, int k)
{
	// 1. 建堆--用a中前k个元素建堆
	int* kMinHeap = (int*)malloc(sizeof(sizeof(int) * k));
	assert(kMinHeap);
	for (int i = 0; i < k; i++) {
		kMinHeap[i] = a[i];
	}
	//建堆
	for (int i = (k - 1 - 1) / 2; i >= 0; i--) {
		_AdjustDown(kMinHeap, k, i);
	}
	// 2. 将剩余n-k个元素依次与堆顶元素交换，不满则则替换
	for (int j = k; j < n; ++j) {
		if (a[j] > kMinHeap[0]) {
			kMinHeap[0] = a[j];
			//弄进来之后要重新弄堆
			_AdjustDown(kMinHeap, k, 0);
		}
	}
	for (int i = 0; i < k; ++i) {
		cout << kMinHeap[i] << " ";
	}
	cout << endl;
}
void TestTopk()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (size_t i = 0; i < n; ++i)
	{
		//这里产生的小于1000000的数
		a[i] = rand() % 1000000;
	}
	//等下可以把下面这些数选出来
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;
	PrintTopK(a, n, 10);
}
int main() {
	TestTopk();
	return 0;
}