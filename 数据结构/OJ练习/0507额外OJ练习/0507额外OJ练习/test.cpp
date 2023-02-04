#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<string>

using namespace std;

#if 1
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

//92. 反转链表 II
class Solution {
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* newhead = NULL;
        ListNode* cur = head;
        while (cur) {
            ListNode* next = cur->next;
            //头插
            cur->next = newhead;
            newhead = cur;
            cur = next;
        }
        return newhead;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* start = head;
        ListNode* end = head;
        ListNode* prev = NULL;
        left--;//第二个位置，走一步就行了
        right--;
        while (left-- && start) {
            prev = start;
            start = start->next;
        }
        while (right-- && end) {
            end = end->next;
        }
        ListNode* cont = end->next;//等一下链接到cont上
        end->next = NULL;
        ListNode* newhead = reverseList(start);
        if (prev) {
            prev->next = newhead;
        }
        else {
            head = newhead;
        }
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = cont;
        return head;
    }
};












//82. 删除排序链表中的重复元素 II
//细节特别的多，都是一步一步调出来的
//如果用一个哨兵位头节点，会简单很多，这里我的方法没有用
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL)return head;
        while (head) {
            if (head->next == NULL)break;
            if (head->val != head->next->val)break;
            ListNode* realhead = head;
            while (realhead && realhead->next && realhead->val == realhead->next->val) {
                realhead = realhead->next;
            }
            if (realhead != head) {
                head = realhead->next;
            }
        }
        if (head == NULL)return NULL;
        ListNode* cur = head->next;
        ListNode* prev = head;
        ListNode* prevPrev = NULL;
        while (cur) {
            if (cur->val == prev->val) {
                while (cur && cur->val == prev->val) {
                    cur = cur->next;
                }
                if (cur) {
                    prevPrev->next = cur;
                    prev = cur;
                    cur = cur->next;
                }
                else {
                    prevPrev->next = NULL;
                }
            }
            else {
                prevPrev = prev;
                prev = cur;
                cur = cur->next;
            }
        }
        return head;
    }
};


#endif





//796. 旋转字符串
bool rotateString(char* s, char* goal) {
    if (strlen(s) != strlen(goal))return false;//注意这个情况
    int len = strlen(s);
    char tmp[1000] = { 0 };
    strcpy(tmp, s);
    strncat(tmp, tmp, len);
    char* p = strstr(tmp, goal);
    if (p == NULL) {
        return false;
    }
    else return true;
}
int main() {
    char str1[] = "abcdef";
    char str2[] = "cdefab";
    bool ret = rotateString(str1, str2);
    return 0;
}




//1019. 链表中的下一个更大节点
//这个是很无脑的暴力法
class Solution {
private:
    int find_maxInList(ListNode* begin) {
        if (begin == NULL) {
            return INT_MIN;
        }
        int target = begin->val;
        ListNode* cur = begin->next;
        while (cur) {
            if (cur->val > target) {
                return cur->val;
            }
            cur = cur->next;
        }
        return INT_MIN;
    }
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int>ret;
        ListNode* cur = head;
        while (cur) {
            int num = find_maxInList(cur);
            if (num != INT_MIN) {
                ret.push_back(num);
            }
            else {
                ret.push_back(0);
            }
            cur = cur->next;
        }

        return ret;
    }
};