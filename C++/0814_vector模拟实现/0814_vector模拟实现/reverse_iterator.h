#pragma once


namespace yufc {
	//复用，迭代器适配器
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator {
		Iterator cur;
		typedef __reverse_iterator<Iterator> RIterator;
		__reverse_iterator(Iterator it)
			:_cur(it) {}
		//为了对称，stl源码进行了一些操作
		Ref operator++() {
			--_cur;//反向迭代器++，就是封装的正向迭代器--
			return *this;
		}
		Ref operator--() {
			++_cur;//反向迭代器++，就是封装的正向迭代器--
			return *this;
		}
		Ref operator*() {
			//return *_cur;
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