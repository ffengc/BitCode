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



#if 0
//1609. 奇偶树
class Solution {
private:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*>node_q;
        if (root == nullptr)return{  };
        vector<vector<int>>ret;
        node_q.push(root);
        while (!node_q.empty()) {
            int curLevelSize = node_q.size();
            ret.push_back(vector<int>());//先加入一个空的vector
            for (int i = 0; i < curLevelSize; i++) {
                TreeNode* node = node_q.front();
                node_q.pop();
                ret.back().push_back(node->val);
                if (node->left)node_q.push(node->left);
                if (node->right)node_q.push(node->right);
            }
        }
        return ret;
    }
    inline bool is_odd(int x) {
        return x % 2 == 1;
    }
    inline bool is_increasing(vector<int>arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] <= arr[i - 1])return false;
        }
        return true;
    }
    inline bool is_decreasing(vector<int>arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] >= arr[i - 1])return false;
        }
        return true;
    }
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<vector<int>>level = levelOrder(root);
        for (int i = 0; i < level.size(); i++) {
            for (int j = 0; j < level[i].size(); j++) {
                if (!is_odd(i)) {
                    //偶数行
                    if (!is_odd(level[i][j]))return false;
                    if (!is_increasing(level[i]))return false;
                }
                else {
                    //奇数行
                    if (is_odd(level[i][j]))return false;
                    if (!is_decreasing(level[i]))return false;
                }
            }
        }
        return true;
    }
};



//2415. 反转二叉树的奇数层
//先用bfs得到每一层的指针
class Solution {
private:
    vector<vector<TreeNode*>> levelOrder(TreeNode* root) {
        queue<TreeNode*>node_q;
        if (root == nullptr)return{  };
        vector<vector<TreeNode*>>ret;
        node_q.push(root);
        while (!node_q.empty()) {
            int curLevelSize = node_q.size();
            ret.push_back(vector<TreeNode*>());//先加入一个空的vector
            for (int i = 0; i < curLevelSize; i++) {
                TreeNode* node = node_q.front();
                node_q.pop();
                ret.back().push_back(node);
                if (node->left)node_q.push(node->left);
                if (node->right)node_q.push(node->right);
            }
        }
        return ret;
    }
protected:
    void reverse_val_in_TreeNodes(vector<TreeNode*>arr) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            swap(arr[left]->val, arr[right]->val);
            left++;
            right--;
        }
    }
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (root == nullptr)return nullptr;
        vector<vector<TreeNode*>>node_arr = levelOrder(root);
        if (node_arr.size() <= 1)return root;
        //开始反转奇数层
        for (int i = 1; i < node_arr.size(); i += 2) {
            reverse_val_in_TreeNodes(node_arr[i]);
        }
        return root;
    }
};

//429. N 叉树的层序遍历
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*>q;
        auto ret = vector<vector<int>>();
        if (!root)return ret;
        q.push(root);
        int level_size = 1;
        while (!q.empty()) {
            vector<int>path;
            for (size_t i = 0; i < level_size; i++) {
                Node* front = q.front();
                q.pop();
                path.push_back(front->val);
                for (int i = 0; i < front->children.size(); i++) {
                    if (front->children[i]) {
                        q.push(front->children[i]);
                    }
                }
            }
            ret.push_back(path);
            level_size = q.size();
        }
        return ret;
    }
};
#endif

//599. 两个列表的最小索引总和
//还未通过 -- 找不到原因
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string>ret;
        //初始化哈希
        unordered_map<string, int>map;
        int min_idx_sum = 1000;
        for (int i = 0; i < list1.size(); i++) {
            map[list1[i]] = i;//<name,index>
        }
        //遍历list2
        for (int i = 0; i < list2.size(); i++) {
            unordered_map<string, int>::iterator pos = map.find(list2[i]);
            if (pos != map.end()) {
                //说明找到了
                int idx_sum = i + pos->second;
                if (idx_sum < min_idx_sum) {
                    min_idx_sum = idx_sum;
                    ret.clear();
                    ret.push_back(pos->first);
                }
                else if (idx_sum == min_idx_sum) {
                    ret.push_back(pos->first);
                }
            }
        }
        return ret;
    }
};
int main(){
    vector<string>s1 = { "Shogun", "Tapioca Express", "Burger King", "KFC" };
    vector<string>s2 = { "Piatti", "The Grill at Torrey Pines",
        "Hungry Hunter Steakhouse", "Shogun" };
    Solution().findRestaurant(s1, s2);
    return 0;
}
