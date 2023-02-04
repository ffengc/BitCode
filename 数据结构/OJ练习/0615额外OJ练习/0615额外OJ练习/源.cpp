#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//面试题 08.08.有重复字符串的排列组合
class Solution {
private:
    void string_sort(string& s) {
        for (int i = 0; i < s.size() - 1; i++) {
            for (int j = 0; j < s.size() - 1 - i; j++) {
                if (s[j] > s[j + 1]) {
                    swap(s[j], s[j + 1]);
                }
            }
        }
    }
    vector<string>ret;
    string path;
    void dfs(string s, vector<bool>used) {
        if (s.size() == path.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (i && s[i] == s[i - 1] && used[i - 1] == false)continue;
            if (used[i] == true)continue;
            path.push_back(s[i]);
            used[i] = true;
            dfs(s, used);
            used[i] = false;
            path.pop_back();
        }
    }
public:
    vector<string> permutation(string S) {
        string_sort(S);
        vector<bool>used(S.size() + 1, false);
        dfs(S, used);
        return ret;
    }
};



//剑指 Offer II 007. 数组中和为 0 的三个数
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3)return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>>ret;
        for (int i = 0; i < nums.size(); i++) {
            //枚举第一个数字
            if (i && nums[i] == nums[i - 1])continue;
            int ret1 = nums[i];
            int target = 0 - ret1;
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum == target) {
                    ret.push_back({ ret1,nums[left],nums[right] });
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1])left++;
                    while (left < right && nums[right] == nums[right + 1])right--;
                }
                else if (sum < target) {
                    left++;
                }
                else if (sum > target) {
                    right--;
                }
            }
        }
        return ret;
    }
};