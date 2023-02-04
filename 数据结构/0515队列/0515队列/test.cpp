#define _CRT_SECURE_NO_WARNINGS 1

#include"Queue.h"

//入队Enqueue
//出队Dequeue

void _test() {
	Queue q;
	_QueueInit(&q);
	_QueuePush(&q, 1);
	_QueuePush(&q, 2);
	_QueuePush(&q, 3);
	_QueuePush(&q, 4);
	_QueuePush(&q, 5);

	while (!(_QueueEmpty(&q))) {
		printf("%d ", _QueueFront(&q));
		_QueuePop(&q);
	}
	printf("\n");
	//队列和栈不一样，只要我入的是12345，无论什么时候出都是12345

	//1.排队，保持绝对公平性
	//2.广度优先遍历
}
int main() {
	_test();
	return 0;
}