#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<unordered_map>
using namespace std;

//345. 反转字符串中的元音字母
class Solution {
private:
    bool is_Valid(char ch) {
        ch = tolower(ch);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')return true;
        return false;
    }
public:
    string reverseVowels(string s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            if (is_Valid(s[left]) && is_Valid(s[right])) {
                swap(s[left], s[right]);
                left++;
                right--;
                continue;
            }
            if (is_Valid(s[left])) {
                right--;
                continue;
            }
            if (is_Valid(s[right])) {
                left++;
                continue;
            }
            left++;
            right--;
        }
        return s;
    }
};



void rotate_Array(vector<int>&arr) {
    int tmp = arr[arr.size() - 1];
    int end = arr.size() - 1;
    while (end > 0) {
        arr[end] = arr[end - 1];
        end--;
    }
    arr[end] =tmp;
}
int main() {
    vector<int>arr = { 1,2,3,4 };
    rotate_Array(arr);
    return 0;
}