#pragma once

#include<string>
#include<iostream>


//这里就不搞太复杂的了
//把查找和插入留下就行

namespace Key{
	template<class K>
	struct BinarySearchTreeNode {
		BinarySearchTreeNode<K>* _left;
		BinarySearchTreeNode<K>* _right;
		K _key;
		BinarySearchTreeNode(const K& key)
			:_left(nullptr), _right(nullptr), _key(key) {}
	};

	template<class K> //一般喜欢叫key
	class BinarySearchTree {
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
	};
}

namespace key_value{
	template<class K,class V>
	struct BinarySearchTreeNode {
		BinarySearchTreeNode<K, V>* _left;
		BinarySearchTreeNode<K, V>* _right;
		K _key;
		V _value;
		BinarySearchTreeNode(const K& key, const V& value)
			:_left(nullptr), _right(nullptr), _key(key),_value(value) {}
	};

	template<class K, class V> //一般喜欢叫key
	class BinarySearchTree {
		typedef BinarySearchTreeNode<K, V> Node;
	private:
		Node* _root = nullptr;
	public:
		BinarySearchTree() = default;
		bool insert(const K& key, const V& value) {
			//如果没有节点，直接new
			if (_root == nullptr) {
				_root = new Node(key, value);
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
			cur = new Node(key, value);
			if (parent->_key < key) {
				parent->_right = cur;
			}
			else {
				parent->_left = cur;
			}
		}
		//查找
		//kv模型这里返回Node*
		Node* find(const K& key) {
			Node* cur = _root;
			while (cur) {
				if (cur->_key < key) {
					cur = cur->_right;
				}
				else if (cur->_key > key) {
					cur = cur->_left;
				}
				else {
					return cur;//返回节点的指针方便我们修改
				}
			}
			return nullptr;
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
	};
	
	void testkv1() {
		//kv模型使用场景1
		BinarySearchTree<string, string>dict;
		dict.insert("sort", "排序");
		dict.insert("left", "左边");
		dict.insert("right", "右边");
		dict.insert("string", "字符串");
		dict.insert("insert", "插入");
		string str;
		while (cin >> str) { //ctrl+Z+\n可以结束   ctrl+C直接杀死进程，建议用前者
			BinarySearchTreeNode<string, string>* ret = dict.find(str);
			if (ret) {
				cout << ":" << ret->_value << endl;
			}
			else {
				cout << "->无此单词" << endl;
			}
		}
	}
	void testkv2() {
		//场景2
		//统计数值出现的次数
		string arr[] = { "苹果","香蕉" ,"草莓" ,"苹果" ,"苹果" };
		BinarySearchTree<string, int>map;
		for (auto& str : arr) {
			BinarySearchTreeNode<string, int>* ret = map.find(str);
			if (ret) {
				ret->_value++;
			}
			else {
				map.insert(str, 1);
			}
		}
	}
}