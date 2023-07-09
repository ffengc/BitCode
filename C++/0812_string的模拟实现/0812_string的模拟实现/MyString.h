#pragma once
#include<cstring>
#include<cassert>
#include<iostream>
using namespace std;


//为了区分和库里面的，我们用命名空间包起来
namespace MyString {
	class string {
	public:
		//迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}
		//const迭代器 -- 只读不写
		const_iterator begin() const {
			return _str;
		}
		const_iterator end() const {
			return _str + _size;
		}
		//构造
#if false
		string()//初始化的时候一定不能给nullptr，因为如果创建一个空对象的时候，去打印
			//就会造成空指针的解引用
			//或者给全却称
			:_str(new char[1]),
			_size(0),
			_capacity(0)
		{
			_str[0] = '\0';//给一个空间放'\0'
		}
#endif
		string(const char* str = "\0")//写""是等价的，因为""会自带'\0'
			//:_str(new char[strlen(str) + 1]),
			//_size(strlen(str)),
			//_capacity(strlen(str)) -- 这样搞用三次strlen() -- 别用初始化列表了
		{
			//动态开辟空间
			size_t len = strlen(str);
			_str = new char[len + 1];
			_size = len;
			_capacity = len;
			strcpy(_str, str);
		}
		//析构
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		//拷贝构造(实现一个深拷贝)		
		//写法1：传统写法
#if 0
		string(const string& s) 
			:_str(new char[s._capacity+1]),
			_size(s._size),
			_capacity(s._capacity)
		{
			strcpy(_str, s._str);
		}

		//赋值重载
		string& operator=(const string& s) {
			if (this == &s)return *this;//自己给自己赋值 -- 直接避开
			//无论什么情况，都选择把原来的空间释放掉+开新的空间+拷贝
			char*tmp = new char[s._capacity + 1];//一定要记得+1
			//new失败怎么办 -- 这样就会造成拷贝失败，而且原来的string被释放了，所以最好先new再delete原来的
			strcpy(tmp, s._str);
			delete[] _str;

			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;
			return *this;
			//这样写的话，自己给自己赋值就会出问题 -- 因为自己给自己释放了 -- 拷贝自己 -- 拷贝到的就是随机值！
		}
#endif
		//现代写法
		//构造来当打工人
		void swap(string& tmp) {
			std::swap(_str, tmp._str);
			std::swap(_size, tmp._size);
			std::swap(_capacity, tmp._capacity);
		}
		string(const string& s)
			: _str(nullptr),
			_size(0),
			_capacity(0)
		{
			//因为s里面的东西可能是随机值
			//如果换给tmp之后，tmp出了作用域是会析构的 -- 析构随机的东西就会出问题
			//析构0或者null是不会出问题的，所以初始化一下
			//因为swap要频繁调用，我们这里自己再写一个最好
			string tmp(s._str);
			swap(tmp);//this->swap(tmp)
		}
		//写法2：
#if 0
		string& operator=(const string& s) {
			if (this == &s)return *this;//自己给自己赋值 -- 直接避开
			string tmp(s);
			swap(tmp);//this和swap换
			return *this;
			//把原来的s换给tmp之后 -- tmp还需要帮忙打扫s的空间，因为tmp是一个局部对象！
		}
#endif
		//写法3
		string& operator=(string s) {//s就是顶替tmp，s就完成拷贝了，而且是局部对象！
			swap(s);
			return *this;
		}
		//在以后复杂数据结构的学习中 -- 现代写法的优势会更大
		
		
		//size
		size_t size()const {
			return _size;
		} 
		size_t capacity()const {
			return _capacity;
		}
		//[]重载
		char& operator[](size_t pos) {
			assert(pos < _size);
			return _str[pos];
		}
		char& operator[](size_t pos) const { //这个是不能写的
			assert(pos < _size);
			return _str[pos];
		}
		//兼容C字符串接口
		const char* c_str() {
			return _str;
		}
		void reserve(size_t n) {
			if (n > _capacity) {
				//扩容不缩容
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;

				_str = tmp;
				_capacity = n;
			}
		}
		void resize(size_t n, char ch = '\0') {
			//开空间+初始化
			if (n > _size) {
				//插入数据
				reserve(n);
				for (size_t i = _size; i < n; i++) {
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else {
				//删除数据
				_str[n] = '\0';
				_size = n;
			}
		}
		void push_back(char ch) {
			//不用去写CheckCapacity函数，我们先写reserve这个函数，复用！
#if 0
			if (_size==_capacity)
			{
				//注意：如果一开始是用了构造的缺省值，也就是0，就不能扩二倍！
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';//一定要记得'\0'
#endif
			insert(_size, ch);
		}
		void append(const char* str) {
#if 0
			size_t len = strlen(str);
			if (_size + len > _capacity)//注意，此时不能扩容二倍了！因为可能不够
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);//哪个好？
			//strcat(_str, str);//这个效率是比较低的 -- 因为要去strcat要去找'\0',持续追加的时候效率非常低！
			_size += len;
#endif
			insert(_size, str);
		}
		string& operator+=(char ch) {
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* str) {
			append(str);
			return *this;
		}
		//insert
		string& insert(size_t pos, char ch) {
			assert(pos <= _size);
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			//pos==0情况第一种处理方法
#if 0
			int end = _size;
			while (end >= (int)pos) {
				//注意：pos==0的时候会出问题，end--之后会变成-1->整型最大值，所以给pos强转一下,_size改成int就行
				_str[end + 1] = _str[end];
				--end;
			}
#endif
			//第二种处理方法(比较推荐)
			size_t end = _size + 1;//这些都别改，继续用uint
			while (end > pos)//这里写成大于！
			{
				_str[end] = _str[end - 1];//这里改成-1
				--end;
			}
			_str[pos] = ch;
			++_size;
			return * this;
		}
		//实现这些接口一定要很细心很细心！
		string& insert(size_t pos, const char* str) {
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			//挪动数据
			size_t end = _size + len;//这些都别改，继续用uint
			while (end >= pos + len)//这里写成大于！
			{
				_str[end] = _str[end - len];//这里改成-1
				--end;
			}
			//放数据
			strncpy(_str + pos, str, len);//这里用ncpy，不要把'\0'拷贝进去
			_size += len;
			return *this;
		}
		//erase
		string& erase(size_t pos, size_t len = npos) {
			assert(pos < _size);
			if (len == npos || pos + len >= _size) {
				//相当于pos后面的全部删掉了
				_str[pos] = '\0';
				_size = pos;
			}
			else {
				//删除部分
				//需要挪动数据
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}
		void clear() {
			_str[0] = '\0';
			_size = 0;
		}
		//find系列
#if true
		size_t find(char ch, size_t pos = 0) {
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++) {
				if (ch == _str[i]) {
					return i;
				}
				return npos;
			}
		}
		size_t find(const char* sub, size_t pos = 0) {
			//strstr -- 暴力
			//字符串匹配算法 kmp/bm
			assert(pos < _size);
			assert(sub);
			const char* ptr = strstr(_str + pos, sub);
			if (ptr == nullptr) {
				return npos;
			}
			return ptr - _str;
		}
		//substr --  从pos位置开始，取len个字符
		string substr(size_t pos = 0, size_t len = npos)const {
			//不用改变自己，const也行
			assert(pos < _size);
			size_t realLen = len;
			if (len == npos || pos + len > _size) {
				//超范围了
				//有多少取多少
				realLen = _size - pos;
			}
			string sub;
			for (size_t i = 0; i < realLen; ++i) {
				sub += _str[pos + i];
			}
			return sub;
		}
#endif
		//运算符重载比较系列
#if true
		bool operator>(const string& s)const {
			return strcmp(_str, s._str) > 0;
		}
		bool operator==(const string& s)const {
			return strcmp(_str, s._str) == 0;
		}
		bool operator>=(const string& s)const {
			return *this > s || *this == s;
		}
		bool operator<=(const string& s)const {
			return !(*this > s);
		}
		bool operator<(const string& s)const {
			return !(*this >= s);
		}
		bool operator!=(const string& s)const {
			return !(*this == s);
		}
#endif
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		//这个npos按道理在外面也可以取到才对
		const static size_t npos = -1;
	};
	//流提取和流插入
	//不是必须是友元的，因为不一定要访问私有，这里就不用
	ostream& operator<<(ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); i++) {
			out << s[i];
		}
		return out;
	}
	istream& operator>>(istream& in, string& s) {

		s.clear();

		//输入字符串很长，不断+=，频繁扩容，效率很低，大家可以想办法优化一下
		//1.reserve() -- 缺陷：浪费空间
		//2.别动string先，先放到一个临时数组里面，因为这个临时数组是在栈上的 -- 出了>>就销毁了
		char ch;
		ch = in.get();

		const size_t N = 32;
		char buff[N];
		size_t i = 0;

		//s.reserve(128);
		while (ch != ' ' && ch != '\n') {
			buff[i++] = ch;
			if (i == N - 1) {//表示满了
				buff[i] = '\0';
				s += buff;//一批一批加到string里面
				i = 0;
			}
			ch = in.get();
		}
		//把最后一批加上去
		//buff相当于缓冲了
		buff[i] = '\0';
		s += buff;
		return in;
		//但是现在会有bug
		//如果字符串里面原来有东西的话，会留下
		//我们先要清空一下string
	}
	//size_t string::npos = -1;//在类外面定义
	//但是const static变量可以在类里面给缺省，外面就不用写了，这是C++的特例
}