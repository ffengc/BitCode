#define _CRT_SECURE_NO_WARNINGS 1


//结构体
#if 0
struct tag {
	member - list;
}variable-list;
#endif



#if 0
struct Stu {
	char name[20];
	int age;
	double score;
};


//特殊的声明
//匿名结构体
struct {
	char name[20];
	float price;
	char id[12];
}ss;//只能用一次


//如果两个匿名的一样
struct {
	int a;
	char b;
	float c;
}x;
struct {
	int a;
	char b;
	float c;
}a[20], * p;
//匿名结构体的成员如果一样，在编译器看来，看作是不同的数据类型
#endif

//结构体的自引用
#if 0
#if 0
struct Node {
	int data;
	struct Node next;
};//可行否？
#endif
//如果可以，那sizeof(struct Node)是多少
//这种是错误的
//所以我们只能存地址
//数据域和指针域
struct ListNode {
	int data;
	struct ListNode* next;
};
#endif

//初始化
struct Book {
	char name[20];
	float price;
	char id[12];
}s = { "鹏哥C语言",55.5f,"PGC001" };
int main() {
	struct Book s2 = { "杭哥数据结构",66.6f,"HG001" };
	return 0;
}