#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;

#if 0
//2114. 句子中的最多单词数
int count_words(char* arr) {
    int cnt = 0;
    while (*arr) {
        arr++;
        if (*arr == ' ' || *arr == '\0')cnt++;
    }
    return cnt;
}
int mostWordsFound(char** sentences, int sentencesSize) {
    int _max = -1;
    for (int i = 0; i < sentencesSize; i++) {
        if (count_words(sentences[i]) > _max) {
            _max = count_words(sentences[i]);
        }
    }
    return _max;
}


//771. 宝石与石头
bool find(char* jewels, char ch) {
    int len = strlen(jewels);
    for (int i = 0; i < len; i++) {
        if (ch == jewels[i])return true;
    }
    return false;
}
int numJewelsInStones(char* jewels, char* stones) {
    int len = strlen(stones);
    int cnt = 0;
    for (int i = 0; i < len; i++) {
        if (find(jewels, stones[i]))cnt++;
    }
    return cnt;
}

//1221. 分割平衡字符串
//贪心
int balancedStringSplit(char* s) {
    int cnt = 0;
    int cur = 0;
    int l = 0;
    int r = 0;
    int len = strlen(s);
    while (cur < len) {
        if (s[cur] == 'L')l++;
        if (s[cur] == 'R')r++;
        if (l == r) {
            cnt++;
            l = 0;
            r = 0;
        }
        cur++;
    }
    return cnt;
}

//344. 反转字符串
void reverseString(char* s, int sSize) {
    char* left = s;
    char* right = s + sSize - 1;
    char tmp = 0;
    tmp = *left;
    *left = *right;
    *right = '\0';
    if (sSize > 2) {
        reverseString(s + 1, sSize - 2);
    }
    *right = tmp;
}

//709. 转换成小写字母
char* toLowerCase(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}


// 2000. 反转单词前缀
void reverseString(char* s, int sSize) {
    char* left = s;
    char* right = s + sSize - 1;
    char tmp = 0;
    tmp = *left;
    *left = *right;
    *right = '\0';
    if (sSize > 2) {
        reverseString(s + 1, sSize - 2);
    }
    *right = tmp;
}
char* reversePrefix(char* word, char ch) {
    char* cut = word;
    for (int i = 0; i < strlen(word); i++) {
        if (ch == word[i]) {
            cut = word + i;
            break;
        }
    }
    reverseString(word, cut - word + 1);
    return word;
}

//剑指 Offer II 006. 排序数组中两个数字之和
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int>ret;
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                ret.push_back(left);
                ret.push_back(right);
                return ret;
            }
            else if (sum > target) {
                right--;
            }
            else if (sum < target) {
                left++;
            }
        }
        return ret;
    }
};


//167. 两数之和 II - 输入有序数组
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int>ret;
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                ret.push_back(left + 1);
                ret.push_back(right + 1);
                return ret;
            }
            else if (sum > target) {
                right--;
            }
            else if (sum < target) {
                left++;
            }
        }
        return ret;
    }
};

#endif


//剑指 Offer II 075. 数组相对排序
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int>ret;
        int hash[1001] = { 0 };
        //放入哈希表
        for (int i = 0; i < arr1.size(); i++) {
            ++hash[arr1[i]];
        }
        //拿出来
        for (int i = 0; i < arr2.size(); i++) {
            while (hash[arr2[i]]--) {
                ret.push_back(arr2[i]);
            }
        }
        //最后再把多出来的放进去
        for (int i = 0; i < 1001; i++) {
            while (hash[i] > 0) {
                ret.push_back(i);
                hash[i]--;
            }
        }
        return ret;
    }
};