#pragma once

//这个反向迭代器 -- list可以用 vector也可以用！
//什么容器的反向我们适配不出来？
//map set是可以的，什么不可以呢
//只要正向迭代器支持 ++ ,-- 都可以适配出来
//++一般容器都有，--不一定有
//比如单链表 -- forward_list就没有--
//1.forward_list 单链表
//2.unordered_map
//3.unordered_set
//
//迭代器从角度分类：
//forward_iterator ++
//bidirectional_iterator ++ --
//random_access_iterator ++ -- + -  随机位置迭代器
//
//deque vector 随机迭代器
//map set list 双向迭代器
//forward_list 单向迭代器
//
//forward_iterator
//bidirectional_iterator
//random_access_iterator
//其实它们是一种继承的关系
//双向是特殊的单向，随机是特殊的双向

namespace yufc {
	//复用，迭代器适配器
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator {
		Iterator _cur;
		typedef __reverse_iterator<Iterator, Ref, Ptr> RIterator;
		__reverse_iterator(Iterator it)
			:_cur(it) {}
		//为了对称，stl源码进行了一些操作
		RIterator operator++() { //迭代器++，返回的还是迭代器
			--_cur;//反向迭代器++，就是封装的正向迭代器--
			return *this;
		}
		RIterator operator--() {
			++_cur;//反向迭代器++，就是封装的正向迭代器--
			return *this;
		}
		Ref operator*() {
			//return *_cur;
			//为什么这里需要拷贝一下对象呢？
			//因为解引用只是取一下数据，迭代器位置肯定是不能变的 -- 变了肯定会出问题的
			auto tmp = _cur;
			--tmp;
			return *tmp;
		}
		Ptr operator->() {
			return &(operator*());
		}
		bool operator!=(const RIterator& it) {
			return _cur != it._cur;
		}
	};
}