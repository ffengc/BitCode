#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<map>
#include<set>
#include<unordered_map>
#include<algorithm>
#include<vector>
using namespace std;
#include<iostream>
#include<bitset>
#elif
#endif

#include"BitSet.h"
#include"BloomFilter.h"
/** 面试题 */
//给40亿个不重复的无符号整数，无序。给一个无符号整数，如何判断一个数是否在其中
//1.搜索树和哈希表 -- 不行（内存中存不下）
//2.排序+二分查找 -- 数据太大，只能放在磁盘上，不好支持二分查找，效率慢
//3.位图 -- 可以很好解决这个问题


//位图
//直接定址法（一个bit位映射标记值，1表示在/0表示不在）
//从0,1,2,......,2^32-1 -- 512MB的大小



/** 面试题2 */
//100亿个数找只出现一次的值 -- 两位的位图 -- 00表示没出现/01表示出现一次/10表示两次两次以上
/** 面试题3 */
//给两个文件，分别有100亿个整数，我们只有1G的内存，如何找到两个文件的交集
/** 面试题4 */
//1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的整数
int main()
{
	//yfc::test_bit_set1();
	//yfc::test_bit_set2();
	//yfc::test_bit_set3();
	//yfc::testBloomFilter1();
	yfc::TestBloomFilter2();
	return 0;
}


//布隆过滤器 -- 字符串转整型
//会冲突
//所以布隆过滤器存在误判！
//在：不准确的，存在误判的
//不在：准确的，不存在误判的

//不可能完全去掉误判  -->  降低误判率
//每个值多映射几个位
//理论上：一个值映射的位越多，误判率越低，但是不能无限映射，那么空间消耗就会增加


/** 面试题4 */
//给两个问题件，分别有100亿个query，我们只有1G内存，如果和找到两个文件的交集
//分别给出精确算法和近似算法
//海量数据处理问题

//哈希切分
//1.假设每个query占30字节
//	100亿个query需要多少空间？-> 3000亿byte -> 约等于300GB
//2.假设两个文件叫A和B
