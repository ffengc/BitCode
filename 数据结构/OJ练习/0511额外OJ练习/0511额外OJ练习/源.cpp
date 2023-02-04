#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<string>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//234. 回文链表
class Solution {
private:
    struct ListNode* reverseList(struct ListNode* head) {
        struct ListNode* newhead = NULL;
        struct ListNode* cur = head;
        while (cur) {
            struct ListNode* next = cur->next;
            //头插
            cur->next = newhead;
            newhead = cur;
            cur = next;
        }
        return newhead;
    }
public:
    bool isPalindrome(ListNode* head) {
        if (head == NULL)return true;//这个记得判断一下
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* slowPrev = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slowPrev = slow;
            slow = slow->next;
        }
        slowPrev->next = NULL;
        ListNode* head2 = reverseList(slow);
        ListNode* cur1 = head;
        ListNode* cur2 = head2;
        while (cur1 && cur2) {
            if (cur1->val != cur2->val) {
                return false;
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        if (cur1) {
            if (cur1->next != NULL)return false;
        }
        if (cur2) {
            if (cur2->next != NULL)return false;
        }
        return true;
    }
};


//2181. 合并零之间的节点
//看看能不能优化，不要vector
//效率已经很高了，看看空间能不能优化
class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        if (head == NULL)return NULL;
        vector<int>arr;
        ListNode* cur = head;
        while (cur) {
            while (cur && cur->val == 0) {
                cur = cur->next;
            }
            if (cur == NULL)break;
            //此时cur指向的节点已经不是0了
            int sum = 0;
            while (cur->val != 0) {
                sum += cur->val;
                cur = cur->next;
            }
            arr.push_back(sum);
        }
        //此时把arr里面的数字都放进去
        cur = head;
        for (int i = 0; i < arr.size(); i++) {
            cur->val = arr[i];
            if (i != arr.size() - 1)cur = cur->next;
        }
        cur->next = NULL;
        return head;
    }
};




#include<unordered_set>
int main() {
    unordered_set<int, int>hash;
    return 0;
}