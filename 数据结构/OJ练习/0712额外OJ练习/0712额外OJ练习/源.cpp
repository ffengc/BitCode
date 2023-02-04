#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


//500. 键盘行
#if 0
class Solution {
private:
    vector<string>str = { "qwertyuiop","asdfghjkl","zxcvbnm" };
    int find(char s) {
        for (int i = 0; i < str.size(); i++) {
            for (int j = 0; j < str[i].size(); j++) {
                if (str[i][j] == s)return i;
            }
        }
        return -1;
    }
    bool is_Valid(string s) {
        if (s.size() == 1)return true;
        for (int i = 0; i < s.size(); i++) {//这里要记得全部换成小写才行
            s[i] = tolower(s[i]);
        }
        int flag = find(s[0]);
        for (int i = 1; i < s.size(); i++) {
            if (find(s[i]) != flag)return false;
        }
        return true;
    }
public:
    vector<string> findWords(vector<string>& words) {
        vector<string>ret;
        for (int i = 0; i < words.size(); i++) {
            if (is_Valid(words[i])) {
                ret.push_back(words[i]);
            }
        }
        return ret;
    }
};



string reverseString(string s) {
    int begin = 0;
    int end = s.size() - 1;
    while (begin <= end) {
        swap(s[begin], s[end]);
        begin++;
        end--;
    }
    return s;
}
#endif


class Solution {
private:
    int pick = 6;
    int guess(int n) {
        if (pick < n)return -1;
        if (pick > n)return 1;
        if (pick == n)return 0;
    }
public:
    int guessNumber(int n) {
        int mid = n / 2;
        while (mid - 1 >= 1 && n - mid >= 1) {
            int ret = guess(mid);
            if (ret == 1) {
                mid = (mid + n) / 2;
            }
            else if (ret == -1) {
                mid = (mid + 1) / 2;
            }
            else {
                return mid;
            }
        }
        return -1;
    }
};
int main() {
    Solution su;
    int ret = su.guessNumber(10);
    return 0;
}