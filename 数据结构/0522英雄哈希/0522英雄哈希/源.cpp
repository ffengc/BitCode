#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

//1748. 唯一元素的和
class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int hash[101] = { 0 };
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            ++hash[nums[i]];
        }
        for (int i = 0; i < nums.size(); i++) {
            if (hash[nums[i]] == 1) {
                sum += nums[i];
            }
        }
        return sum;
    }
};


//2206. 将数组划分成相等数对
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int hash[501] = { 0 };//这里记得要初始化
        for (int i = 0; i < nums.size(); i++) {
            ++hash[nums[i]];
        }
        for (int i = 0; i < nums.size(); i++) {
            //判断奇数还可以写成hash[i]&1
            if (hash[nums[i]] % 2 == 1)return false;
        }
        return true;
    }
};



//1832. 判断句子是否为全字母句
class Solution {
public:
    bool checkIfPangram(string sentence) {
        int hash[256] = { 0 };//直接开只有字母那一段也可以，不过直接开256吧
                          //字母的范围肯定在256之内
        for (int i = 0; i < sentence.size(); i++) {
            ++hash[sentence[i]];
        }
        for (int i = 'a'; i <= 'z'; i++) {
            if (hash[i] == 0)return false;
        }
        return true;
    }
};

//1512. 好数对的数目
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int hash[101] = { 0 };
        int ans = 0;
        for (int j = 0; j < nums.size(); j++) {
            //这里的意思是，如果hash[nums[j]]的位置是0，也就是没有出现过，就不用加
            ans += hash[nums[j]];
            ++hash[nums[j]];
        }
        return ans;
    }
};


//2006. 差的绝对值为 K 的数对数目
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int hash[101] = { 0 };
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i] + k;
            if (x >= 1 && x <= 100) {
                ans += hash[x];
            }
            x = nums[i] - k;
            if (x >= 1 && x <= 100) {
                ans += hash[x];
            }
            ++hash[nums[i]];
        }
        return ans;
    }
};



//930. 和相同的二元子数组
//前缀和+差分+哈希查找
//哈希其实就是用空间化时间
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int hash[60010] = { 0 };
        int ans = 0;
        //计算前缀和
        for (int i = 1; i < nums.size(); i++) {
            nums[i] += nums[i - 1];
            //前缀和先算出来，这里可以原地调整，即调整过后nums[i]就是前面所有元素的和
        }
        hash[goal] = 1;//把goal插入到哈希里面去
        for (int i = 0; i < nums.size(); i++) {
            ans += hash[nums[i]];
            ++hash[nums[i] + goal];
        }
        return ans;
    }
};


//560. 和为 K 的子数组
//这一题和上一题基本一样，区别就是这一题不再是0和1
//如果直接用数组模拟哈希上就会导致数组下标越界
//unordered_map可以帮助我们完成大整数的映射
class Solution {
private:
    unordered_map<int, int>hash;
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0;
        //其它的和上一题一样了
        //其实前面的哈希表都可以用这个
        for (int i = 1; i < nums.size(); i++) {
            nums[i] += nums[i - 1];
        }
        hash.clear();
        hash[k] = 1;
        for (int i = 0; i < nums.size(); i++) {//这个要从头遍历哈希，从0开始
            ans += hash[nums[i]];
            ++hash[nums[i] + k];
        }
        return ans;
    }
};


//454. 四数相加 II
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int>hash;
        hash.clear();
        int ret = 0;
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                ++hash[-(nums1[i] + nums2[j])];
            }
        }
        for (int i = 0; i < nums3.size(); i++) {
            for (int j = 0; j < nums4.size(); j++) {
                ret += hash[(nums3[i] + nums4[j])];
            }
        }
        return ret;
    }
};