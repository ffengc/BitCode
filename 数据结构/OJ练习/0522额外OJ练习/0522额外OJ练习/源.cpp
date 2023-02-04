#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//2108. 找出数组中的第一个回文字符串
class Solution {
private:
    bool isValid(string s) {
        int left = s.size() - 1;
        int right = 0;
        while (left > right) {
            if (s[left] != s[right])return false;
            left--;
            right++;
        }
        return true;
    }
public:
    string firstPalindrome(vector<string>& words) {
        string ret;
        ret = "";
        for (int i = 0; i < words.size(); i++) {
            if (isValid(words[i])) {
                ret = words[i];
                break;
            }
        }
        return ret;
    }
};


//1528. 重新排列字符串
class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string ret(s.size(), 0);
        for (int i = 0; i < indices.size(); i++) {
            ret[indices[i]] = s[i];
        }
        return ret;
    }
};