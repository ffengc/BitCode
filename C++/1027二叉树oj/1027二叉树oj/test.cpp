#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>
#include<set>
#include<algorithm>
#include<numeric>
#include<queue>
#include<assert.h>

using namespace std;

#elif
#endif

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

//105. 从前序与中序遍历序列构造二叉树
//大思路：前序创建树，中序分割左右子树
class Solution {
private:
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int& prei, int inbegin, int inend) {
        if (inbegin > inend)return nullptr;
        //[inbegin,inend]是中序遍历的区间 -- 等下分割要用
        //prei用来遍历preorder -- 因为preorder要按顺序遍历 -- 用来创建根
        TreeNode* root = new TreeNode(preorder[prei]);
        ++prei;
        //分割中序
        int ini = 0;
        vector<int>::iterator it = find(inorder.begin(), inorder.end(), root->val);//在中序中找这个val
        ini = it - inorder.begin();//这个是肯定能找到的
        //[inbegin,ini-1] ini [ini,inend]
        //现在递归创建左子树和右子树就行了
        root->left = _buildTree(preorder, inorder, prei, inbegin, ini - 1);
        root->right = _buildTree(preorder, inorder, prei, ini + 1, inend);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }
};



//106. 从中序与后序遍历序列构造二叉树
//和上一题是一样的 -- 倒过来就行
class Solution {
private:
    TreeNode* _buildTree(vector<int>& postorder, vector<int>& inorder, int& prei, int inbegin, int inend) {
        if (inbegin > inend)return nullptr;
        //[inbegin,inend]是中序遍历的区间 -- 等下分割要用
        //prei用来遍历preorder -- 因为preorder要按顺序遍历 -- 用来创建根
        TreeNode* root = new TreeNode(postorder[prei]);
        --prei;
        //分割中序
        int ini = 0;
        vector<int>::iterator it = find(inorder.begin(), inorder.end(), root->val);//在中序中找这个val
        ini = it - inorder.begin();//这个是肯定能找到的
        //[inbegin,ini-1] ini [ini,inend]
        //现在递归创建左子树和右子树就行了
        root->right = _buildTree(postorder, inorder, prei, ini + 1, inend);
        root->left = _buildTree(postorder, inorder, prei, inbegin, ini - 1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int i = postorder.size() - 1;
        return _buildTree(postorder, inorder, i, 0, inorder.size() - 1);
    }
};


//144. 二叉树的前序遍历
/*
1.左路节点
2.左路节点右子树
*/
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*>st;
        TreeNode* cur = root;
        vector<int>v;
        while (cur || !st.empty()) {
            //开始访问一棵树
            //1.先访问左路节点
            while (cur) {
                v.push_back(cur->val);
                st.push(cur);
                cur = cur->left;
            }
            //2.左路的节点的右子树
            TreeNode* top = st.top();
            st.pop();

            cur = top->right;//子问题访问右子树
            //最精华的就是这一句
        }
        return v;
    }
};


//94. 二叉树的中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*>st;
        vector<int>v;
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            //1.左路节点入栈 -- 但不push进v里面
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            //2.当左路节点从栈中出来时候，表示左子树已经访问过了 -- 应该访问根和右树
            TreeNode* top = st.top();
            st.pop();
            v.push_back(top->val);

            cur = top->right;//子问题 -- 访问右子树
            //其实和前序的区别仅仅就是访问的时机问题而已
            //一个是正向进去的时候就进v，一个是出来 -- pop的时候才进v
        }
        return v;
    }
};

//145. 二叉树的后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*>st;
        vector<int>v;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        while (cur || !st.empty()) {
            //1.左路节点入栈 -- 但不push进v里面
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            TreeNode* top = st.top();//我们找到这个节点的时候能不能直接pop？
            //不一定能
            //因为走到这里只能说明 -- top的左边已经访问过了
            //但是右边是否访问 -- 还是不清楚的
            //能否pop，能否访问当前节点取决于右边是否为空

            //如果当前节点右不为空的情况下：
            //1.右子树没有访问 -- 此时要去访问右节点
            //2.右子树已经访问过了 -- 访问根（当前）节点
            //区分方法
            //a.线索化 -- 看看上一次访问的节点是不是栈前面哪个节点
            //b.第一次访问当前节点之后 -- 在后面放个nullptr

            if (top->right == nullptr || top->right == prev) {
                //右边为空 -- 可以直接访问
                //如果是第二访问 -- 也可以进来
                v.push_back(top->val);
                prev = top;
                st.pop();
            }
            else {
                cur = top->right;
            }
            //st.pop();
            //v.push_back(top->val);

            //cur = top->right;//子问题 -- 访问右子树
            //其实和前序的区别仅仅就是访问的时机问题而已
            //一个是正向进去的时候就进v，一个是出来 -- pop的时候才进v
        }
        return v;
    }
};