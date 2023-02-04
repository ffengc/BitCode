#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

//剑指 Offer II 049. 从根节点到叶节点的路径数字之和
class Solution {
private:
    vector<int>nums;
    vector<int>path;
    int sigma(vector<int>arr) {
        int num = 0;
        int j = 0;
        for (int i = arr.size() - 1; i >= 0; i--) {
            num += pow(10, j) * arr[i];
            j++;
        }
        return num;
    }
    void dfs(TreeNode* root) {
        if (root == nullptr)return;
        if (root->left == nullptr && root->right == nullptr) {
            path.push_back(root->val);
            int path_ret = sigma(path);
            nums.push_back(path_ret);
            path.pop_back();
            return;
        }
        if (root->left) {
            path.push_back(root->val);
            dfs(root->left);
            path.pop_back();
        }
        if (root->right) {
            path.push_back(root->val);
            dfs(root->right);
            path.pop_back();
        }
    }
public:
    int sumNumbers(TreeNode* root) {
        dfs(root);
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            ans += nums[i];
        }
        return ans;
    }
};