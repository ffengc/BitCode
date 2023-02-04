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


//445. 两数相加 II
//这个题是真的复杂，试了很多次，要考虑很多问题
//总体思路是
//先求出长度，然后对齐每一位
//push进一个vector里面
//调整vector里面的数字
//最高位不管先，放进链表里面再管
//最后因为怕链表不够长，先把两个链表连在一起先
//再一个一个放进去
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int>arr;
        int len1 = 0;
        int len2 = 0;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        //求长度
        while (cur1) {
            cur1 = cur1->next;
            len1++;
        }
        while (cur2) {
            cur2 = cur2->next;
            len2++;
        }
        //cur1，2可以继续用
        cur1 = l1;
        cur2 = l2;
        //调整指针，先把不用相加的push进去，让指针对齐
        if (len1 > len2) {
            int k = len1 - len2;
            while (k-- && cur1) {
                arr.push_back(cur1->val);
                cur1 = cur1->next;
            }
        }
        else {
            int k = len2 - len1;
            while (k-- && cur2) {
                arr.push_back(cur2->val);
                cur2 = cur2->next;
            }
        }
        //两个指针同时跑
        while (cur1 && cur2) {
            arr.push_back(cur1->val + cur2->val);
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        //操作arr数组
        int i = 0;//迭代数组
        for (int i = 1; i < arr.size(); i++) {
            int x = i;
            //为什么要用while，因为，可能有连续进位
            //用一个x好，不能影响数组迭代的i
            while (x > 0 && arr[x] >= 10) {//这里是>0不是>=0，否则--的时候数组会越界
                arr[x] -= 10;
                arr[x - 1]++;
                x--;
            }
        }
        //放进链表里
        //先把两个链表连起来先
        ListNode* tail = l1;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = l2;
        //再把tail拿回来操作链表
        tail = l1;
        int j = 0;
        ListNode* prev = tail;
        while (tail && j < arr.size()) {
            if (tail == l1 && arr[0] >= 10) {//如果第一个位置的vector大于等于10，说明要安排多一个节点
                //所以直接一个给1，下一个给arr[0]-10,因为arr[0]是没有被调整的
                tail->val -= 10;
                tail->val = 1;
                tail->next->val = arr[0] -= 10;
                prev = tail->next;
                tail = tail->next->next;
                j++;
                //j用于控制数组
                //tial用于控制链表
            }
            else {
                tail->val = arr[j];
                prev = tail;
                tail = tail->next;
                j++;
            }
        }
        //最后不要忘了，最后一个节点->next置空
        //所以需要一个prev，不要也可以
        //遍历到数组最后一个元素的时候，链表指针tail不要走了
        //这样不要prev也可以
        prev->next = NULL;
        return l1;
    }
};




//25. K 个一组翻转链表
//困难的题，提交一次过啦哈哈哈哈哈哈哈哈哈哈！
//用了一个哨兵位的头节点！
class Solution {
private:
    struct ListNode* reverseList(struct ListNode* head) {
        //快慢指针
        //调换指针序列
        if (head == NULL)return NULL;
        struct ListNode* prev = NULL;
        struct ListNode* cur = head;
        struct ListNode* next = head->next;
        while (next) {
            cur->next = prev;
            prev = cur;
            cur = next;
            next = cur->next;
        }
        cur->next = prev;
        return cur;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        //定义一个哨兵先
        ListNode* newhead = (ListNode*)malloc(sizeof(ListNode));
        newhead->next = head;
        ListNode* tail = newhead;
        ListNode* cur = tail;
        while (cur) {
            for (int i = 0; i < k && cur; i++) {
                cur = cur->next;
            }
            if (cur == NULL)break;
            ListNode* tmp = cur;
            cur = cur->next;
            tmp->next = NULL;
            ListNode* _new = reverseList(tail->next);
            tail->next = _new;
            //找尾
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = cur;
            cur = tail;
        }
        return newhead->next;
    }
};


//面试题 02.03. 删除中间节点
class Solution {
public:
    void deleteNode(ListNode* node) {
        //可以把下一个赋值过来，再把下一个删掉就行了
        node->val = node->next->val;
        node->next = node->next->next;
    }
};


//2. 两数相加
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //因为数字是逆置的，所以其实不用搞vector来存也可以，直接加就行了，但是两条表还是要连起来，否则不够长
        vector<int>arr;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        while (cur1 && cur2) {
            arr.push_back(cur1->val + cur2->val);
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        while (cur1) {
            arr.push_back(cur1->val);
            cur1 = cur1->next;
        }
        while (cur2) {
            arr.push_back(cur2->val);
            cur2 = cur2->next;
        }
        //调整vector的数值
        for (int i = 0; i < arr.size() - 1; i++) {
            if (arr[i] >= 10) {
                arr[i] -= 10;
                arr[i + 1]++;
            }
        }
        if (arr[arr.size() - 1] >= 10) {
            arr[arr.size() - 1] -= 10;
            arr.push_back(1);
        }
        //将两个链表链接起来
        cur1 = l1;
        while (cur1->next) {
            cur1 = cur1->next;
        }
        cur1->next = l2;
        cur1 = l1;
        //放进去
        int j = 0;
        ListNode* prev = l1;
        while (cur1 && j < arr.size()) {
            cur1->val = arr[j];
            j++;
            prev = cur1;
            cur1 = cur1->next;
        }
        prev->next = NULL;
        return l1;

    }
};


//328. 奇偶链表
//自己写的超时了，好像是O(n)的，不知道为什么超时了
//自己写的
//不知道答案对不对，一直显示超时
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        //必须要多余两个节点才行
        if (head == NULL || head->next == NULL)return head;
        ListNode* head2 = head->next;
        ListNode* tail = head2;
        ListNode* prev = head;
        ListNode* cur = head->next;
        while (cur && cur->next) {
            tail->next = cur;
            prev->next = cur->next;
            tail = tail->next;
            cur = cur->next->next;
        }
        tail->next = NULL;
        //找奇数节点的尾
        ListNode* odd = head;
        while (odd->next) {
            odd = odd->next;
        }
        odd->next = head2;
        return head;
    }
};

//题解
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode* evenHead = head->next;
        ListNode* odd = head;
        ListNode* even = evenHead;
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};