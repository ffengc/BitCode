#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

#if 0
//209
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        if (nums.size() == 0)return 0;
        if (nums[0] >= target)return 1;
        int fast = 1;
        int slow = 0;
        int sum = nums[0];
        int len = 10000;//这个一定要足够大才行！
        while (fast < nums.size()) {
            sum += nums[fast];
            if (sum >= target) {
                while (slow < fast && sum - nums[slow] >= target) {
                    sum -= nums[slow];
                    slow++;
                }
                if (fast - slow < len) {
                    len = fast - slow + 1;
                }
                fast++;
            }
            else if (sum < target) {
                fast++;
            }
        }
        if (sum < target)return 0;
        return len;
    }
};
#endif


//剑指 Offer II 009. 乘积小于 K 的子数组
//713. 乘积小于 K 的子数组
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size(), ret = 0;
        int prod = 1, i = 0;
        for (int j = 0; j < n; j++) {
            prod *= nums[j];
            while (i <= j && prod >= k) {
                prod /= nums[i];
                i++;
            }
            ret += j - i + 1;
        }
        return ret;
    }
};
int main() {
    Solution su;
    vector<int>arr = { 10,5,2,6 };
    int k = 100;
    su.numSubarrayProductLessThanK(arr, k);
    return 0;
}