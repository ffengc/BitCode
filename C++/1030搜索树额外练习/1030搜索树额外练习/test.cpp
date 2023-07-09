#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<unordered_map>
#include<set>
#include<algorithm>

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

//98. 验证二叉搜索树
//一次通过 -- good
//思路：判断中序是否递增 + 用set判断是否有重复值
class Solution {
private:
    vector<int>order;
    void dfs(TreeNode* root) {
        if (root == nullptr)return;
        dfs(root->left);
        order.push_back(root->val);
        dfs(root->right);
    }
    void duplicate_removal(vector<int>& arr) {
        set<int>s;
        for (auto e : arr) {
            s.insert(e);
        }
        arr.clear();
        set<int>::iterator it = s.begin();
        while (it != s.end()) {
            arr.push_back(*it);
            it++;
        }
    }
public:
    bool isValidBST(TreeNode* root) {
        //有重复的也不能是搜索树
        dfs(root);
        vector<int>tmp = order;
        duplicate_removal(order);
        if (order != tmp)return false;
        sort(order.begin(), order.end());
        return tmp == order;
    }
};



//剑指 Offer II 052. 展平二叉搜索树
//思路：记录中序遍历的顺序，重新构造树
//问题：1.空间复杂度为O(n)  2.节点没有释放
class Solution {
private:
    vector<int>arr;
    void dfs(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left);
        arr.push_back(root->val);
        dfs(root->right);
    }
    TreeNode* creat_new_tree() {
        if (arr.size() == 0)return nullptr;
        TreeNode* root = new TreeNode(arr[0]);
        TreeNode* cur = root;
        for (int i = 1; i < arr.size(); i++) {
            cur->right = new TreeNode(arr[i]);
            cur = cur->right;
        }
        return root;
    }
public:
    TreeNode* increasingBST(TreeNode* root) {
        //先用一个列表来存储中序遍历的值
        dfs(root);
        //构造新树
        return creat_new_tree();
    }
};


//剑指 Offer II 056. 二叉搜索树中两个节点之和
//思路：有序数组的二分查找
class Solution {
private:
    vector<int>arr;
    void dfs(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left);
        arr.push_back(root->val);
        dfs(root->right);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        dfs(root);
        //二分查找数组arr
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int sum = arr[left] + arr[right];
            if (sum > k) {
                right--;
            }
            else if (sum < k) {
                left++;
            }
            else if (sum == k) {
                return true;
            }
        }
        return false;
    }
};


//700. 二叉搜索树中的搜索
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* cur = root;
        while (cur) {
            if (cur->val == val)return cur;
            else if (val > cur->val) {
                cur = cur->right;
            }
            else if (val < cur->val) {
                cur = cur->left;
            }
        }
        return nullptr;
    }
};





//938. 二叉搜索树的范围和
//思路：把中序遍历弄出来就行
class Solution {
private:
    vector<int>arr;
    void dfs(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left);
        arr.push_back(root->val);
        dfs(root->right);
    }
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        dfs(root);
        int sum = 0;
        //遍历数组
        for (auto e : arr) {
            if (e >= low && e <= high) {
                sum += e;
            }
        }
        return sum;
    }
};


//501. 二叉搜索树中的众数
//思路：用哈希表记录一下出现频率就行
class Solution {
private:
    unordered_map<int, int>map;
    void dfs(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left);
        map[root->val]++;
        dfs(root->right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        vector<int>ret;
        int max_value = 0;
        dfs(root);
        unordered_map<int, int>::iterator it = map.begin();
        while (it != map.end()) {
            if (it->second > max_value) {
                max_value = it->second;
                ret.clear();
                ret.push_back(it->first);
            }
            else if (it->second == max_value) {
                ret.push_back(it->first);
            }
            it++;
        }
        return ret;
    }
};




//1008. 前序遍历构造二叉搜索树
//其实就是写一个insert
class Solution {
private:
    bool insert(TreeNode*& root, int val) {
        if (root == nullptr) {
            root = new TreeNode(val);
            return true;
        }
        //找插入的位置
        TreeNode* parent = nullptr;
        TreeNode* cur = root;
        while (cur) {
            if (val > cur->val) {
                parent = cur;
                cur = cur->right;
            }
            else if (val < cur->val) {
                parent = cur;
                cur = cur->left;
            }
            else {
                return false;
            }
        }
        //现在已经找到插入的位置了
        //此时cur为空
        cur = new TreeNode(val);
        if (parent->val > val) {
            parent->left = cur;
        }
        else {
            parent->right = cur;
        }
        return true;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode* root = nullptr;
        for (auto e : preorder) {
            insert(root, e);
        }
        return root;
    }
};