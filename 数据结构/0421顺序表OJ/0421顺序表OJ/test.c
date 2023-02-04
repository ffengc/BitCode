#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//OJ27 移除元素
//1 2 2 2 3 4 5 6 2
//自己完成的
#if 0
void delete_num(int* arr,int*end) {
	int* cur = arr;
	while (cur < end) {
		*cur = *(cur + 1);
		cur++;
	}
}
int removeElement(int* arr, int numsSize, int val) {
	int* cur = arr;
	int* end = arr + numsSize - 1;
	while (cur <= end) {
		if (*cur == val) {
			delete_num(cur,end);
			numsSize--;
			end--;
		}
		else {
			cur++;
		}
	}
	return numsSize;
}
int main() {
	int arr[] = { 1,2,2,3,4,5,2,2,3,4,2 };
	int len = sizeof(arr) / sizeof(arr[0]);
	len = removeElement(arr, sizeof(arr) / sizeof(arr[0]), 2);
	//int* end = arr + len - 1;
	//delete_num(arr, end);
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
#endif
//但是这个时间复杂度不为O(n)了

//自己完成--双指针--杭哥也是这个方法
#if 0
int removeElement(int* arr, int numsSize, int val) {
	//1 2 2 2 3 4 5 6 2
	int* ahead = arr;
	int* end = arr + numsSize - 1;
	int* prev = arr;
	while (ahead <= end) {
		if (*ahead == val) {
			ahead++;
			numsSize--;
		}
		else {
			*prev = *ahead;
			prev++;
			ahead++;
		}
	}
	return numsSize;
}
int main() {
	int arr[] = { 1,2,2,3,4,5,2,2,3,4,2 };
	int len = sizeof(arr) / sizeof(arr[0]);
	len = removeElement(arr, sizeof(arr) / sizeof(arr[0]), 2);
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
#endif




//OJ26 删除有序数组中的重复项
#if 0
int removeDuplicates(int* nums, int numsSize) {
	//去重算法
	//双指针
	//1 2 2 3 4 5 6 2 2 2 2
	int* ahead = nums + 1;
	int* prev = nums;
	int* end = nums + numsSize - 1;
	while (ahead < end) {
		if (*ahead == *prev) {
			ahead++;
		}
		else {
			prev++;
			*prev = *ahead;
			ahead++;
		}
	}
	return prev-nums;
}
#endif


//OJ88 合并两个有序数组
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
	int* end1 = nums1 + m - 1;
	int* end2 = nums2 + n - 1;
	int* end = nums1 + m + n - 1;
	while ((end1 >= nums1) && (end2 >= nums2)) {
		if (*end1 > *end2) {
			*end-- = *end1--;
		}
		else if (*end1 < *end2) {
			*end-- = *end2--;
		}
	}
	while (end2 - nums2 >= 0) {
		*end-- = *end2--;
	}
}