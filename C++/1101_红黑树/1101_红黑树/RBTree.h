#pragma once
//#include<map>
#include<iostream>
#include<assert.h>
using namespace std;


enum Colour {
	RED,BLACK
};
template<class K,class V>
struct __Red_Black_TreeNode {
	__Red_Black_TreeNode<K, V>* _left;
	__Red_Black_TreeNode<K, V>* _right;
	__Red_Black_TreeNode<K, V>* _parent;
	pair<K, V>_kv;
	Colour _col;
	__Red_Black_TreeNode(const pair<K, V>& kv)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv) {}
};


template<class K, class V>
struct RBTree {
	typedef __Red_Black_TreeNode<K, V>Node;
private:
	Node* _root = nullptr;
private:
	//左单旋
	void rotate_left(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}
		Node* ppNode = parent->_parent;//记录一下原先parent的parent
		subR->_left = parent;
		parent->_parent = subR;
		if (_root == parent) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			//如果ppNode==nullpt，是不会进来这里的
			if (ppNode->_left == parent) {
				ppNode->_left = subR;
			}
			else {
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}
	//右单旋
	void rotate_right(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR) {
			subLR->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (_root == parent) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			if (ppNode->_left == parent) {
				ppNode->_left = subL;
			}
			else {
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}
	void _inorder(Node* root) {
		if (root == nullptr)return;
		_inorder(root->_left);
		cout << root->_kv.first << endl;
		_inorder(root->_right);
	}
	bool prev_check(Node* root, int blackNum,int bench_mark) {
		if (root == nullptr) {
			if (blackNum != bench_mark)return false;
			return true;
		}
		if (root->_col == BLACK) {
			blackNum++;
		}
		if (root->_col == RED && root->_parent->_col == RED) {
			//存在连续的红节点，return false
			return false;
		}
		return prev_check(root->_left, blackNum, bench_mark) &&
			prev_check(root->_right, blackNum, bench_mark);
	}
public:
	bool is_balance() {
		if (_root == nullptr)return true;
		if (_root->_col == RED)return false;
		//黑色节点数量基准值
		int bench_mark = 0;
		Node* cur = _root;
		while (cur) {
			if (cur->_col == BLACK)++bench_mark;
			cur = cur->_left;
		}
		return prev_check(this->_root, 0, bench_mark);
	}
public:
	void inorder() {
		this->_inorder(this->_root);
		cout << "\n";
	}
	//前面插入的过程和搜索树一样的
	bool insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else return false;
		}
		cur = new Node(kv);
		cur->_col = RED;//一开始尽量先变红
		if (parent->_kv.first < kv.first) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED) {
			Node* grandparent = parent->_parent;
			assert(grandparent && grandparent->_col == BLACK);
			//关键看叔叔
			//判断一下左右
			if (parent == grandparent->_left) {
				Node* uncle = grandparent -> _right;
				//情况1（不看方向）
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					//继续向上处理
					cur = grandparent;
					parent = cur->_parent;
				}
				//情况2+3
				//uncle不存在/存在且为黑
				else {
					//情况2
					//   g
					//  p  u
					// c
					//右单旋+变色
					if (cur == parent->_left) {
						rotate_right(grandparent);
						parent->_col = BLACK;//父亲变黑
						grandparent->_col = RED;//祖父变红
					}
					//情况3
					//   g
					//  p  u
					//   c
					//左右双旋+变色
					else {
						rotate_left(parent);
						rotate_right(grandparent);
						//看着图写就行了
						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
			else {
				Node* uncle = grandparent->_left;
				//情况1（不看方向）
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					//继续向上处理
					cur = grandparent;
					parent = cur->_parent;
				}
				else {
					//情况2
					//   g
					//  u  p
					//      c 
					//左单旋+变色
					if (cur == parent->_right) {
						rotate_left(grandparent);
						parent->_col = BLACK;//父亲变黑
						grandparent->_col = RED;//祖父变红
					}
					//情况3
					//   g
					//  u  p
					//    c
					//右左双旋+变色
					else {
						rotate_right(parent);
						rotate_left(grandparent);
						//看着图写就行了
						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;//最后无论根是红是黑 -- 都处理成黑
		return true;
	}
};


void test1() {
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int>t1;
	for (auto e : a) {
		t1.insert(make_pair(e, e));
	}
	t1.inorder();
	cout << "is_balance():" << t1.is_balance() << endl;
}
void test2() {
	size_t N = 10000;
	srand((unsigned)time(nullptr));
	RBTree<int, int>t1;
	for (size_t i = 0; i < N; ++i) {
		int x = rand();
		t1.insert(make_pair(x, i));
	}
	cout << "is_balance():" << t1.is_balance() << endl;
}