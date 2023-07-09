#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


//31. 下一个排列
//超时未通过
class Solution {
private:
    vector<vector<int>>ret;
    vector<int>path;
    void dfs(vector<int>nums, vector<bool>used) {
        if (path.size() == nums.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i&& nums[i] == nums[i - 1] && used[i - 1] == false)continue;
            if (used[i] == true)continue;
            path.push_back(nums[i]);
            used[i] = true;
            dfs(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
    int find_index(vector<int>nums) {
        for (int i = 0; i < ret.size(); i++) {
            if (nums == ret[i])return i;
        }
        return -1;
    }
public:
    void nextPermutation(vector<int>& nums) {
        vector<int>nums_org = nums;
        sort(nums_org.begin(), nums_org.end());
        vector<bool>used(nums.size() + 1, false);
        dfs(nums_org, used);
        int idx = find_index(nums);
        if (idx == ret.size() - 1)nums = ret[0];
        else nums = ret[idx + 1];
    }
};
int main() {
    vector<int>nums = { 1,5,1 };
    Solution().nextPermutation(nums);
    return 0;
}