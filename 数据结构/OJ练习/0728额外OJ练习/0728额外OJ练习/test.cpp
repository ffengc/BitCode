#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cassert>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    //这三个都是构造函数，相互重载
    Node() {}
    Node(int _val) {
        val = _val;
        next = NULL;
    }
    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

//剑指 Offer II 029. 排序的循环链表
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        //先把新的节点创建好
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = nullptr;
        newNode->val = insertVal;
        //如果节点为空
        if (head == nullptr) {
            head = newNode;
            newNode->next = newNode;
            return newNode;
        }
        //如果只有一个节点
        if (head->next == head) {
            head->next = newNode;
            newNode->next = head;
            return head;
        }
        //不止一个节点
        //先把真正的head找到 -- 即调整一下head的位置
        Node* cur = head->next;
        Node* prev = head;
        //还是要把realhead找出来，不然[3,3,3],0等情况处理不了
        int cnt = 0;//记录现在是否是第一圈
        while (1) {
            if (cur->next->val >= cur->val && prev->val > cur->val)break;
            if (cur == head && cnt != 0)break;
            prev = cur;
            cur = cur->next;
            cnt++;
        }
        cnt = 0;//记录现在是否是第一圈
        Node* realHead = cur;
        while (1) {
            if (cur->val >= insertVal && prev->val <= insertVal)break;
            if (cur == realHead && cnt != 0)break;//代表绕了一圈了
            prev = cur;
            cur = cur->next;
            ++cnt;
        }
        //此时新节点应该插入在prev和cur之间
        prev->next = newNode;
        newNode->next = cur;
        return head;
    }
};