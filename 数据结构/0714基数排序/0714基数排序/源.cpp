#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
//基数排序
/*
* 核心思想：
* 1.分发数据
* 2.回收数据
*/
//这是一个多关键字排序
//按照位数多趟分发回收
#define K 3 //最多3位数
#define RADIX 10 //十个基数
#include<queue>

//定义基数
queue<int>Q[RADIX];//这个是队列数组--基数排序要做到先进先出 -- 所以使用队列
//找到key
int GetKey(int value, int k) {
	//value:278
	//k:0
	//代表第一次分发，按照8来排
	//所以就把8提取出来就可
	int key = 0;
	while (k >= 0) {
		key = value % 10;
		value /= 10;
		k--;
	}
	return key;//比如一个数字时25256 现在按照个位的6来分，key就返回的时6
}
//分发数据
void distribute(int* arr, int left, int right,int k) {
	//k代表是第几次分发
	for (int i = left; i < right; i++) {//注意这里是左闭右开，所以是<
		//根据key分发，key怎么找，用k来找
		int key = GetKey(arr[i], k);
		Q[key].push(arr[i]);//把arr[i]push到下标为8的队列里面
	}
}
void collect(int* arr) {
	//不需要区分第几次，只需要把数据回收到数组里面即可
	//要检查所有的队列，因为我们不知道哪一些队列有数据哪一些没有
	int k = 0;
	//arr从0开始重新收集
	for (int i = 0; i < RADIX; i++) {
		while (!Q[i].empty()) {
			//说明这个队列里面有数据
			//下面两行其实就是把数据依次放到数组里面去
			arr[k++] = Q[i].front();
			Q[i].pop();
		}
	}
}
void _radixSort(int* arr, int left, int right) {
	for (int i = 0; i < K; ++i) {//最多循环三次
		//有几位数循环几次
		//分发数据
		distribute(arr, left, right, i);//i代表我现在操作的时哪一位数
		//回收数据
		collect(arr);
	}
}
void radixSort(int* arr, int sz) {
	int left = 0;
	int right = sz;
	//[right,left)
	_radixSort(arr, left, right);
}
int main() {
	int arr[] = { 278,109,63,930,589,184,505,269,8,83 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	//
	radixSort(arr, sz);
	//
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}