#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

//41. 缺失的第一个正数
class Solution {
private:
    int find_one(vector<int>nums) {
        int i = 0;
        for (i = 0; i < nums.size(); i++) {
            if (nums[i] == 1)break;
        }
        return i;
    }
    void removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return;
        }
        int fast = 1, slow = 1;
        while (fast < n) {
            if (nums[fast] != nums[fast - 1]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
    }
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        //调用一下删除数组重复项的代码
        removeDuplicates(nums);
        //先看看这个数组的最大值是什么，如果小于等于0，直接返回1即可
        if (nums[nums.size() - 1] <= 0)return 1;
        if (nums[0] > 1)return 1;
        int index = find_one(nums);
        int cmp = 1;
        while (index < nums.size()) {
            if (nums[index] == cmp) {
                cmp++;
                index++;
            }
            else {
                return cmp;
            }
        }
        return cmp;
    }
};