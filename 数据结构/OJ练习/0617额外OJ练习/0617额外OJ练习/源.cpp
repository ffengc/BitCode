#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;


//剑指 Offer 57 - II. 和为s的连续正数序列
class Solution {
public:
    //滑动窗口
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>>ret;
        vector<int>path;
        if (target == 0 || target == 1 || target == 2)return {};
        int fast = 2;
        int slow = 1;
        int sum = slow;
        while (fast < target) {
            if (sum + fast < target) {
                sum += fast;
                fast++;
            }
            //如果相等
            if (sum + fast == target) {
                sum += fast;
                sum -= slow;
                for (int i = slow; i <= fast; i++) {
                    path.push_back(i);
                }
                ret.push_back(path);
                path.clear();
                fast++;
                slow++;
            }
            if (sum + fast > target) {
                sum -= slow;
                slow++;
            }
        }
        return ret;
    }
};







int my_strlen(char* s) {
    int cnt = 0;
    while (*s && *s != ' ') {
        cnt++;
        s++;
    }
    return cnt;
}
int lengthOfLastWord(char* s) {
    int len = 0;
    while (*s) {
        while (*s && *s == ' ') {
            s++;
        }
        if (*s != ' ' && *s) {
            len = my_strlen(s);
            s = s + len;
        }
        else break;
    }
    return len;
}
int main() {
    char arr[] = "   fly me   to   the moon  ";
    int ret=lengthOfLastWord(arr);
    return 0;
}