#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
//1768. 交替合并字符串
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string str;
        int i = 0;
        for (i = 0; i < word1.size() && i < word2.size(); i++) {
            str += word1[i];
            str += word2[i];
        }
        //此时的i word1.size()-1  word2.size()-1
        if (i < word1.size() - 1) {
            for (int j = i; j < word1.size(); j++) {
                str += word1[j];
            }
        }
        if (i < word2.size() - 1) {
            for (int j = i; j < word2.size(); j++) {
                str += word2[j];
            }
        }
        return str;
    }
};
#if 0
int main() {
    Solution su;
    string str1 = "ab";
    string str2 = "pqrs";
    su.mergeAlternately(str1, str2);
    return 0;
}
#endif


//面试题 01.01. 判定字符是否唯一
class Solution {
public:
    bool isUnique(string astr) {
        sort(astr.begin(), astr.end());
        for (int i = 0; i < astr.size() - 1; i++) {
            if (astr[i] == astr[i + 1])return false;
        }
        return true;
    }
};