#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<cassert>
#include<queue>

using namespace std;

//707. 设计链表
class MyListNode {
public:
    MyListNode* next;
    int val;
    MyListNode() :next(0), val(0) {}
};
class MyLinkedList {
private:
    MyListNode* head;
public:
    //弄一个带头的比较舒服一点 
    MyLinkedList()
        :head(nullptr)
    {
        head = (MyListNode*)malloc(sizeof(MyListNode));
        head->next = nullptr;
    }

    int get(int index) {
        if (index < 0)return -1;
        MyListNode* cur = head->next;
        while (cur && index--) {
            cur = cur->next;
        }
        if (!cur)return -1;
        return cur->val;
    }
    //头插
    void addAtHead(int val) {
        MyListNode* newNode = (MyListNode*)malloc(sizeof(MyListNode));
        newNode->val = val;
        assert(newNode);
        newNode->next = head->next;
        head->next = newNode;
    }
    //尾插
    void addAtTail(int val) {
        //找尾
        MyListNode* cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        //此时cur->next==nullptr
        MyListNode* newNode = (MyListNode*)malloc(sizeof(MyListNode));
        assert(newNode);
        newNode->val = val;
        cur->next = newNode;
        newNode->next = nullptr;
    }

    void addAtIndex(int index, int val) {
        if (index < 0) {
            addAtHead(val);
            return;
        }
        //第index个节点前
        // 头-1-2-3-4-5-6
        MyListNode* newNode = (MyListNode*)malloc(sizeof(MyListNode));
        newNode->next = nullptr;
        newNode->val = val;
        assert(newNode);
        MyListNode* cur = head->next;
        MyListNode* prev = head;
        while (cur && index--) {
            prev = cur;
            cur = cur->next;
        }
        if (!cur && index > 0)return;
        //此时newNode就要插入在prev和cur之间
        newNode->next = cur;
        prev->next = newNode;
    }

    void deleteAtIndex(int index) {
        if (index < 0)return;
        MyListNode* cur = head->next;
        //1 2 3
        MyListNode* prev = head;
        while (cur && index--) {
            prev = cur;
            cur = cur->next;
        }
        if (index > 0)return;
        //此时cur就是要删除的节点
        if (cur)prev->next = cur->next;
        else prev->next = nullptr;
        free(cur);
    }
};
int main() {
    MyLinkedList list;
    list.addAtHead(1);
    list.addAtTail(3);
    list.addAtIndex(1, 2);
    list.get(1);
    list.deleteAtIndex(1);
    list.get(1);
    return 0;
}

/*
["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
[[],[1],[3],[1,2],[1],[1],[1]]
*/


//933. 最近的请求次数
/*
我们可以用一个队列维护发生请求的时间，当在时间 tt 收到请求时，将时间 tt 入队。

由于每次收到的请求的时间都比之前的大，因此从队首到队尾的时间值是单调递增的。当在时间 tt 收到请求时，为了求出 [t-3000,t][t−3000,t] 内发生的请求数，我们可以不断从队首弹出早于 t-3000t−3000 的时间。循环结束后队列的长度就是 [t-3000,t][t−3000,t] 内发生的请求数。

作者：LeetCode-Solution
链接：https://leetcode.cn/problems/number-of-recent-calls/solution/zui-jin-de-qing-qiu-ci-shu-by-leetcode-s-ncm1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class RecentCounter {
    queue<int> q;
public:
    RecentCounter() {}
    int ping(int t) {
        q.push(t);
        while (q.front() < t - 3000) {
            q.pop();
        }
        return q.size();
    }
};