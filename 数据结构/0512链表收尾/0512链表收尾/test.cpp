#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<list>
using namespace std;

//剑指 Offer 35. 复杂链表的复制
class Node {
public:
    int val;
    Node* next;
    Node* random;//有一个随机指针的
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution {
public:
    Node* copyRandomList(Node* head) {
        //1.把拷贝节点放到后面
        Node* cur = head;
        while (cur) {
            Node* copy = (Node*)malloc(sizeof(Node));
            copy->val = cur->val;
            copy->next = cur->next;
            cur->next = copy;

            cur = cur->next->next;//迭代
        }
        //2.连接起来
        cur = head;
        while (cur) {
            Node* copy = cur->next;
            //建立关系
            if (cur->random == NULL) {
                copy->random = NULL;
            }
            else {
                copy->random = cur->random->next;
            }
            cur = copy->next;
        }
        //3.断开连接
        //这里是用尾插的方式，不用这种方式也可以的
        cur = head;
        Node* copyhead = NULL;
        Node* copytail = NULL;
        while (cur) {
            Node* copy = cur->next;
            Node* next = copy->next;

            if (copytail == NULL) {
                copyhead = copytail = copy;
            }
            else {
                copytail->next = copy;
                copytail = copytail->next;
            }
            cur->next = next;
            cur = next;
        }
        return copyhead;
    }
};



//二叉搜索树-红黑树-优点-查找快！
#include<map>
#include<set>
//哈希表-查找快
#include<unordered_map>
#include<unordered_set>
//顺序表
#include<vector>
//字符串-也是顺序表
#include<string>
//单链表
#include<forward_list>
//双链表
#include<list>
int main() {
    forward_list<int>list2;
    list2.push_front(1);
    list2.push_front(2);
    list2.push_front(3);
    list2.push_front(4);

    return 0;
}