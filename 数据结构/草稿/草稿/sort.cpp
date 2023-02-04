#define _CRT_SECURE_NO_WARNINGS 1
#include"sort.h"

//使用数组和指针，不使用vector
void BubbleSort(int* arr, int sz) {
	for (int i = 0; i < sz - 1; i++) {//外层循环
	//tips:只需要sz-1次，因为最后一次是没有两个数可以交换了
		int if_swap = 0;
		for (int j = 0; j < sz - 1 - i; j++) {//这里的sz-1-i，我们只要画一画，把例子写出来就可以很好地明白，这里不赘述了
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);//交换两者的值，注：C语言实现swap需要传地址。
				if_swap = 1;
			}
		}
		//每一轮走完之后，如果if_swap==0;直接return
		if (if_swap == 0)
			return;
	}
}

void SelectSort(int* arr, int sz) {
	int i = 0;
	int j = 0;
	for (i = 0; i < sz - 1; i++) {
		int min = i;
		for (j = i + 1; j < sz; j++) {
			//从下标为arr[i+1]开始找
			//是<sz，因为最后一个元素也要比较
								  //上面<sz-1的原因是，总体循环只需要sz-1次，最后一次不用排了
								  //和冒泡的外层循环原理一样
			if (arr[j] < arr[min]) {
				min = j;//打擂台
			}
		}
		//出了这层循环之后，交换min和i的值，把i后面最小的放到i的位置
		swap(arr[i], arr[min]);//交换二者的值
	}
}



//使用c，cpp共有的数组
void InsertSort(int* arr, int sz) {
	int sortNum = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++) {
		sortNum = arr[i];//要排序的数字
		for (j = i - 1; j >= 0; j--) {//因为要从待排序那个数的前一个数开始，往后挪一个
			//从后往前挪动，所以用反向循环
			//先判断，因为只需要挪动比待排序数字大的数字
			if (arr[j] < sortNum) {
				break;
			}
			arr[j + 1] = arr[j];//一个个挪动数据
		}
		arr[j + 1] = sortNum;//因为是j指向的数字小于sort才出循环的
		//所以此时的j指向空位置前一个位置，所以arr[j+1]=sort;
	}
}



void sort_in_group(int* arr, int sz, int pos, int step) {
	int sortNum = 0;
	int i = 0;
	int j = 0;
	for (i = pos + step; i < sz; i += step) {
		//pos+step就是该组第一个元素的位置
		//例如：当pos==0的时候，该组第一个元素就是整个序列第一个元素
		//当pos=1的时候，该组第一个元素就是整个序列第二个元素
		sortNum = arr[i];//要插入的数
		for (j = i - step; j >= 0; j -= step) {
			//i-step就是该组最后一个元素，结合上面给的图可以更好的理解
			if (arr[j] < sortNum) {
				break;
			}
			arr[j + step] = arr[j];//挪动数据，普通插排是一个一个挪，这个是，隔step个挪，道理是一样的，静下心思考就能很好地理解。
		}
		arr[j + step] = sortNum;
	}
}
void ShellSort(int* arr, int sz) {
	int i = 0;
	int step = 0;
	//step为步长，每次减少为原来的一半，取整数，最后一次必定为1
	for (step = sz / 2; step > 0; step /= 2) {
		//步长为step，即共有istep个组，对每一组都执行插入排序
		for (i = 0; i < step; i++) {
			//这个每一组的排序groupSort就是插入排序稍微改变一点的版本
			sort_in_group(arr, sz, i, step);
			//i=0的时候，第三个参数是0，结合那张图，也就是红色那组进行插排
			//i=1的时候，第三个参数是1，结合图，也就是绿色那组进行插排
			//后面的同理
			//step毋庸置疑，肯定是要传的
		}
	}
}


enum {
	LEFT,//表示左下标动
	RIGHT//表示又下标动
};
void QuickSort(int* arr, size_t sz) {
	if (sz < 2)
		return;//如果数组元素小于两个就不用排了
	int pivot = arr[0];//首先选取最左边的数为中心轴
	int ileft = 0;//控制下标
	int iright = sz - 1;
	int imoving = RIGHT;//当前应该移动的下标，LEFT表示要移动左下标，RIGHT表示移动右下标
	//因为一开始先把最左边空出来了，所以下标一开始从右边开始走

	while (ileft < iright) {//一轮排序结束的标志为左右下标重叠
		if (imoving == RIGHT) {
			if (arr[iright] >= pivot) {//如果右下标所对应的数比基准数大，表示不用动
				iright--;//直接下标减减
				continue;//进入到下一轮移动下标操作
			}
			else if (arr[iright] < pivot) {//如果右下标所对应的数比基准数小，把这个数丢到坑里。
			//更换该移动的下标
				arr[ileft] = arr[iright];
				ileft++;//左下标++
				imoving = LEFT;//更换
				continue;
			}
		}
		//另一边是同样道理的
		if (imoving == LEFT) {
			if (arr[ileft] <= pivot) {
				ileft++;
				continue;
			}
			else if (arr[ileft] > pivot) {
				arr[iright] = arr[ileft];
				iright--;
				imoving = RIGHT;
				continue;
			}
		}
	}
	arr[ileft] = pivot;//别忘了把基准值放进来
	//到这里我们完成了一轮排序
	//此时的基准值换到最后的坑里了
	QuickSort(arr, ileft);//基准值左边序列快排
	QuickSort(arr + ileft + 1, sz - ileft - 1);//基准值右边序列快排
}






//arr-待排序数组的首地址，arrtmp-用于排序的临时数组的首地址
//start-排序区间第一个元素的位置，end-排序区间最后一个元素的位置
//注：
//这里的istart1，iend1，istart2，iend2都是下标，不是指针，当然，用指针实现也是可以的
void _mergeSort(int* arr, int* arrtmp, int start, int end) {
	//如果start>=end，表示该区间的元素少于两个，递归终止
	if (start >= end) return;

	int mid = start + (end - start) / 2;//找到排序中间位置
	//把一个数组分为两个区间
	int istart1 = start;
	int iend1 = mid;

	int istart2 = mid + 1;
	int iend2 = end;
	//对两边分别递归排序
	_mergeSort(arr, arrtmp, istart1, iend1);
	_mergeSort(arr, arrtmp, istart2, iend2);

	//开始合并各个分开的区间
	int i = start;
	//把区间左右两边数列合并到已经排序数组arrtmp中
	while (istart1 <= iend1 && istart2 <= iend2) {
		arrtmp[i] = arr[istart1] < arr[istart2] ? arr[istart1++] : arr[istart2++];
		//此处istart1，istart2后面的++是不能拿到下面来的，因为拿了哪个哪个才要++，另外一个较大的是不用动的
		i++;
	}
	while (istart1 <= iend1) {//如果数组1还有剩，数组1后面的全部跟到arrtmp[]后面即可
		arrtmp[i] = arr[istart1];
		i++;
		istart1++;
	}
	while (istart2 <= iend2) {
		arrtmp[i] = arr[istart2];
		i++;
		istart2++;
	}
	//最后再把arrtmp[]里面的数据拷贝回去
	memcpy(arr + start, arrtmp + start, sizeof(int) * (end - start + 1));
}
void MergeSort(int* arr, int sz) {
	if (sz < 2)return;//小于两个元素不需要排序
	int* arrtmp = (int*)malloc(sz * sizeof(int));//分配一个与待排序数组相同大小的数组
	_mergeSort(arr, arrtmp, 0, sz - 1);
}




void heapify(int* arr, int start, int end) {
	//1.循环法
#if 0
	//确定父结点和左子结点的数组下标
	int dad = start;
	int son = dad * 2 + 1;
	//循环条件：子结点的下标不越界
	while (son <= end) {
		//先比较两个子节点的大小，选大的
		if ((son + 1 <= end) && (arr[son] < arr[son + 1])) {//注意条件防止越界
		//先判断是否右边有兄弟节点才能比较
			son++;//这一步就是从左结点转到右结点
		}
		//如果父结点大于子结点代表该元素不需要下沉或者已调整完毕，直接跳出函数
		if (arr[dad] > arr[son])return;
		//否则交换父子节点内容再继续子结点和孙结点的比较
		swap(arr[dad], arr[son]);
		//迭代
		dad = son;//子结点变成新的父节点，继续循环
		son = dad * 2 + 1;//通过新的父结点找到新的子结点
	}
#endif
	//2.递归法
#if 1
	//确定父结点和左子结点的数组下标
	int dad = start;
	int son = dad * 2 + 1;
	//如果超出范围了，return
	if (son > end) return;//递归结束条件
	//先比较两个子结点，选择大的
	if ((son + 1 <= end) && (arr[son] < arr[son + 1])) {
		son++;//这里和循环法同一个道理
	}
	if (arr[dad] > arr[son]) {
		return;//表示不需要下沉了
	}
	swap(arr[dad], arr[son]);
	//迭代
	heapify(arr, son, end);//子结点成为新的父节点来递归
#endif
}
void HeapSort(int* arr, int sz) {
	int i = 0;
	//1.构建二叉树，构建大顶堆
	//初始化堆，从最后一个父结点开始调整
	for (i = (sz - 1) / 2; i >= 0; i--) {//这里一定要i>=0，因为最顶上的元素也是要下沉的
		//每一个元素都检查一下是否需要下沉
		heapify(arr, i, sz - 1);//heapify元素下沉函数
	}
	//2.把第一个元素和堆最后一个元素交换，然后重新调整，直到排序完毕
	for (i = sz - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		//换完之后重新构建大顶堆
		heapify(arr, 0, i - 1);
	}
}


void BucketSort(int* arr, int sz) {
	int bucket[5][5] = { 0 };//分配五个桶,因为在我们例子中最大的数是49，所以5个桶
	//如果测试用例变了，我们桶的个数也要变
	int bucket_size[5] = { 0 };//每个桶都需要计数，因为我们要知道我们往桶里扔了多少元素
	//把数组arr的数据放到桶里面
	int i = 0;
	for (i = 0; i < sz; i++) {
		//这种方法把每个元素除以十，也就是取十位的方法不是完美的，如果数组里面有50几以上的，五个桶就不够了
		bucket[arr[i] / 10][bucket_size[arr[i] / 10]++] = arr[i];
		//arr[i]/10表示桶的序号，
		//所以bucket_size[arr[i]/10]++]表示相对应桶序号的计数器序号
	}
	//对每个桶进行快排，读者要自己另外调用一种排序方式，这里用快排做例子
	for (i = 0; i < 5; i++) {
		QuickSort(bucket[i], bucket_size[i]);
		//bucket_size[i]表示每个桶里面的元素
	}

	//把每个桶中的数据填充到数组arr中
	//也就是一个简单的把二维数组中的元素放到一个一维数组中
	int j = 0;//和i一起控制二维数组
	int k = 0;//控制arr
	for (i = 0; i < 5; i++) {
		for (j = 0; j < bucket_size[i]; j++) {
			arr[k++] = bucket[i][j];
		}
	}
}



int arrMax(int* arr, int sz) {
	int max = INT_MIN;
	for (int i = 0; i < sz; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
void _radixSort(int* arr, int sz, int exp) {
	int i = 0;//控制循环
	int* ret = (int*)calloc(sz, sizeof(int));//存放从桶收集后的临时数组
	int buckets[10] = { 0 };//只有0-9十种数字，所以10个桶
	/*
	* 这里的一维数组buckets就是这个排序的精妙所在，我们思考的时候是把数字放到桶里面
	* 但是我们实际写代码的时候，是只需要计数就可以了。
	* 因为我们一次排序，也就是一次_radixSort是不用关心其它位数是什么的
	*/
	//遍历arr，将数据出现次数存储在buckets中
	for (i = 0; i < sz; i++) {
		buckets[(arr[i] / exp) % 10]++;
	}
	//下面这两个for，是比较难理解的
	//调整buckets各元素的值，调整后的值就是arr中元素在ret中的位置
	for (i = 1; i < 10; i++) {
		buckets[i] = buckets[i] + buckets[i - 1];//后面有解释
	}
	//将arr中的元素填充到result中
	//以下这个循环非常精妙，我们可以观察到调整bucket[]后里面的数值和排序完之后ret[]里面应有的数值是有一个精妙的关系的
	for (i = sz - 1; i >= 0; i--) {
		int iexp = (arr[i] / exp) % 10;//这个iexp就是我要排的那一位的那个数，比如134，我现在正在排个位，那iexp就是4
													   //我在排十位，iexp就是3
		ret[buckets[iexp] - 1] = arr[i];//后面有解释
		buckets[iexp]--;//每放一个数到ret里，所对应的计数器要减减
	}
	//将排序好的数组ret复制到arr中
	memcpy(arr, ret, sz * sizeof(int));
}
void RadixSort(int* arr, int sz) {
	int imax = arrMax(arr, sz);//获取数组arr中的最大值,因为数组中最大的数决定分配的次数
	int iexp;//排序指数，iexp=1：按各位排序，iexp=10：按十位排序.....
	//从个位开始，对数组arr按指数位进行排序
	for (iexp = 1; imax / iexp > 0; iexp *= 10) {//循环条件恰恰就可以确定我们要循环的次数
		//imax/iexp就是最大循环次数，当iexp增大的时候就会接近这个循环条件
		_radixSort(arr, sz, iexp);//每一次的基数排序
		//iexp告诉_radixSort()这次是要对哪一位数进行排序
	}
}