#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//KMP其实利用前缀表的利用
//因为strstr暴力查找 -- 浪费的时间其实就是字串不断一次一次的重复
//而KMP的优势在于，因为我已经得到了前缀
//所以移动字符串之后，前面的不用比较了


//生成前缀表
void prefix_table(char pattern[], int prefix[], int n) {
	//其实是动态规划的思想
	prefix[0] = 0;//初始化
	int len = 0;
	int i = 1;//应该是从第二个字母开始比较
	while (i < n) {
		//如果发现第i个位置的字母等于第len位置的字母
		//说明前缀[]可以++
		//i是在遍历的下标
		//len是从0开始算的前缀，len在左边
		if (pattern[i] == pattern[len]) {
			len++;//前缀可以++，因为匹配上了
			prefix[i] = len;
			i++;
		}
		else {//不相等
			//这里要斜着匹配 -- 不明白
			if (len > 0)len = prefix[len - 1];
			else {
				prefix[i] = len;
				i++;//要记得迭代
			}
		}
	}
}
//写一个函数把这个prefix前缀表向后移一位
void move_prefix_table(int prefix[], int n) {
	for (int i = n - 1; i > 0; i--) {
		prefix[i] = prefix[i - 1];
	}
	prefix[0] = -1;
}
void kmp_search(char text[], char pattern[]) {

}
int main() {
	char pattern[] = "ABABCABAA";
	int prefix[9];
	int n = 9;
	prefix_table(pattern, prefix, n);
	move_prefix_table(prefix, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", prefix[i]);
	}
	return 0;
}