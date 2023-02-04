#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};
#if 0
class Solution {
private:
    int ret = 0;
    void dfs(TreeNode* root) {
        if (root == nullptr)return;
        if (root->left && root->left->left == nullptr && root->left->right == nullptr) {
            ret += root->left->val;
        }
        dfs(root->left);
        dfs(root->right);
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        dfs(root);
        return ret;
    }
};
#endif



class Solution {
private:
    int count_and_findIndex(vector<int>members) {
        vector<int>ans;
        for (int i = 0; i < members.size(); i++) {
            if (members[i] != 0) {
                ans.push_back(i);
            }
        }
        if (ans.size() != 1)return -1;
        return ans[0];
    }
public:
    int findTheWinner(int n, int k) {
        vector<int>members(n, -1);
        int j = 1;//控制数数
        int i = 0;//控制下标
        int index = 0;
        while (1) {
            //设置跳出条件
            index = count_and_findIndex(members);
            if (index != -1)break;
            while (members[i] == 0) {
                i++;
            }
            members[i] = j;
            if (j == k) {
                members[i] = 0;
                j = 0;
            }
            j++;
            i++;
            while (i < n && members[i] == 0) {
                i++;
            }
            //重新把下标弄回去
            if (i >= n) {
                i = 0;
            }
        }
        return index + 1;
    }
};
int main() {
    int n = 493;
    int k = 434;
    Solution su;
    int ret = su.findTheWinner(n, k);
    cout << ret << endl;
    return 0;
}
//这个方法答案是对的，但是超时了

//这个是答案
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> qu;
        for (int i = 1; i <= n; i++) {
            qu.emplace(i);
        }
        while (qu.size() > 1) {
            for (int i = 1; i < k; i++) {
                qu.emplace(qu.front());
                qu.pop();
            }
            qu.pop();
        }
        return qu.front();
    }
};

//这个是自己写的
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int>members;
        for (int i = 1; i <= n; i++) {
            members.push(i);
        }
        //已经把数字和人push进去了
        while (members.size() > 1) {
            for (int j = 1; j < k; j++) {
                members.push(members.front());
                members.pop();
            }
            members.pop();
        }
        return members.front();
    }
};