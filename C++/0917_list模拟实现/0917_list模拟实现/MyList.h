#pragma once

#include<iostream>
#include<algorithm>
#include<cassert>
#include<list>
#include"reverse_iterator.h"

using namespace std;

namespace yufc {
	template<class T>
	struct list_node {
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& x = T()) //给缺省
			:_data(x), _next(nullptr), _prev(nullptr)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct __list__iterator {
		typedef list_node<T>Node;
		//标准的stl迭代器要检查类型的
		//如果不加下面几句用不了find
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef ptrdiff_t difference_type;

		Node* _node;
		__list__iterator(Node* node)//构造
			:_node(node) {}
		//核心控制行为
		bool operator!=(const __list__iterator& it)const {
			return _node != it._node;
		}
		//如果我们返回 const T& 我们就不能改了
		//对迭代器解引用 -- 注意，要返回引用 -- 可读可写
		Ref operator*() { // 同样，泛型化
			return _node->_data;
		}
		__list__iterator& operator++() {
			_node = _node->_next;
			return *this;
		}
		//继续完善
		bool operator==(const __list__iterator& it)const {
			return _node == it._node;
		}
		__list__iterator operator++(int) {
			__list__iterator tmp(*this);//先保存一下之前的值
			_node = _node->_next;
			return tmp;//只能传值返回了 -- 因为是临时对象
		}
		__list__iterator operator--(int) {
			__list__iterator tmp(*this);//先保存一下之前的值
			_node = _node->_prev;
			return tmp;//只能传值返回了 -- 因为是临时对象
		}
		__list__iterator& operator--() {
			_node = _node->_prev;
			return *this;
		}
		//stl里面还重载了一个 -> 毕竟迭代器就是[指针行为]的一种数据类型
		//什么时候会用 -> 呢？ 数据类型是结构体(类的时候)就需要了
		//T* operator->() {
		Ptr operator->() { //泛型化 -- 你传什么类型就调用什么类型
			//重载不了 -- 因为返回值不同不构成重载
			return &(operator*());
		}
	};


	template<class T>
	class list {
		typedef list_node<T>Node;
	public:
		typedef __list__iterator<T, T&, T*>iterator;
		typedef __list__iterator<T, const T&, const T*>const_iterator;
		typedef __reverse_iterator<iterator, T&, T*>reverse_iterator;
		typedef __reverse_iterator<const_iterator, const T&, const T*>const_reverse_iterator;


		iterator begin() {
			return iterator(_head->_next);//begin()是哨兵位的下一个位置
		}
		iterator end() {
			return iterator(_head);//end()是哨兵位
		}
		reverse_iterator rbegin() {
			return reverse_iterator(end());//因为前面我们设计的是对称的，所以你的正就是我的反，你的反就是我的正
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_iterator begin() const {
			return const_iterator(_head->_next);//begin()是哨兵位的下一个位置
		}
		const_iterator end() const {
			return const_iterator(_head);//end()是哨兵位
		}
		list() {
			empty_init();
		}
		~list() {
			//如果我们写完析构 -- 再浅拷贝 -- 就会肯定会崩溃了
			//先clear一下，再把头弄掉就行了
			this->clear();
			delete _head;
			_head = nullptr;
		}
		void empty_init() {
			//创建并初始化哨兵位头节点
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}//这样写好之后我们的构造也直接调用这个empty_init()就行了
		//拷贝构造
		//现在写法 -- 复用构造函数 -- 这个构造函数是传一个迭代器区间的（不一定要是list的迭代器）
		template<class InputIterator>
		list(InputIterator first, InputIterator last) { //构造
			empty_init();//创建并初始化哨兵位头节点
			while (first != last) { //当然我们不能直接插入 -- 头节点要先弄好 -- 不然直接push直接崩
				push_back(*first);
				++first;
			}
		}
		void swap(list<T>& x) {
			std::swap(_head, x._head);
		}
		list(const list<T>& lt) {
			//直接复用list(InputIterator first, InputIterator last)构造函数就行
			//lt2(lt1)
			empty_init();//先把自己初始化一下
			list<T>tmp(lt.begin(), lt.end());//这个构造结果就是lt2想要的
#if 0
			std::swap(_head, tmp._head);//直接换头指针就行了
#endif
			swap(tmp);
		}
		list<T>& operator=(list<T> lt) {
			//lt是一个深拷贝临时对象，换过来 -- 还帮你释放
			swap(lt);
			return*this;
		}
		void clear() {
			//清数据 -- 哨兵位是要保留的
			iterator it = begin();
			while (it != end()) {
				it = erase(it);
				//erase之后 -- 就失效了 -- 但是会返回下一个位置的迭代器
				//所以it = erase(it) 这样写就行了
			}
		}
		void push_back(const T& x) {
#if 0
			Node* tail = _head->_prev;//尾节点
			Node* newnode = new Node(x);
			//简单的链接关系
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
#endif
			//复用insert
			insert(end(), x);
		}
		void push_front(const T& x) {
			insert(begin(), x);
		}
		iterator insert(iterator pos,const T&x){
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			//prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}
		void pop_back() {
			erase(--end());
		}
		void pop_front() {
			erase(begin());
		}
		iterator erase(iterator pos) {
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;
			delete cur;
			return iterator(next);//返回下一个位置的迭代器
		}
	/// <summary>
	/// 迭代器 -- 重点之重点
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// 我们怎么用++去调用迭代器呢
	/// C++的两个精华 -- 封装、运算符重载/
	/// 首先肯定要重载*，要重载++
	private:
		Node* _head;
	};


	void print_list(list<int>&lt) {
		for (auto e : lt) {
			cout << e << " ";
		}
		cout << endl;
	}
	void test() {
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		lt.push_front(0);
		lt.push_front(-1);

		list<int>::iterator it = lt.begin();
		while (it != lt.end()) {
			cout << *it << " ";
			++it;
		}
		cout << endl;
		for (auto e : lt) {//相应的，它也能跑了
			cout << e << " ";
		}
		cout << endl;
		lt.pop_back();
		lt.pop_back();
		for (auto e : lt) {//相应的，它也能跑了
			cout << e << " ";
		}
		cout << endl;
		lt.pop_front();
		lt.pop_front();
		for (auto e : lt) {//相应的，它也能跑了
			cout << e << " ";
		}
		cout << endl;

		//find
		//在3之前插入一个30
		auto pos = find(lt.begin(), lt.end(), 3);
		if (pos != lt.end()) {
			//pos会失效吗？不会
			lt.insert(pos, 30);
			*pos *= 100; // 迭代器指向的是3
		}
		for (auto e : lt) {
			cout << e << " ";
		}
		cout << endl;
	}

	void func(const list<int>& lt) {
		//现在想去遍历一下
		//肯定是跑不了的 -- 需要const迭代器
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end()) {
			//*it = 10;
			cout << *it << " ";
			++it;
		}
	}
	void test2() {
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		func(lt);
	}

	void test3() {
		//深浅拷贝问题
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		list<int>copy = lt;
		*lt.begin() = 10;
		print_list(lt);
		cout << endl;
		print_list(copy);
		//如果是浅拷贝的话两个都改了 -- 两个list的头都指向同一个哨兵位头节点 -- 同一个链表
		lt.clear();
		cout << endl;
		print_list(lt);
		lt.push_back(1);
		print_list(lt);
	}
	void test4() {
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		list<int>copy;
		copy = lt;
		print_list(lt);
		print_list(copy);
		*lt.begin() = 10;
		print_list(lt);
		print_list(copy);
	}

	//反向迭代器测试
	void test5() {
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.push_back(6);
		lt.push_back(7);
		lt.push_back(8);
		print_list(lt);
		//反向迭代器测试
		list<int>::reverse_iterator rit = lt.rbegin();
		while (rit != lt.rend()) {
			cout << *rit << " ";
			++rit;
		}
		cout << endl;
	}
}
//现在要去实现反向迭代器
//普通思维：拷贝一份正向迭代器 -- 修改一下
//大佬思维：
//1.list可以这样实现，那vector那些的怎么办呢？
//	vector也可以像list一样弄一个struct 去重载
//  原来vector迭代器直接++是不用operator的，因为本来这个行为就可以符合规范
//	但是现在我们需要实现一个vector的反向迭代器，我们就可以operator一个++ 实际上是--_ptr
//2.复用！ -- 见vector的新头文件