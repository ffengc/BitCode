#pragma once


#include <assert.h>

namespace bit
{
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;

		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}

		list_node(T&& x)
			/// 记得完美转发
			:_data(std::forward<T>(x))
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};

	// typedef __list_iterator<T, T&, T*>             iterator;
	// typedef __list_iterator<T, const T&, const T*> const_iterator;

	// 像指针一样的对象
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> iterator;

		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef ptrdiff_t difference_type;


		Node* _node;

		// 休息到17：02继续
		__list_iterator(Node* node)
			:_node(node)
		{}

		bool operator!=(const iterator& it) const
		{
			return _node != it._node;
		}

		bool operator==(const iterator& it) const
		{
			return _node == it._node;
		}

		// *it  it.operator*()
		// const T& operator*()
		// T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		//T* operator->() 
		Ptr operator->()
		{
			return &(operator*());
		}

		// ++it
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		// it++
		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		// --it
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// it--
		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		//typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
		//typedef __reverse_iterator<const_iterator, const T&, const T*> //const_reverse_iterator;


		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		/*reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}*/

		void empty_init()
		{
			// 创建并初始化哨兵位头结点
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list()
		{
			empty_init();
		}

		void swap(list<T>& x)
			//void swap(list& x)
		{
			std::swap(_head, x._head);
		}

		// lt2(lt1)
		list(const list<T>& lt)
		{
			empty_init();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}

		// lt1 = lt3
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void push_back(const T& x)
		{
			//Node* tail = _head->_prev;
			//Node* newnode = new Node(x);

			//// _head          tail  newnode
			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;

			insert(end(), x);
		}

		void push_back(T&& x)
		{
			/// 记得完美转发
			insert(end(), std::forward<T>(x));
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;

			Node* newnode = new Node(x);

			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}

		iterator insert(iterator pos, T&& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			/// 
			/// 记得完美转发
			Node* newnode = new Node(std::forward<T>(x));

			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;
			delete cur;

			return iterator(next);
		}

	private:
		Node* _head;
	};
}