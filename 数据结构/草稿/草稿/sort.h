#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<ctime>
using namespace std;

void BubbleSort(int* arr, int sz);
void SelectSort(int* arr, int sz);
void InsertSort(int* arr, int sz);
void ShellSort(int* arr, int sz);
void QuickSort(int* arr, size_t sz);
void MergeSort(int* arr, int sz);
void HeapSort(int* arr, int sz);
void BucketSort(int* arr, int sz);
void RadixSort(int* arr, int sz);