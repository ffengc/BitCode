#define _CRT_SECURE_NO_WARNINGS 1



#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

#if 0
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
 
//965. 单值二叉树
//这个是自己写的
class Solution {
private:
    bool ret = true;
    void dfs(TreeNode* root, int x) {
        if (root == NULL)return;
        if (root->val != x)ret = false;
        if (ret == false)return;
        dfs(root->left, x);
        dfs(root->right, x);
    }
public:
    bool isUnivalTree(TreeNode* root) {
        dfs(root, root->val);
        return ret;
    }
};


//杭哥-不带返回值的dfs
class Solution {
private:
    bool flag = true;
    void PreOrderCompare(TreeNode* root, int val) {
        if (root == NULL || flag == false)return;
        if (root->val != val)flag = false;
        PreOrderCompare(root->left, val);
        PreOrderCompare(root->right, val);
    }
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == NULL)return true;
        PreOrderCompare(root, root->val);
        return flag;
    }
};


//这种方法要学会！
//带返回值的
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == NULL)return true;
        if (root->left && root->left->val != root->val) return false;
        if (root->right && root->right->val != root->val)return false;
        //走到这一样，说明顶上那三个是一样的，符合条件！
        //接下来才往下递归！
        return isUnivalTree(root->left) && isUnivalTree(root->right);
    }
    //画一下展开图进一步理解一下
    //递归不是返回到外面！是返回到上一层！
};



//100. 相同的树
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //这种如果要带返回值，一定要抓不相等，而不是抓相等
        if (p == NULL && q == NULL)return true;
        if ((p == NULL && q != NULL) || (p != NULL && q == NULL))return false;
        if (p->val != q->val)return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};




//101. 对称二叉树
//这个是自己写的
class Solution {
private:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //这种如果要带返回值，一定要抓不相等，而不是抓相等
        if (p == NULL && q == NULL)return true;
        if ((p == NULL && q != NULL) || (p != NULL && q == NULL))return false;
        if (p->val != q->val)return false;
        //这里稍微改一下，一个往左边跑，一个往右边跑
        return isSameTree(p->left, q->right) && isSameTree(p->right, q->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL)return true;
        if (root->left == NULL && root->right == NULL)return true;
        if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))return false;
        TreeNode* p = root->left;
        TreeNode* q = root->right;
        return isSameTree(p, q);
    }
};


//杭哥写的
class Solution {
public:
    bool compare(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL && root2 == NULL)return true;
        if ((!root1 && root2) || (!root2 && root1))return false;
        if (root1->val != root2->val)return false;
        return compare(root1->left, root2->right) && compare(root1->right, root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == NULL)return true;
        //不是空，比较左子树和右子树
        return compare(root->left, root->right);
    }
};



//572. 另一棵树的子树
class Solution {
private:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //这种如果要带返回值，一定要抓不相等，而不是抓相等
        if (p == NULL && q == NULL)return true;
        if ((p == NULL && q != NULL) || (p != NULL && q == NULL))return false;
        if (p->val != q->val)return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
#if 0
        if (root == NULL && subRoot == NULL)return true;
        if ((root == NULL && subRoot != NULL) || (root != NULL && subRoot == NULL))return false;//这里肯定没有
#endif
        if (root == NULL)return false;//这样也是可以的
        //找到了就返回true
        if (isSameTree(root, subRoot))return true;
        //找不到就往子树找
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};

#endif

//牛客KY11 二叉树的遍历 链接见课件
//建立二叉树之后，用中序遍历
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef char BTDataType;
typedef struct BinaryTreeNode {
    struct BinaryTreeNode* _left;
    struct BinaryTreeNode* _right;
    BTDataType data;
}BTNode;

BTNode* BuyNode(BTDataType x) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    assert(node);
    node->data = x;
    node->_left = NULL;
    node->_right = NULL;
    return node;
}
//这个就是前序构建二叉树的过程
BTNode* CreatTree(char* str, int* pi) {//同样这里给地址
    if (str[*pi] == '#') {
        (*pi)++;
        return NULL;
    }
    //
    BTNode* root = BuyNode(str[(*pi)++]);
    root->_left = CreatTree(str, pi);
    root->_right = CreatTree(str, pi);
    return root;
}
void InOrder(BTNode* root) {
    if (root == NULL)return;
    InOrder(root->_left);
    printf("%c ", root->data);
    InOrder(root->_right);
}
int main() {
    char str[100] = { 0 };
    scanf("%s", str);
    int i = 0;
    BTNode* root = CreatTree(str, &i);
    InOrder(root);
    return 0;
}