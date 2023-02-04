#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stack>

struct ListNode {
	int val;
	struct ListNode* next;
	ListNode(int x) :val(x), next(NULL) {}
};



//OJ142 找入环口
class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				//相遇
				ListNode* meet = slow;

				//这个是从数学公式推导出来的
				while (meet != head) {
					//一个从head开始走
					//一个从meet开始走
					meet = meet->next;
					head = head->next;
				}
				return meet;
			}
		}
		return NULL;
	}
};


//断开转化成相交链表问题也是可以的
class Solution {
private:
    struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
        if (headA == NULL) {
            return headB;
        }
        if (headB == NULL) {
            return headA;
        }
        struct ListNode* cur1 = headA;
        struct ListNode* cur2 = headB;
        struct ListNode* curA = headA;
        struct ListNode* curB = headB;
        int la = 0;
        int lb = 0;
        while (cur1) {
            la++;
            cur1 = cur1->next;
        }
        while (cur2) {
            lb++;
            cur2 = cur2->next;
        }
        if (lb > la) {
            for (int i = 0; i < lb - la; i++) {
                curB = curB->next;
            }
        }
        else {
            for (int i = 0; i < la - lb; i++) {
                curA = curA->next;
            }
        }
        //光有下面是不行的，因为两个链表长度不一定一样，所以可以先把La，Lb求出来，让长的先走差值
        while (curA) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                fast = fast->next;
                slow->next = NULL;
                return getIntersectionNode(fast, head);
            }
        }
        return NULL;
    }
};