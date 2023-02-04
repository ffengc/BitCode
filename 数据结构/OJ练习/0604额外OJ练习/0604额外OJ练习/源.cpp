#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<string>
#include<vector>
using namespace std;

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
};

//¾µÏñ¶þ²æÊ÷
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};


//LCP 44. ¿ªÄ»Ê½Ñæ»ð
class Solution {
private:
    int hash[1002] = { 0 };
    void dfs(TreeNode* root) {
        if (root == nullptr)
            return;
        ++hash[root->val];
        dfs(root->left);
        dfs(root->right);
    }
public:
    int numColor(TreeNode* root) {
        int ret = 0;
        dfs(root);
        for (int i = 0; i < 1001; i++) {
            if (hash[i])
                ++ret;
        }
        return ret;
    }
};