#pragma once
#include<map>
#include<iostream>
#include<assert.h>
using namespace std;
enum Colour {
	RED,BLACK
};

template<class T>
struct __Red_Black_TreeNode {
	__Red_Black_TreeNode<T>* _left;
	__Red_Black_TreeNode<T>* _right;
	__Red_Black_TreeNode<T>* _parent;
	//pair<K, V>_kv;
	T _data;
	Colour _col;
	__Red_Black_TreeNode(const T& data)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _data(data) {}
};

//迭代器
template<class T, class Ref, class Ptr>
struct __redblack_tree_iterator {
	typedef __Red_Black_TreeNode<T>Node;
	Node* _node;
	__redblack_tree_iterator(Node* node)
		:_node(node) {}
	Ref operator*() {
		return _node->_data;
	}
	Ptr operator->() {
		return &_node->_data;
	}
	bool operator!=(const __redblack_tree_iterator& s) const {
		return _node != s._node;
	}
	bool operator==(const __redblack_tree_iterator& s) const {
		return _node == s._node;
	}
	__redblack_tree_iterator& operator++() {
		//1.右子树不为空，++就是找右子树的中序第一个
		//2.如果右子树为空，找孩子不是父亲右边的那个祖先
			//如果当前节点是父亲的右，说明父亲访问过了
		if (_node->_right) {
			//1.
			Node* left = _node->_right;
			while (left->_left) {
				left = left->_left;
			}
			_node = left;
		}
		else {
			//2.
			Node* parent = _node->_parent;
			Node* cur = _node;
			while (parent && cur == parent->_right) {
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	__redblack_tree_iterator& operator--() {
		//1.如果左不为空 -- 找左的最右
		//2.如果左为空 -- 找到孩子不是父亲的左的那个祖先
		if (_node->_left) {
			Node* right = _node->_left;
			while (right->_right) {
				right = right->_right;
			}
			_node = right;
		}
		else {
			Node* parent = _node->_parent;
			Node* cur = _node;
			while (parent && cur == parent->_left) {
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}	
};


//第三个模板参数是一个仿函数
template<class K,class T,class KeyOfT>
struct RBTree {
	typedef __Red_Black_TreeNode<T>Node;
private:
	Node* _root = nullptr;
public:
	typedef __redblack_tree_iterator<T, T&, T*> iterator;
	iterator begin() {
		//stl源码里面是有哨兵位的，这里我们没有 -- 所以我们找一下最左节点
		Node* left = _root;
		while (left && left->_left) {
			left = left->_left;
		}
		return iterator(left);
	}
	iterator end() {
		return iterator(nullptr);//直接给空就行了
	}
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
public:
	//前面插入的过程和搜索树一样的
	pair<iterator, bool> insert(const T& data) {
		KeyOfT kot;
		if (_root == nullptr) {
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root), true);
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (kot(cur->_data) < kot(data)) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data)) {
				parent = cur;
				cur = cur->_left;
			}
			else return make_pair(iterator(cur), false);
		}
		cur = new Node(data);
		Node* newnode = cur;
		cur->_col = RED;//一开始尽量先变红
		if (kot(parent->_data) < kot(data)) {
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
		//这里我们要返回新增的节点 -- 但是刚才插入过程可能不见了，所以前面最好保存一下
		return make_pair(iterator(newnode), true);
	}
};