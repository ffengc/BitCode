#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
using namespace std;
//真正的堆排序O(nlogn)
//向上调整算法
void _AdjustUp(int* a, int child) {
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
void _AdjustDown(int* a, int size, int parent) {
	int child = parent * 2 + 1;
	while (child < size) {
		//选出小的那个孩子节点
		if (child + 1 < size && a[child + 1] > a[child]) {
			++child;
		}
		if (a[child] > a[parent]) {
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
void _heapSort1(int* a, int n) {
	//建堆-方式1
#if 0
	for (int i = 1; i < n; i++) {
		//从第二个位置开始向上调整
		_AdjustUp(a, i);
	}
#endif
	//建堆-方式2
	//从倒数第一个非叶子节点开始向下调整-迭代向上
	//向下调整的前提：左右子树必须是大/小堆
	//否则向下调整没有意义
	//所以我们建堆的时候要从下往上
	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {//n-1是最后一个叶子，n-1-1/2就是第一个非叶子节点
		_AdjustDown(a, n, i);
	}
	//这个建堆-方式1的复杂度是O(NlogN)，因为最多是高度次
	//方式2的复杂度是O(n)--方式2更快

	//升序--建大堆
	//如果建小堆-选出最小的数，还要重新建堆，每次建堆是O(n)
	//最后是O(n^2)
	//那跟冒泡一样，还用这么麻烦
	//建大堆
	//向下调整O(logN)
	int end = n - 1;
	while (end > 0) {
		swap(a[0], a[end]);
		_AdjustDown(a, end, 0);
		--end;
	}
}
int main() {
	int arr[] = { 27,15,19,18,28,34,65,49,25,37 };
	int size = sizeof(arr) / sizeof(arr[0]);
	_heapSort1(arr, size);//堆排序
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}