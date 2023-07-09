#pragma once

#include<vector>
#include<iostream>
using namespace std;

//位图特点
//1.快、节省空间
//2.相对局限，只能映射处理整型



//用char -- 一个char位置存8位
//怎么找位置，比如20
//20/8=2表示放在第几个char上
//20%8=4表示放在这个char的第几个位置
namespace yfc
{
	template<size_t N>
	class bit_set
	{
	public:
		bit_set()
		{
			_bits.resize(N / 8 + 1, 0);//+1可以保证空间一定够
		}
		void set(size_t x)
		{
			//把x的位置设置成1
			size_t i = x / 8;
			size_t j = x % 8;
			//怎么把_bit[i]的第j位弄成1呢
			//用一个或运算！
			_bits[i] |= (1 << j);
		}
		void reset(size_t x)
		{
			//把x的位置设置成0
			size_t i = x / 8;
			size_t j = x % 8;
			_bits[i] &= ~(1 << j);
		}
		bool test(size_t x)
		{
			//看这一位是0还是1
			size_t i = x / 8;
			size_t j = x % 8;
			return _bits[i] & (1 << j);
		}
	private:
		vector<char> _bits;
	};
	void test_bit_set1()
	{
		bit_set<100>bs1;
		bs1.set(8);
		bs1.set(9);
		bs1.set(20);

		cout << bs1.test(8) << endl;
		cout << bs1.test(9) << endl;
		cout << bs1.test(20) << endl;

		bs1.reset(8);
		bs1.reset(9);
		bs1.reset(20);

		cout << bs1.test(8) << endl;
		cout << bs1.test(9) << endl;
		cout << bs1.test(20) << endl;
	}
	void test_bit_set2()
	{
		//这三种写法都可以
		bit_set<-1>bs1;//-1的写法是最好的 -- -1对应的size_t就是全1
#if 0
		bit_set<0xffffffff>bs2;
		bit_set < 1024 * 1024 * 1024 * 4 - 1> bs3;
#endif
		//我们打开看任务管理器 -- 是可以看到是512MB左右的
	}




	//面试题2
	//我们用两个位图就行 -- 两个位图对应位置一起表示状态
	template<size_t N>
	class twobitset
	{
	private:
		bit_set<N>_bs1;
		bit_set<N>_bs2;
	public:
		void set(size_t x)
		{
			//要先判断一下
			bool inSet1 = _bs1.test(x);
			bool inSet2 = _bs2.test(x);
			if (inSet1 == false && inSet2 == false)
			{
				//00->01
				_bs2.set(x);
			}
			else if (inSet1 == false && inSet2 == true)
			{
				//01->10
				_bs1.set(x);
				_bs2.reset(x);
			}
		}
		void print_once_num()
		{
			for (size_t i = 0; i < N; i++)
			{
				if (_bs1.test(i) == false && _bs2.test(i) == true)
				{
					cout << i << " ";
				}
			}
			cout << endl;
		}
	};
	void test_bit_set3()
	{
		int a[] = { 1,2,3,4,5,6,7,8,9,10,12,10,9,8,6,5,3,2,1 };
		twobitset<100>bs;
		for (auto e : a)
		{
			bs.set(e);
		}
		bs.print_once_num();
	}
	//面试题3
	//也是用两个位图
	//第一个是文件1的映射
	//第二个是文件2的映射
	//映射位都是1的值就是交集

	//面试题4
	//其实和2是一样的，00/01/10/11就行
}