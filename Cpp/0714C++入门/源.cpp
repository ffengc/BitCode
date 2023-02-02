#define _CRT_SECURE_NO_WARNINGS 1

//兼容C的语法
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

//命名空间
//解决命名冲突的问题
//如果定义了一个变量
#if 0
#include<stdlib.h>
//int rand=0;
//但是rand是stdlib.h里面的一个函数，这样就会重定义
namespace bit {
	int rand = 0;
}
//这样就不会报错了
/*   using namespace bit;   */
int main() {
	printf("%p\n", rand);//这里的打印的其实是rand()的地址，不是bit里面那个rand变量
	//但是如果我 using namespace bit; 这样又会报错了
	return 0;
}
#endif


#if 0
int a = 0;
int main() {
	int a = 1;
	printf("%d\n", a);//1
	//  ::是域限定符，::左边是空白，表示全局域
	printf("%d\n", ::a);//0
	return 0;
}
#endif

#if 0
#include<stdlib.h>
namespace bit {
	int rand = 0;
}
int main() {
	printf("%p\n", rand);
	printf("%p\n", &bit::rand);
	//这样就很好理解了，这两个是不一样的
	return 0;
}
#endif


//空间里面还能定义函数，定义类型
#if 0
namespace bit {
	int rand = 0;
	void func() {
		printf("func()\n");
	}
	struct TreeNode {
		struct TreeNode* left;
		struct TreeNode* right;
		int val;
	};
}
int main() {
	printf("%p\n", rand);
	printf("%p\n", &bit::rand);
	//func();//直接调用是调用不了的
	bit::func();
	struct bit::TreeNode node;
	return 0;
}
#endif



//命名空间可以嵌套
#if 0
namespace sql {
	int a = 0;

	namespace bit {
		int rand = 0;
		void func() {
			printf("func()\n");
		}
		struct TreeNode {
			struct TreeNode* left;
			struct TreeNode* right;
			int val;
		};
	}
}
int main() {
	printf("%p\n", rand);
	printf("%p\n", &sql::bit::rand);
	//func();//直接调用是调用不了的
	sql::bit::func();
	struct sql::bit::TreeNode node;
	return 0;
}
#endif

//多个文件里面如果用同一个命名空间名，其实只有一个
//编译器最后会合并的
//如果using namespace bit;
//现在全局找，然后就在bit里面去找
//std是C++标准库的命名空间

int main() {
	// << 流插入
	cout << "hello world" << endl;
	// << 可以自动识别类型
	// >> 流提取
	return 0;
}

//如果觉得using namespace std;  展开太多了
//可以指定一些展开，比如我觉得cin，cout比较常用
using std::cout;
using std::cin;
//也可