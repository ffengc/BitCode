#pragma once


struct QueueNode {
	QueueNode* next;
	int val;
};
class Queue {
public:
	void Init();
	void Push(int x);
	void Pop();
private:
	QueueNode* head;
	QueueNode* tail;
};