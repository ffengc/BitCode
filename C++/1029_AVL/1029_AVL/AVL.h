#pragma once

#include<map>
#include<set>
#include<algorithm>
#include<assert.h>
#include<time.h>
using namespace std;


template<class K,class V>
struct AVLNode {
public:
	AVLNode<K, V>* _left;
	AVLNode<K, V>* _right;
	AVLNode<K, V>* _parent;
	pair<K, V>_kv;
	int _bf;  //balance factor
public:
	AVLNode(const pair<K, V>& kv)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0) {}
};




//如何更新平衡因子
//如何旋转
template<class K, class V>
struct AVL {
	typedef AVLNode<K, V>Node;
private:
	Node* _root = nullptr;
private:
	//左单旋
	void rotate_left(Node* parent) {
		//当然我们还要注意处理parent指针
		//parent和subR不可能为空 -- ，但是subRL可能为空
		//1.parent是整颗树根
		//2.parent是子树的根
		//最后更新一下平衡因子
		//只有subR和parent的平衡因子受到了影响
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
		//更新一下平衡因子
		subR->_bf = parent->_bf = 0;//这个看图就行了
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
		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}
	//左右双旋
	void rotate_left_right(Node* parent) {
		//要在单旋之前记录一下，因为单旋之后平衡因子会变
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;//记录一下subLR的平衡因子
		rotate_left(parent->_left);//先最左边进行一个左旋
		rotate_right(parent);//再对自己进行一个右旋转
		//如何区分三种情况的平衡因子更新呢？

		subLR->_bf = 0;//一定要画图！三种情况的subLR最终都是0
		if (bf == 1) {
			//情况1
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1) {
			//情况2
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else if (bf == 0) {
			//情况3
			parent->_bf = 0;
			subL->_bf = 0;
		}
		else assert(false);
	}
	//右左双旋
	void rotate_right_left(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		rotate_right(parent->_right);
		rotate_left(parent);
		subRL->_bf = 0;
		if (bf == 1) {
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1) {
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else if (bf == 0) {
			subR->_bf = 0;
			parent->_bf = 0;
		}
		else assert(false);
	}
public:
	//我们先不返回pair，到时候我们封装map的时候在搞
	bool insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
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
		if (parent->_kv.first < kv.first) {
			parent->_right = cur;
		}
		else  {
			parent->_left = cur;
		}
		cur->_parent = parent;
		//控制平衡
		//先更新平衡因子
		while (parent) {//只有根没有父亲
			//最坏可能需要更新到根
			if (cur == parent->_right) {
				parent->_bf++;
			}
			else {
				parent->_bf--;
			}

			if (parent->_bf == 0) {
				//高度不变 -- 停止更新
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				//继续更新
				parent = parent->_parent;
				cur = cur->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) {
				//说明parent所在的子树已经不平衡了 -- 需要旋转
				//左旋
				if (parent->_bf == 2 && cur->_bf == 1) {
					//注意这里肯定是bf==1的情况 -- 才是单旋
					//parent->_bf==2说明是左单旋
					rotate_left(parent);//旋转就动了6个指针 -- O(1)
				}
				else if (parent->_bf == -2 && cur->_bf == -1) {
					rotate_right(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//左右双旋
					rotate_left_right(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//右左双旋
					rotate_right_left(parent);
				}
				else assert(false);
				break;
			}
			else {
				assert(false);//理论上不能走到这里
			}
		}
		return true;
	}
public:
	void inorder() {
		_inorder(this->_root);
	}
	bool is_balance() {
		return _is_balance(this->_root);
	}
private:
	void _inorder(Node* root) {
		if (root == nullptr) {
			return;
		}
		_inorder(root->_left);
		cout << (root->_kv).first << ":" << (root->_kv).second << endl;
		_inorder(root->_right);
	}
	int _height(Node* root) {
		if (root == nullptr)return 0;
		int leftHT = _height(root->_left);
		int rightHT = _height(root->_right);
		return max(leftHT, rightHT) + 1;
	}
	bool _is_balance(Node* root) {
		if (root == nullptr)return true;
		int leftHT = _height(root->_left);//左子树高度
		int rightHT = _height(root->_right);//右子树高度
		int diff = rightHT - leftHT;
		//把平衡因子也检查一下
		if (diff != root->_bf) {
			cout << root->_kv.first << "的平衡因子异常" << endl;
			return false;
		}
		return abs(diff) < 2
			&& _is_balance(root->_left)//判断一下左子树是否平衡
			&& _is_balance(root->_right);//判断一下右子树是否平衡
	}
};

void test1() {
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVL<int, int>t1;
	for (auto e : a) {
		t1.insert(make_pair(e, e));
	}
	t1.inorder();
	cout << "is_balance():" << t1.is_balance() << endl;
}
void test2(){
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVL<int, int>t1;
	for (auto e : a) {
		t1.insert(make_pair(e, e));
	}
	t1.inorder();
	cout << "is_balance():" << t1.is_balance() << endl;
}
void test3(){
	size_t N = 10000;
	srand(time(nullptr));
	AVL<int, int>t1;
	for (size_t i = 0; i < N; ++i) {
		int x = rand();
		t1.insert(make_pair(x, i));
	}
	cout << "is_balance():" << t1.is_balance() << endl;
}