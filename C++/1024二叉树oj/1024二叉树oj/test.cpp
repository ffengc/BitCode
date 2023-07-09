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
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//606. 根据二叉树创建字符串
//1.左右都为空 -- 省略
//2.左不为空，右为空 -- 省略
//tips:左空右不空 -- 不省略 -- 因为省略了就分不清数字是左的还是右的了
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)return"";
        string str;
        str += to_string(root->val);

        //左边部位哦那个或者左边为空右边不为空，左边保留
        if (root->left || root->right) {
            str += '(';
            //中间的交给子问题
            str += tree2str(root->left);
            str += ')';
        }

        //右为空一定为空肯定要省略
        if (root->right) {
            str += '(';
            str += tree2str(root->right);
            str += ')';
        }
        return str;
    }
};


//102. 二叉树的层序遍历
//思路：出一个带一层
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ret;
        if (root == nullptr)return ret;
        queue<TreeNode*>q;
        size_t levelsize = 0;

        q.push(root);
        levelsize = 1;
        while (!q.empty()) {
            //控制一层一层出
            vector<int>path;
            for (size_t i = 0; i < levelsize; ++i) {
                TreeNode* front = q.front();
                q.pop();
                path.push_back(front->val);
                if (front->left) {
                    q.push(front->left);
                }
                if (front->right) {
                    q.push(front->right);
                }
            }
            ret.push_back(path);
            //当前层出完了，下一层都进队列了，队列的size就是下一层的数据个数
            levelsize = q.size();
        }
        return ret;
    }
};
/** 双队列也可以解决这个问题 -- 一个用来存TreeNode*,一个用来存层 */



//107. 二叉树的层序遍历 II
//最简思路：把正序的reverse一下


//236. 二叉树的最近公共祖先
//方法1：
//如果两个节点分别在当前节点的两边，当前节点就是最近祖先
//O(h*n)
class Solution {
private:
    bool find(TreeNode* sub, TreeNode* x) {
        if (sub == nullptr)return false;
        if (sub == x)return true;
        return find(sub->left, x) || find(sub->right, x);
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //如果两个节点一个在我的左，一个在我的右 -- 就算找到了
        //都在我的左边 -- 直接进左边
        //都在我的右边 -- 直接进右边
        if (root == nullptr)return nullptr;
        if (root == p || root == q) {
            return root;
        }
        //走到这里,pq都在子树里
        bool pInLeft, pInRight, qInLeft, qInRight;
        pInLeft = find(root->left, p);
        pInRight = !pInLeft;
        qInLeft = find(root->left, q);
        qInRight = !qInLeft;
        if ((pInLeft && qInRight) || (qInLeft && pInRight))return root;
        else if (pInLeft && qInLeft) {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if (pInRight && qInRight) {
            return lowestCommonAncestor(root->right, p, q);
        }
        else {
            //按照题目要求不会走到这里
            assert(false);
        }
    }
};

//优化到O(n)
//找到节点的路径
class Solution {
private:
    //这个查找和以前写的其实本质是一样的
    //只不过是我额外的把路径放进path里面而已
    bool find_path(TreeNode* root, TreeNode* x, stack<TreeNode*>& path) {
        if (root == nullptr)return false;
        path.push(root);
        if (root == x)return true;
        if (find_path(root->left, x, path)) {
            return true;
        }
        if (find_path(root->right, x, path)) {
            return true;
        }
        path.pop();
        return false;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //用一个栈存路径
        stack<TreeNode*>pPath, qPath;
        find_path(root, p, pPath);
        find_path(root, q, qPath);
        //类似链表相交
        while (pPath.size() != qPath.size()) {
            if (pPath.size() > qPath.size()) {
                pPath.pop();
            }
            else if (pPath.size() < qPath.size()) {
                qPath.pop();
            }
        }
        while (pPath.top() != qPath.top()) {
            pPath.pop();
            qPath.pop();
        }
        return pPath.top();
    }
};



//牛客 JZ36 二叉搜索树与双向链表

/**
 * left指向中序的前一个
 * right指向中序的后一个.
 */

/*
思路一
左 - 中 - 右 处理left
右 - 根 - 左 处理right
*/
class Solution {
private:
    void inorderconvert(TreeNode* cur, TreeNode*& prev) {//prev要给引用 -- 因为prev要改
        if (cur == nullptr)return;
        inorderconvert(cur->left, prev);
        cur->left = prev;
        if (prev)
            prev->right = cur;
        prev = cur;

        inorderconvert(cur->right, prev);
    }
public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode* prev = nullptr;
        inorderconvert(pRootOfTree, prev);
        //找到头就行了
        TreeNode* head = pRootOfTree;
        //不断往左找就行了
        while (head && head->left) {
            head = head->left;
        }
        return head;
    }
};




////剑指 Offer 36. 二叉搜索树与双向链表
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node() {}
    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }
    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
//注意这个是循环的
//和上面大致一样
//最后加上一个头尾相连就行了
class Solution {
private:
    void inorder(Node* root, Node*& prev) {
        if (root == nullptr)return;
        inorder(root->left, prev);
        root->left = prev;
        if (prev)
            prev->right = root;
        prev = root;//递归迭代
        inorder(root->right, prev);
    }
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr)return nullptr;
        Node* prev = nullptr;
        inorder(root, prev);
        Node* head = root;
        while (head && head->left)head = head->left;
        Node* tail = root;
        while (tail && tail->right)tail = tail->right;
        //此时找到head和tail了
        head->left = tail;
        tail->right = head;
        return head;
    }
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