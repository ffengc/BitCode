#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#if 0

//1486. 数组异或操作
class Solution {
public:
    int xorOperation(int n, int start) {
        vector<int>arr;
        for (int i = 0; i < n; i++) {
            arr.push_back(start + 2 * i);
        }
        int ret = 0;
        for (int i = 0; i < n; i++) {
            ret ^= arr[i];
        }
        return ret;
    }
};


//1290. 二进制链表转整数
class Solution {
private:
    struct ListNode* reverseList(struct ListNode* head) {
        struct ListNode* newhead = NULL;
        if (head == NULL) {
            return head;
        }
        struct ListNode* cur = head;
        struct ListNode* next = head->next;
        while (cur != NULL) {
            cur->next = newhead;
            newhead = cur;
            cur = next;
            if (cur != NULL) {
                next = cur->next;
            }
        }
        return newhead;
    }
public:
    int getDecimalValue(ListNode* head) {
        head = reverseList(head);
        long long ret = 0;
        for (int i = 0; head; i++) {
            ret += pow(2, i) * (head->val);
            head = head->next;
        }
        return ret;
    }
};


//258. 各位相加
class Solution {
private:
    int _add(int num) {
        int ans = 0;
        while (num) {
            ans += num % 10;
            num /= 10;
        }
        return ans;
    }
public:
    int addDigits(int num) {
        while (num / 10 != 0) {
            num = _add(num);
        }
        return num;
    }
};

#endif

// 2074. 反转偶数长度组的节点
class Solution {
private:
    struct ListNode* reverseList(struct ListNode* head) {
        struct ListNode* newhead = NULL;
        if (head == NULL) {
            return head;
        }
        struct ListNode* cur = head;
        struct ListNode* next = head->next;
        while (cur != NULL) {
            cur->next = newhead;
            newhead = cur;
            cur = next;
            if (cur != NULL) {
                next = cur->next;
            }
        }
        return newhead;
    }
public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        if (head == NULL || head->next == NULL)return head;
        ListNode* slow_prev = head;
        ListNode* fast_prev = head;
        ListNode* fast = head;
        ListNode* slow = head;
        for (int i = 1;; i++) {
            int i_tmp = i;
            while (i_tmp && fast) {
                fast_prev = fast;
                fast = fast->next;
                i_tmp--;//这个一定要放在里面，否则就减多一次了！
            }
            if ((i - i_tmp) % 2 == 0) {
                //反转链表
                fast_prev->next = NULL;
                slow_prev->next = reverseList(slow);
                //找尾
                while (slow_prev->next) {
                    slow_prev = slow_prev->next;
                }
                slow_prev->next = fast;
                slow = fast;
                fast_prev = slow_prev;
            }
            else {
                slow_prev = fast_prev;
                slow = fast;
            }
            if (fast == NULL)break;
        }
        return head;
    }
};


ListNode* _CreatListNode(int x);
void ListPushBack(ListNode** pphead, int x);
int main() {
    //[5,2,6,3,9,1,7,3,8,4]
    Solution su;
    ListNode* head = NULL;
    ListPushBack(&head, 5);
    ListPushBack(&head, 2);
    ListPushBack(&head, 6);
    ListPushBack(&head, 3);
    ListPushBack(&head, 9);
    ListPushBack(&head, 1);
    ListPushBack(&head, 7);
    ListPushBack(&head, 3);
    ListPushBack(&head, 8);
    ListPushBack(&head, 4);
    ListNode* ret = su.reverseEvenLengthGroups(head);
    return 0;
}

ListNode* _CreatListNode(int x) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

void ListPushBack(ListNode** pphead, int x) {
    ListNode* newNode = _CreatListNode(x);
    //空链表的情况
    if (*pphead == NULL) {
        *pphead = newNode;
    }
    else {
        //找尾
        ListNode* tail = *pphead;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}


//520. 检测大写字母
class Solution {
public:
    bool detectCapitalUse(string word) {
        if (isupper(word[0])) {
            if (isupper(word[1])) {
                for (int i = 2; i < word.size(); i++) {
                    if (islower(word[i]))return false;
                }
            }
            else {
                for (int i = 2; i < word.size(); i++) {
                    if (isupper(word[i]))return false;
                }
            }
        }
        else {
            for (int i = 0; i < word.size(); i++) {
                if (isupper(word[i]))return false;
            }
        }
        return true;
    }
};