#define _CRT_SECURE_NO_WARNINGS 1
#include"sort.h"

//记录快排递归次数
int callCount = 0;

void PrintArray(int* a, int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
//直接插入排序
void InsertSort(int* a, int n) {
	//[0,end]有序，把end+1位置的值插入，保持有序
	for (int i = 0; i < n - 1; i++) {//边界是n-2
		int end = i;
		int tmp = a[end + 1];//所以end最后的位置是n-2
		while (end >= 0) {
			if (tmp < a[end]) {
				a[end + 1] = a[end];
				--end;
			}
			else {
				break;//先break再赋值
			}
		}
		a[end + 1] = tmp;
	}
}
//希尔排序
void ShellSort(int* a, int n) {
	//预排序+插入排序
	//gap

	//下面是单趟循环
#if 0
	for (int j = 0; j < gap; j++) {
		for (int i = 0; i < n - gap; i += gap) {
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0) {
				if (tmp < a[end]) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else break;
			}
			a[end + gap] = tmp;
		}
	}
#endif
	//上面套两层循环的方式可以解决，比较清晰，但是下面这种方法是简化后的写法
	int gap = n;
	while (gap > 1) {
		gap /= 2;
		for (int i = 0; i < n - gap; ++i) {
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0) {
				if (tmp < a[end]) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else break;
			}
			a[end + gap] = tmp;
		}
	}
}
//排升序的时候，gap越大，大的数字可以更快的到后面，小的数可以更快到前面
//但是越不接近有序
//gap越小，月接近有序，当gap==1的时候，就是直接插入排序



//堆排序
//降序-小堆
//升序-大堆
void _AdjustDown(int* a, int size, int parent) {
	int child = parent * 2 + 1;
	while (child < size) {
		//选出小的那个孩子节点
		if (child + 1 < size && a[child + 1] > a[child]) {
			++child;
		}
		if (a[child] > a[parent]) {
			//向下调整
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			//无需调整
			break;
		}
	}
}
void HeapSort(int* a, int n) {
	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {//n-1是最后一个叶子，n-1-1/2就是第一个非叶子节点,从最后一个有儿子的结点开始下沉
		_AdjustDown(a, n, i);
	}
	int end = n - 1;
	while (end > 0) {
		swap(a[0], a[end]);
		_AdjustDown(a, end, 0);
		--end;
	}
}


//直接选择排序O(n^2)
//插入排序好还是选择排序好？
//插入更好，如果是随机或者接近有序，都是插入快
void SelectSort(int* a, int n) {
	assert(a);
	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int mini = begin;
		int maxi = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (a[i] < a[mini]) {
				mini = i;//更新下标
			}
			if (a[i] > a[maxi]) {
				maxi = i;//更新下标
			}
		}
		//最小的值换到左边，做大的值换到右边
		swap(a[begin], a[mini]);
		//调试会发现是有问题的，如果begin和maxi重叠了的话
		//第一部交换，会导致maxi的数字被换走，发生错误
		//所以
		if (begin == maxi)maxi = mini;
		swap(a[end], a[maxi]);
		//以上是一趟的，迭代起来就可以了
		begin++;
		end--;
		//end和begin 奇数n会相遇，偶数n会错过
	}
}


//冒泡排序
void BubbleSort(int* a, int n) {
	for (int i = 0; i < n - 1; i++) {
		int exchange = 0;
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				exchange = 1;
			}
		}
		if (!exchange)break;
	}
}


//快排--------每一种partsort-----找出坑的位置
// 
// 
// 
//优化-三数取中
int GetMidIndex(int* a, int begin, int end) {
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid]) {
		if (a[mid] < a[end]) {
			return mid;
		}
		else if (a[begin] < a[end]) {
			return end;
		}
		else {
			return begin;
		}
	}
	else {//a[begin]>a[mid]
		if (a[mid] > a[end]) {
			return mid;
		}
		else if (a[begin] < a[end]) {
			return begin;
		}
		else {
			return end;
		}
	}
}
//hoare版本        O(nlogn)
//1.选出一个key，一般是最左边或者最右边的值
//2.单趟排完之后：要求左边比key小，右边比key大
//左边key，右边先走
//右边key，左边先走
//每次排完一趟，key的位置的值就是准确的了，不用动了
int PartSort1(int* a, int begin, int end) {//hoare
	int left = begin;
	int right = end;
	int keyi = left;//保存下标，也就是指针是最优的
//下面是单趟
	while (left < right) {//相遇就停下来
		//右边先走，找小
		while (left < right && a[right] >= a[keyi])--right;//while一定要带等号，否则会死循环
		                                               //而且要带多一个调节，否则有可能会越界
		//左边再走，找大
		while (left < right && a[left] <= a[keyi])++left;
		//交换
		swap(a[left], a[right]);
	}
	//交换key和相遇位置换
	swap(a[keyi], a[right]);
//为什么左边做key，要让右边先走？
//因为要保证相遇的位置的值比key小

	keyi = left;
	//[begin,keyi-1]和[keyi+1,end]有序即可
	return keyi;
}
//挖坑法
//和hoare相同的地方就是-排完单趟-做到key左边比key小，右边比key大
int PartSort2(int* a, int begin, int end) {
	int key = a[begin];
	int piti = begin;//begin是第一个坑
	int left = begin;
	int right = end;
	while (left < right) {
		//右边找小，填到左边的坑
		while (left < right && a[right] >= key) {
			right--;
		}
		a[piti] = a[right];
		piti = right;//自己变成坑
		while (left < right && a[left] <= key){
			left++;
		}
		a[piti] = a[left];
		piti = left;
	}
	//一定相遇在坑的位置
	a[piti] = key;
	return piti;
}
//前后指针版
int PartSort3(int* a, int begin, int end) {
	//排完之后prev之前的比prev小，prev后的比prev大
	int prev = begin;
	int cur = begin + 1;//一开始cur和prev要错开
	int keyi = begin;

	//加入三数取中的优化
	int midi = GetMidIndex(a, begin, end);
	swap(a[keyi], a[midi]);//这样换一下，key就变成GetMidIndex()函数的取值了-后面的代码都不变了

	while (cur <= end) {
		//如果cur的值小于keyi的值
		if (a[cur] < a[keyi] && ++prev != cur) {//只有这种情况要处理一下
			swap(a[prev], a[cur]);
		}
		++cur;
	}
	swap(a[prev], a[keyi]);
	keyi = prev;
	return keyi;
}
void _QuickSort(int* a, int begin, int end) {
	//记录递归次数
	callCount++;
	//区间不存在或者只会有一个值不需要再处理
	//快排：每次把key弄好，递归解决key两边的数
	if (begin >= end)return;
	//小区间优化
	if (end - begin > 10) {
		int keyi = PartSort3(a, begin, end);//每一个partsort负责找到key
		_QuickSort(a, begin, keyi - 1);
		_QuickSort(a, keyi + 1, end);
	}
	else {
		InsertSort(a + begin, end - begin + 1);//注意+1和a+begin
	}
}
//但是以上三种找key的方法，如果在数组是有序的时候，效率就会很低
//效率变成
//n+n-1+n-2+n-3.....
//O(n^2)
//而且因为递归，所以如果数字稍微大一些，就会出现栈溢出
//我们可以用TestOP来测试
//如果用快排来排有序的时候，在debug版本小就可能会爆
//而且效率会变得非常低

//所以要优化
//1.随机选key
//2.三数取中--第一个，中间，最后一个 选中间那个
//3.小区间优化--当区间比较小的时候，就不再递归划分去排序这个小区间。可以考虑其他排序
//  直接用插入排序
//我们用callCount就可以很好的看出，递归次数其实减少了非常多

//如果想看递归次数怎么办
//加一个callCount变量
//但是这样就会出现一些问题
//如果加在.h文件里面，在sort.c,test.c里面都会展开
//这样会出现重定义的问题(链接问题)
//如果我们加一个static，那么sort.c，sort.h，test.c里面的callCount就互不影响，也不行，不知道在哪打印了


// 快速排序 非递归实现
//递归改非递归
//递归是肯定存在一个缺陷的
//如果递归深度太深，就会出现stackoverflow
#include<stack>
void QuickSortNonR(int* a, int begin, int end) {
	//1.直接改循环
	//2.用数据结构栈模拟递归过程
	stack<int>st;
	st.push(end);
	st.push(begin);
	//栈里面没有区间了，就结束了
	while (!st.empty()) {
		int left = st.top();
		st.pop();

		int right = st.top();
		st.pop();

		int keyi = PartSort3(a, left, right);
		//[left,keyi-1]keyi[keyi+1,right]
		
		//怎么迭代
		//先入右再入左

		//栈里面的区间都会拿出来，单趟排序分割，子区间再入栈
		if (left < keyi - 1) {
			st.push(keyi - 1);
			st.push(left);
		}
		if (keyi + 1 < right) {
			st.push(right);//同样，先入右再入左
			st.push(keyi + 1);
		}
	}
}
//
void QuickSort(int* a, int n) {
	int begin = 0;
	int end = n - 1;
	_QuickSort(a, begin, end);
}
//其实如果用队列来实现
//其实就是dfs和bfs的区别
//用栈来实现的话，就是模拟dfs
//如果用队列就是bfs
//和二叉树的遍历有一定相同的地方


//归并排序
//本质是分治
void _MergeSort(int* a, int begin, int end, int* tmp) {
	//区间不存在，或者区间只有一个值，所以是>=
	if (begin >= end)return;
	int mid = (begin + end) / 2;
	//[begin,mid][mid+1,end]
	//分治递归，让子区间有序
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid + 1, end, tmp);
	//现在已经左右区间有序了，我们要开始归并了！
	//其实就是一个后序的过程
	//下面就是把这两个区间归并一下	[begin,mid][mid+1,end]
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin1;//注意，不是拷贝到tmp的最开始的位置，而是begin1的位置
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] < a[begin2]) {
			tmp[i++] = a[begin1++];
		}
		else {
			tmp[i++] = a[begin2++];
		}
	}
	//剩下的还没走完
	while (begin1 <= end1) {
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2) {
		tmp[i++] = a[begin2++];
	}
	// 把归并的数据拷贝回原来的数组
	memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));//注意这里的a+begin和tmp+begin
}
void MergeSort(int* a, int n) {
	//要先开一个数组用来归并
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == nullptr) {
		perror("malloc:");
		exit(-1);
	}
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}


//非递归用栈适合前序不适合后序
//非递归的思路，直接分成一个一个，然后两个两个，然后四个四个合并...
//可以控制一个gap
//一开始gap是1
//然后gap是2...
void MergeSortNonR(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == nullptr) {
		perror("malloc:");
		exit(-1);
	}
	//
	int gap = 1;
	while (gap < n) {
		for (int i = 0; i < n; i += 2 * gap) {//为什么是i+=2*gap,因为两组两组归并，所以一次跳过两组gap
			//[i,i+gap-1][i+gap,i+2*gap-1]....的区间，分别归并
			//归并的代码和上面递归法类似
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			//修正边界-解决越界问题
			if (end1 >= n) {
				//如果end1越界
				end1 = n - 1;//直接修正end1
				//如果end1越界了，那么begin2，end2怎么办
				//修正为不存在的区间
				//[begin2,end2]要是不存在的区间
				begin2 = n;
				end2 = n - 1;
				//这里是不能直接break的，因为这样会导致多出来的数据不拷贝回去，因为拷贝在后面
			}
			else if (begin2 >= n) {
				//把begin2修正为一个不存在的区间
				begin2 = n;
				end2 = n - 1;
			}
			else if (end2 >= n) {//不能用else，因为没越界的不能去修正
				end2 = n - 1;//谁越界了就修正谁
			}
			//因为我们这里是整组整组拷贝回去的，所以不能直接break
			//如果break直接不归，那么下main每一个循环结束都要拷贝一次
			//所以还是要归，而归的大思路就是修正边界

			//修正过后，如果区间不存在，下面的循环就不会进去


			int j = begin1;//注意，不是拷贝到tmp的最开始的位置，而是begin1的位置
			while (begin1 <= end1 && begin2 <= end2) {
				if (a[begin1] < a[begin2]) {
					tmp[j++] = a[begin1++];
				}
				else {
					tmp[j++] = a[begin2++];
				}
			}
			//剩下的还没走完
			while (begin1 <= end1) {
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2) {
				tmp[j++] = a[begin2++];
			}
		}
		memcpy(a, tmp, sizeof(int) * n);//全部处理完了再一次性拷贝回去
		//以上是gap=1的时候的控制，我们再套一个循环控制gap即可
		gap *= 2;//控制gap
	}
	free(tmp);
}
//如果这个非递归，不加任何边界处理，是肯定会越界的，因为算gap的时候，i直接把下标跳过去了，因为直接加了两倍的gap
//其实只有一个值不会越界，只有begin1不会越界，其它都会越界


//非比较排序
//桶排序
//基数排序
//计数排序



//计数排序
//适合范围集中，数据重复的
//时间复杂度O(max(range,N))
//空间复杂度O(range)
void CountSort(int* a, int n) {
	//要先算最小值和最大值
	int min = a[0];
	int max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] < min) {
			min = a[i];
		}
		if (a[i] > max) {
			max = a[i];
		}
	}
	//
	int range = max - min + 1;//注意+1
	int* hash = (int*)malloc(sizeof(int) * range);
	if (hash == nullptr) {
		perror("malloc");
		exit(-1);
	}
	memset(hash, 0, sizeof(int) * range);

	for (int i = 0; i < n; i++) {
		++hash[a[i] - min];
	}
	//重新拿出来
	//排序
	int j = 0;
	for (int i = 0; i < range; i++) {
		//出现几次写几个
		while (hash[i]--) {
			a[j++] = i + min;
		}
	}
}


//直接插入排序：稳定
//希尔排序：不稳定  （预排的时候，相同的数据可能会被分到不同组里面去了）
//选择排序：不稳定  （网上有些资料和书籍说它是稳定的，这是不正确的）
//堆排序：不稳定
//冒泡排序：稳定
//快速排序：不稳定
//归并排序：稳定