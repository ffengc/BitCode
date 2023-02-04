#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<stack>
#include<queue>
#include<unordered_map>
using namespace std;

//1662. 检查两个字符串数组是否相等
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string str1;
        string str2;
        for (int i = 0; i < word1.size(); i++) {
            str1 += word1[i];
        }
        for (int i = 0; i < word2.size(); i++) {
            str2 += word2[i];
        }
        if (str1 == str2) {
            return true;
        }
        return false;
    }
};

//2149. 按符号重排数组
//这种方法空间复杂度高
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int>positive;
        vector<int>nagetive;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0)positive.push_back(nums[i]);
            else nagetive.push_back(nums[i]);
        }
        int size = nums.size();
        nums.clear();
        for (int i = 0; i < positive.size() && i < nagetive.size(); i++) {
            nums.push_back(positive[i]);
            nums.push_back(nagetive[i]);
        }
        return nums;
    }
};


//2176. 统计数组中相等且可以被整除的数对
class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] != nums[j])continue;
                if ((i * j) % k == 0)cnt++;
            }
        }
        return cnt;
    }
};
