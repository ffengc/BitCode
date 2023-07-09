#pragma once
#include<cassert>
#include<string.h>
#include<algorithm>
#include<functional>
#include<initializer_list>
namespace yufc {
	template<class T>
	class vector {
	public:
		typedef T* iterator;//这个要放成共有，不然迭代器外面访问不了 -- 定义迭代器类型是指针类型
		typedef const T* const_iterator;
		//vector的迭代器就是原生指针
		iterator begin() {
			return _start;
		}
		iterator end() {
			return _finish;
		}
		//如果不提供const迭代器 -- 如果传了const的vector是遍历不了的，因为权限不能放大
		const_iterator begin()const { //不能返回普通迭代器，要返回const迭代器
			return _start;
		}
		const_iterator end()const {
			return _finish;
		}
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
		~vector() {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		//用初始化列表初始化
		vector(initializer_list<T>& list)
		{
			//用n个值去构造
			reserve(list.size());
			for (size_t i = 0; i < n; i++) {
				push_back(list[i]);
			}
		}
		//stl的vector还支持使用迭代器区间去构造
		//为什么需要一个其它类型的迭代器？
		//因为他要支持用其它容器的迭代器的区间构造
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) 
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			while (first != last) {
				//不能直接push_back()，直接push_back()会崩溃 -- 因为没有初始化 -- 野指针
				push_back(*first);
				++first;
			}
		}
		vector(size_t n, const T& val = T()) 
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			//用n个值去构造
			reserve(n);
			for (size_t i = 0; i < n; i++) {
				push_back(val);
			}
		}
		//传统拷贝构造
#if 0
		vector(const vector<T>& v) {
			_start = new T[v.size()];//这里是给size还是capacity呢？STL没有要求
			//memcpy(_start, v._start, sizeof(T) * v.size());
			//解决vector<vector<int>>深拷贝的情况,memcpy不能帮助内层的自定义类型完成深拷贝，赋值可以（我们写好了自定义类型的赋值）
			for (size_t i = 0; i < v.size(); i++) {
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();//因为T[]里面给了size(),所以这里也应该是v.size()
		}
#endif
		//写法2
#if 0
		vector(const vector<T>& v) 
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			reserve(v.size());
			for (const auto& e : v) { //注意：这里拷贝过去一定要引用，不然又要拷贝了
												//写深拷贝自己还要调深拷贝 -- 肯定是会出问题的
				push_back(e);
			}
			//不需要去调整_finish,因为push_back()已经搞定了
		}
#endif

		//现代写法拷贝构造 -- 复用迭代器区间构造函数
		void swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
#if 1
		vector(const vector<T>& v) 
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			vector<T>tmp(v.begin(), v.end());
			swap(tmp);//当然自定义类型自己写的swap更高效 -- 我们自己实现一个
		}
#endif
		vector<T>& operator=(vector<T> v) { //v1=v2
			//v是v2的拷贝，而且是局部的，swap完之后给到v1，v还会自动析构（因为是局部对象）
			swap(v);
			return *this;
		}
		size_t capacity()const {
			return _end_of_storage - _start;
		}
		size_t size()const {
			return _finish - _start;
		}
		void reserve(size_t n) {
			if (n > capacity()) {
				T* tmp = new T[n];
				size_t sz = size();
				if (_start) {
					//memcpy(tmp, _start, sizeof(T) * sz);//拷贝size()个字节过去，先放到tmp里面
					//同样，解决
					//vector<自定义类型>的问题
					for (size_t i = 0; i < sz; i++) {
						tmp[i] = _start[i];//当T是自定义类型时，调用T类型的operator=
					}
					delete[] _start;
				}
				_start = tmp;
				//_finish = _start + size();//这里不要现场去算size()
				//因为size()是用start减出来的，上面那一行start已经变了
				//所以在前面我们最好保留一下size先
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T()) {
			//1.扩容+初始化
			//2.初始化
			//3.删除数据
			if (n > capacity()) {
				reserve(n);
			}
			if (n > size()) {
				//初始化填值
				while (_finish < _start+n) {
					*_finish = val;
					++_finish;
				}
			}
			else {
				_finish = _start + n;
			}
		}
		T& operator[](size_t pos) {
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos) const {
			assert(pos < size());
			return _start[pos];
		}
		void push_back(const T& x) {
			//加了const保证传什么类型都行，因为隐式类型转换临时变量具有常性
			if (_finish == _end_of_storage) {
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = x;
			++_finish;
		}
		void pop_back() {
			assert(_finish > _start);//为空是不能删的
			--_finish;
		}
		void insert(iterator pos, const T& x) {
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _end_of_storage) {//扩容
				//记住pos和start的相对位置
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;//更新pos的位置 -- 解决迭代器失效
			}
			//挪动数据
			iterator end = _finish - 1;
			while (end >= pos) { // insert要扩容的时候，这个循环就失效了，停不下来了，为什么？
				*(end + 1) = *end;
				end--;
			}
			//扩容之后，旧空间的数据拷贝到新空间
			//旧空间已经被释放了 -- pos是指向旧空间的一个数字的位置的
			//pos成了野指针！ -- 迭代器失效
			//所以我们要把pos更新一下
			// -- 修改了内部的pos之后，其实问题还没有根本的解决
			*pos = x;
			++_finish;
		}
		iterator erase(iterator pos) {
			assert(pos >= _start);
			assert(pos < _finish);
			//挪动覆盖删除
			iterator begin = pos + 1;
			while (begin < _finish) {
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			//删除了位置的下一个位置 -- 还是pos
			return pos;
		}
		T& front() {
			assert(size() > 0);
			return *_start;
		}
		T& back() {
			assert(size() > 0);
			return *(_finish - 1);
		}
	private:
		iterator _start;//start相当于整个数组的开始位置
		iterator _finish;//[_start,_finish)
		iterator _end_of_storage;
	};
}