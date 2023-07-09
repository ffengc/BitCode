#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//C++学习中我们要看到编译器做了更多的事情
//C
//ST st;
//...
//Creat ... Destroy
//
//C++
//stack<int>st;
//st.push()
//事实上有没有传地址？
//有的！ this指针就是地址



/*
1. 栈又叫堆栈，非静态局部变量/函数参数/返回值等等，栈是向下增长的。
2. 内存映射段是高效的I/O映射方式，用于装载一个共享的动态内存库。用户可使用系统接口创建共享共
享内存，做进程间通信。（Linux课程如果没学到这块，现在只需要了解一下）
3. 堆用于程序运行时动态内存分配，堆是可以上增长的。
4. 数据段--存储全局数据和静态数据。
5. 代码段--可执行的代码/只读常量
*/
#if 0
void Test() {
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = new int;
	//申请5个int的数组
	int* p3 = new int[5];//开5个 -- 不初始化
	//申请一个int对象，初始化为5
	int* p4 = new int(5);
	
	//C++98不支持初始化new的数组
	//C++11支持
	int* p5 = new int[5]{ 1,2,3 };

	free(p1);
	delete p2;
	delete[] p3;
	delete p4;
	delete[] p5;
	//malloc --  free
	//new -- delete 
	//要相对应 -- 有时候会出问题有时候不会

	//针对内置类型 -- new/delete 跟malloc没有本质区别，只有用法的类型
}
int main() {
	Test();
	return 0;
}
#endif

//针对自定义类型 -- 是有很大区别的
#if 0
class A {
public:
	A(int a = 0) :_a(a) {
		cout << "调用了A的构造函数" << " " << this << endl;
	}
	~A() {
		cout << "调用了A的析构函数" << " " << this << endl;
	}
private:
	int _a;
};
int main() {
#if 0
	A* p1 = (A*)malloc(sizeof(A));
	//还要检查

	//malloc()只申请空间
	free(p1);
	//只释放空间


	A* p2 = new A;
	//1.申请堆上的空间  2.还会调用构造函数（注意：是默认构造）
	delete p2;
	//1.调析构  2.释放

	//new delete 是为了自定义类型准备的

#endif
	//如果是多个对象呢？
	A* p3 = new A[3];
	delete[] p3;
	//每个对象都会调构造 -- 每个对象都会调析构
	//析构顺序和构造顺序是相反的
	//后定义的先析构

	//默认构造最好我们还是提供一下，给个缺省，不给容易编不过 -- 找不到默认构造
	return 0;
}
#endif


//还有一个明显的区别 -- 开空间失败的处理
#if 0
int main() {
	//失败返回NULL
	char* p1 = (char*)malloc(sizeof(char) * 1024u * 1024u * 1024u * 1024u);
	//cout << p1 << endl;//这里最好不要用cout，cout会识别成字符串 -- 这里最好用printf
	printf("%p\n", p1);
	free(p1);


	//new失败是抛出异常
	char* p2 = new char[1024u * 1024u * 1024u * 1024u * 1024u];
	printf("%p\n", p2);
	//抛异常是面向对象语言处理错误的方式，py中了解过了
	return 0;
}
#endif




#if 0
//new和delete本质上是调用了malloc和free
//为什么要封装一层？
//因为要处理异常
//operator new的意义
//1.封装malloc -- 为了去跑异常
#define free(p) _free_dbg(p, _NORMAL_BLOCK)
//free 本质上是一个宏 -- 我们找源代码看到时候能看懂


//opertor new我们也可以自己用的 用法和malloc一样
int main() {
	char* p = (char*)operator new(sizeof(char) * 1024);
	//用法和malloc一样，失败的话抛异常
	return 0;
}
#endif
//实际应用不要去用
//直接用new和delete就行了


//opertor new/...是可以被重载的
//如果不写就是调用默认那个
//我们也可以写一个自己专属的 -- 它就会去调用我们自己写的


//重载一个类专属的operator new
class ListNode {
public:
	int _val;
	ListNode* _next;
	static allocator<ListNode>_alloc;//大家的节点弄一个内存池就行
	//注意 static 引用的在类里面声明在类外面定义！别忘了！

	ListNode(int val)
		:_val(val),
		_next(nullptr)
	{}
	//重载
	void* operator new(size_t n) {
		//...可以写一个内存池
		//我们也可以直接调用库里面的

		//allocator这个类 -- 是一个内存池
		//C++里面叫空间配置器
		void* obj = _alloc.allocate(n);
		//我们可以写成成员变量
		return obj;
	}
	void operator delete(void* ptr) {
		_alloc.deallocate((ListNode*)ptr, 1);
	}
};	
allocator<ListNode>ListNode::_alloc;
int main() {
	//频繁申请ListNode
	//想要提高效率 -- 申请ListNode的时候，不去malloc，而是走自己定制的内存池
	ListNode* node1 = new ListNode(1);
	ListNode* node2 = new ListNode(2);
	ListNode* node3 = new ListNode(3);
	ListNode* node4 = new ListNode(4);

	delete node1;
	delete node2;
	delete node3;
	delete node4;

	return 0;
}

//在计算机领域下面 -- 频繁申请一个东西可以采用池化技术！
//这里是内存池

//总结：
//new = operator new+构造函数
//默认情况下operator new使用全局库里面
//每个类可以去实现自己专属operator new 。new这个对象的时候，就不会去调默认的，而失去调自己的



//定位new 了解