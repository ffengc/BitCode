#define _CRT_SECURE_NO_WARNINGS 1

#include"Queue.h"

void _QueueInit(Queue* pq) {
	assert(pq);
	pq->head = pq->tail = nullptr;
}
void _QueueDestroy(Queue* pq) {
	assert(pq);
	QNode* cur = pq->head;
	while (cur) {
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = nullptr;
}
void _QueuePush(Queue* pq, QDataType x) {
	assert(pq);
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == nullptr) {
		perror("_QueuePush::malloc");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = nullptr;
	if (pq->tail == nullptr) {
		//如果是空队列的情况
		pq->head = pq->tail = newnode;
	}
	else {
		//队列非空
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}
void _QueuePop(Queue* pq) {
	//头删-保存下一个 free掉头，很简单
	//当然要判空
	assert(pq);
	assert(!_QueueEmpty(pq));
	//如果只有一个节点要单独分析一下
	if (pq->head->next == nullptr) {
		//如果只有一个节点，删完之后两个指针都要置空
		free(pq->head);
		pq->head = pq->tail = nullptr;
	}
	else {
		//记录新头
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}
QDataType _QueueFront(Queue* pq) {
	//取队头数据
	assert(pq);
	assert(!_QueueEmpty(pq));
	return pq->head->data;
}
QDataType _QueueBack(Queue* pq) {
	assert(pq);
	assert(!_QueueEmpty(pq));
	return pq->tail->data;
}
bool _QueueEmpty(Queue* pq) {
	assert(pq);
	return pq->head == nullptr;
}
int _QueueSize(Queue* pq) {
	//如果想提高效率，可以在结构体里面弄一个size可以是O(1)

	//遍历
	//O(n)
	assert(pq);
	QNode* cur = pq->head;
	size_t cnt = 0;
	while (cur) {
		cnt++;
		cur = cur->next;
	}
	return cnt;
}