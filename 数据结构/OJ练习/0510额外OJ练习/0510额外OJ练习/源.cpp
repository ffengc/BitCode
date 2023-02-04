#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<string>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};


//66. 加一
//思路：逆序找到第一个不为9的数字，把它++，然后后面的全部置为0
//如果全是9，就返回一个新的数组，大小比digits大1，然后第一个数字为1，其他全为0
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] != 9) {
                ++digits[i];
                for (int j = i + 1; j < n; ++j) {
                    digits[j] = 0;
                }
                return digits;
            }
        }

        // digits 中所有的元素均为 9
        vector<int> ans(n + 1);
        ans[0] = 1;
        return ans;
    }
};



//283. 移动零
//双指针算法
//如果不注意跳出循环条件
//容易越界访问
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int prev = 0;
        int cur = 0;
        while (cur < nums.size() - 1) {
            while (nums[prev] == 0 && nums[cur] == 0 && cur < nums.size() - 1) {
                cur++;
            }
            //此时cur指向的数字不为0了，交换两个数字
            if (nums[prev] == 0 && nums[cur] != 0 && cur > prev) {
                swap(nums[prev], nums[cur]);
            }
            while (nums[prev] != 0) {
                if (cur == prev) {
                    cur++;
                }
                prev++;
                if (prev == nums.size() - 1)break;
            }
            if (prev == (nums.size() - 1) || cur < prev)
                break;
        }
    }
};





//191. 位1的个数
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        for (int i = 0; i < 32; i++) {
            if ((n >> i) & 1 == 1) {
                cnt++;
            }
        }
        return cnt;
    }
};




//2235. 两整数相加
class Solution {
public:
    int sum(int num1, int num2) {
        return num1 + num2;
    }
};



//1480. 一维数组的动态和
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int sum = 0;
        vector<int>ret;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            ret.push_back(sum);
        }
        return ret;
    }
};


//1929. 数组串联
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        vector<int>ret;
        for (int i = 0; i < nums.size(); i++) {
            ret.push_back(nums[i]);
        }
        for (int i = 0; i < nums.size(); i++) {
            ret.push_back(nums[i]);
        }
        return ret;
    }
};

//1920. 基于排列构建数组
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        vector<int>ret;
        for (int i = 0; i < nums.size(); i++) {
            ret.push_back(nums[nums[i]]);
        }
        return ret;
    }
};


//1672. 最富有客户的资产总量
class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int max = 0;
        int sum = 0;
        for (int i = 0; i < accounts.size(); i++) {
            sum = 0;
            for (int j = 0; j < accounts[0].size(); j++) {
                sum += accounts[i][j];
            }
            if (sum > max)max = sum;
        }
        return max;
    }
};



//1720. 解码异或后的数组
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int>ret;
        ret.push_back(first);
        for (int i = 0; i < encoded.size(); i++) {
            ret.push_back(ret[i] ^ encoded[i]);
        }
        return ret;
    }
};



//2011. 执行操作后的变量值
class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int x = 0;
        for (int i = 0; i < operations.size(); i++) {
            if (operations[i] == "X++") {
                x++;
            }
            else if (operations[i] == "++X") {
                ++x;
            }
            else if (operations[i] == "X--") {
                x--;
            }
            else if (operations[i] == "--X") {
                --x;
            }
        }
        return x;
    }
};
