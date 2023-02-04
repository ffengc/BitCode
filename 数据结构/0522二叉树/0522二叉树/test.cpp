#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//普通的链式二叉树-增删查改没有意义
//如果有存储数据-不如用顺序表链表

//1.为了后面学习更复杂二叉树打基础
//     （搜索二叉树，AVL树，红黑树，B树等）-快速地搜索数据
//2.很多OJ都是在普通二叉树上

//主要学习遍历、控制结构


//遍历
//前中后序 DFS
//层序遍历 BFS

//前序遍历 根-左子树-右子树
//中序遍历 左子树-根-右子树
//后序遍历 左子树-右子树-根

typedef int BTDataType;
typedef struct BinaryTreeNode {
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
	BTDataType data;
}BTNode;

//先手搓一个二叉树出来，先别管增删查改
/*
*        1
*      2   4
*    3    5 6
*/
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
/*
*        1
*      2   4
*    3    5 6
      7
*/


//前序遍历
void PreOrder(BTNode* root);
//中序遍历
void InOrder(BTNode* root);
//后序遍历
void PostOrder(BTNode* root);
//二叉树大小
int TreeSize(BTNode* root);
int TreeSize_pro(BTNode* root);
//二叉树叶子节点的个数
int TreeLeafSize(BTNode* root);
//求第k层节点的个数
int TreeKLevel(BTNode* root, int k);
//求二叉树的深度
int TreeDepth(BTNode* root);
//查找二叉树中值为x的结点
BTNode* TreeFind(BTNode* root, BTDataType x);
//销毁二叉树
void TreeDestroy(BTNode* root);
//层序遍历
void LevelOrder(BTNode* root);


int count = 0;//二叉树大小全局变量
int main() {
	BTNode* root;
	root = CreatBinaryTree();

	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");

	count = 0;//每次调用之前都要置为0
	//printf("TreeSize:%d\n", TreeSize(root));

	printf("TreeSize:%d\n", TreeSize_pro(root));

	printf("TreeLeafSize:%d\n", TreeLeafSize(root));

	printf("TreeKLevel:%d\n", TreeKLevel(root, 1));
	printf("TreeKLevel:%d\n", TreeKLevel(root, 2));
	printf("TreeKLevel:%d\n", TreeKLevel(root, 3));

	printf("TreeFind:%d\n", TreeFind(root, 5)->data);

	printf("TreeDepth:%d\n", TreeDepth(root));

	LevelOrder(root);

	//销毁二叉树
	TreeDestroy(root);
	root = NULL;//因为传的是一级指针，所以在接口里面置空没用
	return 0;
}
//分治算法



//前序遍历
void PreOrder(BTNode* root) {
	//1 2 3 # # # 4 5 # # 6 # #
	if (root == NULL) {
		printf("# ");
		return;
	}
	printf("%d ", root->data);
	PreOrder(root->_left);
	PreOrder(root->_right);
}
//中序遍历
void InOrder(BTNode* root) {
	//# 3 # 2 # 1 # 5 # 4 # 6 #
	if (root == NULL) {
		printf("# ");
		return;
	}
	InOrder(root->_left);
	printf("%d ", root->data);
	InOrder(root->_right);
}
//后序遍历
void PostOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%d ", root->data);
}


//二叉树大小
//这个方法用全局变量其实是有缺陷的
//如果在操作系统，多线程的时候，count也会叠加起来
#if 0
int TreeSize(BTNode* root) {
	//遍历的思路
	if (root == NULL)return;
	++count;
	TreeSize(root->_left);
	TreeSize(root->_right);
	return count;
}
#endif
int TreeSize_pro(BTNode* root) {
	//分支的思路
	return root == NULL ? 0 : 
		TreeSize_pro(root->_left) + TreeSize_pro(root->_right) + 1;
}


//二叉树叶子节点的个数
int TreeLeafSize(BTNode* root) {
	if (root == NULL)return 0;
	if (root->_left == NULL && root->_right == NULL)return 1;
	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}


//求第k层节点的个数
int TreeKLevel(BTNode* root, int k) {
	//求左树的第k-1层+右树的k-1层
	assert(k >= 1);
	if (root == NULL)return 0;
	if (k == 1)return 1;
	//说明要继续遍历
	return TreeKLevel(root->_left, k - 1) + TreeKLevel(root->_right, k - 1);
}

//求二叉树的深度
int fmax(int a, int b) {
	return a > b ? a : b;
}
int TreeDepth(BTNode* root) {
	if (root == NULL)return 0;
	//return fmax(TreeDepth(root->_left), TreeDepth(root->_right)) + 1;//--这样也是对的
	int leftDepth = TreeDepth(root->_left);
	int rightDepth = TreeDepth(root->_right);
	return fmax(leftDepth, rightDepth) + 1;
}


//查找二叉树中值为x的结点
//这个要画栈帧图来想清楚
BTNode* TreeFind(BTNode* root, BTDataType x) {
	if (root == NULL)return NULL;
	if (root->data == x)return root;
	//下面是自己写的
	//if(root->_left)	return TreeFind(root->_left, x);
	//if (root->_right)return TreeFind(root->_right, x);

	BTNode* ret1 = TreeFind(root->_left, x);
	if (ret1)return ret1;
	BTNode* ret2 = TreeFind(root->_right, x);
	if (ret2)return ret2;

	return NULL;
}


//前序是最适合dfs的

//深度优先搜索 dfs  递归
//广度优先搜索 bfs  队列辅助完成


//销毁二叉树
void TreeDestroy(BTNode* root) {
	if (root == NULL)return;
	TreeDestroy(root->_left);
	TreeDestroy(root->_right);
	free(root);
}


#include<queue>
#include<iostream>
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
		//此处出队列
		std::cout << front->data << " ";
		q.pop();
		//把下一层带上来
		if (front->_left) {
			q.push(front->_left);
		}
		if (front->_right) {
			q.push(front->_right);
		}
	}
	std::cout << std::endl;
}