#pragma once


template<class K> 
struct BinarySearchTreeNode {
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	K _key;
	BinarySearchTreeNode(const K& key)
		:_left(nullptr), _right(nullptr), _key(key) {}
};

template<class K> //一般喜欢叫key
class BinarySearchTree{
	typedef BinarySearchTreeNode<K> Node;
private:
	Node* _root = nullptr;
public:
	~BinarySearchTree() {
		_destroy(_root);
	}
	BinarySearchTree() = default;//C++11 -- 强制编译器生成默认的构造
	BinarySearchTree(const BinarySearchTree<K>& t) {
		//前序是最好的
		_root = _copy(t._root);
	}
	BinarySearchTree<K>& operator=(BinarySearchTree<K>t) {
		swap(_root, t._root);
		return *this;
	}
private:
	Node* _copy(Node* root) {
		if (root == nullptr) {
			return nullptr;
		}
		Node* copyRoot = new Node(root->_key);
		copyRoot->_left = _copy(root->_left);
		copyRoot->_right = _copy(root->_right);
		return copyRoot;
	}
	void _destroy(Node*& root) {
		//加引用可以让最后的置空起作用
		if (root == nullptr) {
			return;
		}
		_destroy(root->_left);
		_destroy(root->_right);
		delete root;
		root = nullptr;
	}
public:
	bool insert(const K& key) {
		//如果没有节点，直接new
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}
		//找插入的位置
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				//搜索树是不允许重复键值的
				return false;//插入失败
			}
		}
		//为了能插入，最好定义一个parent同时遍历
		cur = new Node(key);
		if (parent->_key < key) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
	}
	//递归插入
	bool insertR(const K& key) {
		return _insertR(_root, key);
	}
	//查找
	bool find(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (cur->_key < key) {
				cur = cur->_right;
			}
			else if (cur->_key > key) {
				cur = cur->_left;
			}
			else {
				return true;//插入失败
			}
		}
		return false;
	}
	//递归查找
	bool findR(const K& key) {
		return _findR(_root, key);
	}
	//删除
		//删除孩子没有节点 -- 直接置空
		//删除孩子只有一个孩子 -- 托孤
		//删除孩子有两个孩子 -- 替换法删除 -- 找一个值去替换要删除的
		//找谁去替换呢 -- 左子树的最大节点或者右子树的最小节点

		/**
		 * 替换节点赋值给删除节点后，删除替换节点
		 * 替换节点要么没有孩子，要么只有一个孩子，可以直接删除.
		 */
	bool erase(const K& key) {
		//先查找
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				//找到了 -- 开始删除
				//要删除的是度为1的节点
				//当然还有一个特殊情况 -- 如果要删除的是根 -- 怎么办
				if (cur->_left == nullptr) {
					//先判断它的父亲是在左边还是在右边
					if (cur == this->_root) {
						//处理特殊情况
						_root = cur->_right;
					}
					else { // 删掉不是根
						if (cur == parent->_left) {
							parent->_left = cur->_right;
						}
						else {
							parent->_right = cur->_right;
						}
					}
					delete cur;//删除这个节点
					cur = nullptr;
				}
				else if (cur->_right == nullptr) {
					//先判断它的父亲是在左边还是在右边
					if (cur == _root) {
						_root = cur->_left;
					}
					else {
						if (cur == parent->_left) {
							parent->_left = cur->_left;
						}
						else {
							parent->_right = cur->_left;
						}
					}
					delete cur;//删除这个节点
					cur = nullptr;
				}
				//要删除的是度为2的节点
				else {
					//替换法删除
					//找到右子树最小节点进行替换
					Node* rightMin = cur->_right;
					Node* minParent = cur;//这里不能给空 -- 如果要删的是_root就出问题了，循环进不去
					while (rightMin->_left) {
						minParent = rightMin;
						rightMin = rightMin->_left;//找到最左边的
					}
					swap(cur->_key, rightMin->_key);
					//现在就是度为1/0的情况了
					
					//minParent->_left = min->_right;
					// //这里不能直接让parent的左去指向min的右
					//万一删除的是根节点 -- 就不是parent的左去指了，而是parent的右去指min的右
					//所以这里老老实实判断一下
					if (minParent->_left == rightMin) {
						minParent->_left = rightMin->_right;
					}
					else {
						minParent->_right = rightMin->_right;
					}
					delete rightMin;
					rightMin = nullptr;
				}
				return true;
			}
		}
		return false;
	}
	//递归删除
	bool eraseR(const K& key) {
		return _eraseR(this->_root, key);
	}
	//写一个中序
	void inorder() {
		_inorder(_root);
		cout << endl;
	}
private:
	void _inorder(Node* root) {
		if (root == nullptr)return;
		_inorder(root->_left);
		cout << root->_key << " ";
		_inorder(root->_right);
	}
	//递归查找
	bool _findR(Node* root, const K& key) {
		//O(h) h是树的高度
		if (root == nullptr)return false;
		if (root->_key < key) {
			return _findR(root->_right, key);
		}
		else if (root->_key > key) {
			return _findR(root->_left, key);
		}
		else {
			return true;
		}
	}
	//递归插入
	bool _insertR(Node*& root, const K& key) {
		//神之一笔 -- 这里加了引用 -- 这样直接加了就直接链接起来了
		if (root == nullptr) {
			//可以插入
			root = new Node(key);
			return true;
		}
		if (root -> _key < key) {
			return _insertR(root->_right, key);
		}
		else if (root -> _key > key) {
			return _insertR(root->_left, key);
		}
		else return false;
	}
	//递归删除
	bool _eraseR(Node*& root, const K& key) {
		if (root == nullptr) {
			return false;
		}
		if (root->_key < key) {
			return _eraseR(root->_right, key);
		}
		else if (root->_key > key) {
			return _eraseR(root->_left, key);
		}
		else {
			Node* del = root;
			if (root->_left == nullptr) {
				root = root->_right;
			}
			else if (root->_right == nullptr) {
				//现在的root是上一层root->right的别名 -- 直接换掉就行
				root = root->_left;
			}
			else {
				//要删除的节点度为2
				//这个时候就不能借助上面的方式了
				Node* min = root->_right;
				while (min->_left) {
					min = min->_left;
				}
				swap(root->_key, min->_key);
				//return eraseR(key); -- err 这样是删不掉的 -- 因为交换之后树的结构已经出问题了
				return _eraseR(root->_right, key);//但是我从root->right开始遍历就可
			}
			delete del;
			return true;
		}
	}
};
/**
 * 增删查的时间复杂度是O(h)
 * 最坏的情况是O(n)
 * 当树是单支的时候搜索树会退化成链表
 * 改进的方案：平衡树 -- AVL/红黑树.
 */


/** key模型，判断关键字在不在 */
/** key/value模型，通过key去找value */


void Test1(){
	BinarySearchTree<int>t;
	int a[] = { 8,3,1,10,6,4,7,14,13 };
	for (auto e : a) {
		//插入其实是排序+去重
		t.insert(e);
	}
	t.inorder();

	t.erase(3);
	t.inorder();
	t.erase(8);
	t.inorder();
}

void Test2() {
	BinarySearchTree<int>t;
	int a[] = { 8,3,1,10,6,4,7,14,13 };
	for (auto e : a) {
		//插入其实是排序+去重
		t.insertR(e);
	}
	t.inorder();

	cout << "开始删除" << endl;
	for (auto e : a) {
		//插入其实是排序+去重
		t.eraseR(e);
		t.inorder();
	}
}

//拷贝问题
void Test3() {
	BinarySearchTree<int>t;
	int a[] = { 8,3,1,10,6,4,7,14,13 };
	for (auto e : a) {
		//插入其实是排序+去重
		t.insertR(e);
	}
	//t.inorder();

	BinarySearchTree<int>copy = t;
	copy.inorder();
	t.inorder();

	BinarySearchTree<int>t1;
	t1 = t;
	t1.insert(100);
	t1.inorder();
}