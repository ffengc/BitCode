#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include"UnorderedMap.h"
#include"UnorderedSet.h"

int main()
{
	//yfc::test_map1();
	//cout << endl;
	//yfc::test_set1();
	yfc::test_map2();
	return 0;
}

/**
 * 一个类型K去做set和unordered_set它的模板参数有什么要求？
 * set:
 * 要求支持小于比较，或者显式提供比较的仿函数
 * unordered_set:
 * 1.K类型对象可以转换整形取模，或者提供转成整型的仿函数
 * 2.K类型可以支持等于比较或者提供等于比较的仿函数.
 */