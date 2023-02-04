#define _CRT_SECURE_NO_WARNINGS 1

#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<cassert>
using namespace std;

typedef int BTDataType;
typedef struct BinaryTreeNode {
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
	BTDataType data;
}BTNode;

BTNode* BuyNode(BTDataType x) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	assert(node);
	node->data = x;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}
BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);
	BTNode* node7 = BuyNode(7);

	node1->_left = node2;
	node1->_right = node4;
	node2->_left = node3;
	node4->_left = node5;
	node4->_right = node6;
	node3->_right = node7;
	return node1;
}

//二叉树的销毁
//后序销毁最好
//见0522二叉树


//bfs层序遍历
//见0522二叉树
void LevelOrder(BTNode* root) {
	//借助队列
	//思路
	//第一层进去，每层出队列带下一层入队列
	std::queue<BTNode*>q;
	if (root) {
		//如果节点不为空
		q.push(root);
	}
	while (!q.empty()) {
		//如果队列不为空
		BTNode* front = q.front();
		std::cout << front->data << " ";
		q.pop();
		if (front->_left) {
			q.push(front->_left);
		}
		if (front->_right) {
			q.push(front->_right);
		}
	}
	std::cout << std::endl;
}



//判断一棵二叉树是不是完全二叉树
//可以用层序遍历，把空也入到队列里面，如果空后面还有非空，就不是完全二叉树
bool TreeComplete(BTNode* root) {
	queue<BTNode*>q;
	if (root) {
		//如果节点不为空
		q.push(root);
	}
	while (!q.empty()) {
		//如果队列不为空
		BTNode* front = q.front();
		q.pop();
		if (front->_left == nullptr);
		if (front) {
			q.push(front->_left);
			q.push(front->_right);
		}
		else {
			//此时遇到空了-跳出
			break;
		}
	}
	//如果后面全是空，则是完全二叉树，如果还有非空，就不是完全二叉树
	while (!q.empty()) {
		BTNode* front = q.front();
		q.pop();
		if (front)return false;
	}
	return true;
}


int main() {
	BTNode* root;
	root = CreatBinaryTree();

	LevelOrder(root);
	printf("TreeComplete:%d\n", TreeComplete(root));
	return 0;
}