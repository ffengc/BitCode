#pragma once

#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;

void PrintArray(int* a, int n);
// 插入排序
void InsertSort(int* a, int n);
// 希尔排序
void ShellSort(int* a, int n);
// 选择排序
void SelectSort(int* a, int n);
// 堆排序
void HeapSort(int* a, int n);
// 冒泡排序
void BubbleSort(int* a, int n);
// 快速排序递归实现
void QuickSort(int* a, int n);
//归并排序
void MergeSort(int* a, int n);
void MergeSortNonR(int* a, int n);
//记录快排递归次数(声明)
extern int callCount;
//计数排序
void CountSort(int* a, int n);
//计数排序的局限性
/*
* 1.如果是浮点数、字符串就不能玩了
* 2.如果数据范围很大，空间复杂度就会很高。相对不适合
*/