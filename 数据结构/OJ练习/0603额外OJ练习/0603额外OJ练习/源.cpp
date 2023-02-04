#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
void reverse_str(char* str, int n) {
	char* start = str;
	char* end = str + n - 1;
	char tmp = *start;
	*start = *end;
	*end = tmp;
	if (n > 2) {
		reverse_str(str + 1, n - 2);
	}
}
char* reverseLeftWords(char* str, int k) {
	char* cut = str + k;
	reverse_str(str, k);
	reverse_str(cut, strlen(str) - k);
	reverse_str(str, strlen(str));
	return str;
}
bool isFlipedString(char* s1, char* s2) {
	if (strlen(s1) == strlen(s2) && strlen(s1) == 0)return true;
	if (strlen(s1) != strlen(s2))return false;
	int sz = strlen(s1);
	for (int i = 0; i < sz; i++) {
		reverseLeftWords(s2, 1);
		if (!strcmp(s1, s2))return true;
	}
	return false;
}
int main() {
	char str1[] = "abcd";
	char str2[] = "acdb";
	isFlipedString(str1, str2);
	return 0;
}