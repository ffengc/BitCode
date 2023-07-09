#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;


//60. 排列序列
//效率不过关 -- 超时了
//优化后通过
#if 0
class Solution {
private:
    int cnt = 0;
    vector<vector<int>>ret;
    vector<int>path;
    vector<int>ans;
    int _factorial(int x) {
        int ans = 1;
        for (int i = 1; i <= x; i++) {
            ans *= i;
        }
        return ans;
    }
    void dfs(vector<int>nums, vector<bool>used, int k) {
        //先完成一些剪枝 -- 不然过不了
        int rest_numNodes_cnt = _factorial(nums.size() - path.size() - 1);
        if (path.size() == nums.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true)continue;
            if (rest_numNodes_cnt < k && rest_numNodes_cnt>0) {
                k -= rest_numNodes_cnt;
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            dfs(nums, used, k);
            //为什么这里不用换原状态？
            //used[i] = false;
            //path.pop_back();
        }
    }
    int My_to_int(vector<int>arr) {
        int ret = 0;
        for (int i = 0; i < arr.size(); i++) {
            ret += arr[i] * pow(10, arr.size() - i - 1);
        }
        return ret;
    }
public:
    string getPermutation(int n, int k) {
        vector<int>nums;
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }
        vector<bool>used(n, false);
        dfs(nums, used, k);
        //现在要将ret的下标为k-1的几个数字合并成一个数
        int ans = My_to_int(ret[ret.size() - 1]);
        return to_string(ans);
    }
};
int main() {
    cout << Solution().getPermutation(9, 94626) << endl;
    //"348567921"
    return 0;
}
#endif
/*
所求排列 一定在叶子结点处得到，进入每一个分支，可以根据已经选定的数的个数，进而计算还未选定的数的个数，然后计算阶乘，就知道这一个分支的 叶子结点 的个数：
如果 kk 大于这一个分支将要产生的叶子结点数，直接跳过这个分支，这个操作叫「剪枝」；
如果 kk 小于等于这一个分支将要产生的叶子结点数，那说明所求的全排列一定在这一个分支将要产生的叶子结点里，需要递归求解。
*/





//42. 接雨水
//算法正确，但是超时
//思路：一层一层算
class Solution {
private:
    int count_rain_v(vector<int>blocks) {
        //现在blocks是每一层的情况
        //用双指针控制
        int slow = 0;
        int fast = 0;
        int sum_v = 0;
        while (fast < blocks.size()) {
            if (fast == slow && blocks[fast] == 0 && (fast == 0) || fast == blocks.size() - 1) {
                //这种情况，两个指向0的可以同时前进
                fast++;
                slow++;
            }
            else if (fast == slow && blocks[fast] == 1) {
                fast++;
                slow++;
            }
            else if (fast == slow && blocks[fast] == 0 && blocks[fast - 1] == 1) {
                //fast走，slow不动
                while (fast < blocks.size() && blocks[fast] == 0)fast++;
                if (fast == blocks.size()) {
                    //说明fast走出去了，不用加
                    return sum_v;
                }
                //此时说明，fast没有出去，可以积累雨水
                sum_v += fast - slow;
                slow = fast;
            }
            else {
                fast++;
                slow++;
            }
        }
        return sum_v;
    }
public:
    int trap(vector<int>& height) {
        //计算每一层能接到雨水的体积
        //先算出最高几层楼
        int max_height = INT_MIN;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > max_height) {
                max_height = height[i];
            }
        }
        //先把每一层的数组弄出来先
        vector<vector<int>>blocks;
        for (int i = 0; i < max_height; i++) {
            vector<int>path;
            for (int j = 0; j < height.size(); j++) {
                if (height[j] - i > 0) {
                    path.push_back(1);
                }
                else path.push_back(0);
            }
            blocks.push_back(path);
        }
        //[0,1,0,2,1,0,1,3,2,1,2,1]

        //[0,1,0,1,1,0,1,1,1,1,1,1]
        //[0,0,0,1,0,0,0,2,1,0,1,0]
        //[0,0,0,0,0,0,0,1,0,0,0,0]
        //计算每一层能积累的雨水
        int ans_v = 0;//最终体积
        for (int i = 0; i < blocks.size(); i++) {
            //现在是遍历每一层
            ans_v += count_rain_v(blocks[i]);
        }
        return ans_v;
    }
};
int main() {
    vector<int>height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    Solution().trap(height);
    return 0;
}