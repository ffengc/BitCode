#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

//队列实现栈
class MyStack {
public:
    queue<int>que;
    MyStack() {

    }

    void push(int x) {
        que.push(x);
    }

    int pop() {
        int size = que.size();
        size--;
        while (size--) {
            que.push(que.front());
            que.pop();
        }
        int ret = que.front();
        que.pop();
        return ret;
    }

    int top() {
        return que.back();//栈头就是队尾底
    }

    bool empty() {
        return que.empty();
    }
};





//循环队列
//链表的实现方式
//head==NULL是满也是空
//所以用一个size记录可以，开一个节点不存储数据也可已解决这个问题
//加数据：tail=tail->next;
//出数据：head=head->next;

//使用数组的方式实现
//head tail是下标
//加数据：tail++;
//出数据：head++;
//下标超数组的范围的时候，绕回来，取模是一种方式
//如果tail+1==head就满了
//这种方式的话取尾比较简单，但是注意边界问题
#if 1
typedef struct {
    int* a;//数组
    int k;
    int head;
    int tail;
} MyCircularQueue;

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    //注意tail在数组最后，head在最前的特殊情况
    int next = obj->tail + 1;
    if (next == obj->k + 1) {
        next = 0;
    }
    return next == obj->head;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->head == obj->tail;
}

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));//先搞一个节点出来
    obj->a = (int*)malloc(sizeof(int) * (k + 1));//多开一个空间
    obj->head = obj->tail = 0;//这里head tail是下标
    obj->k = k;
    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj))return false;
    obj->a[obj->tail] = value;//在tail的位置放val
    obj->tail++;
    //但是要控制边界
    if (obj->tail == obj->k + 1) {
        obj->tail = 0;//把下标绕回来
    }
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))return false;
    ++obj->head;
    if (obj->head == obj->k + 1) {
        obj->head = 0;
    }
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))return -1;
    return obj->a[obj->head];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))return -1;
    int prev = obj->tail - 1;
    if (obj->tail == 0) {
        prev = obj->k;
    }
    return obj->a[prev];
}

void myCircularQueueFree(MyCircularQueue* obj) {
    //先free数组
    //再free循环队列
    free(obj->a);
    free(obj);
}
#endif

/*
* 现有一循环队列，其队头指针尾front，队尾指针尾rear；循环队列长度尾N，实际最多存储N-1个数据。
* 其队内有效长度为：
* (rear-front+N)%N
*/