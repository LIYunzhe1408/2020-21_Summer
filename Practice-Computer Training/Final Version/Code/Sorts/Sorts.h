// Sorts.h		三种（冒泡、选择、快速）基本排序算法（升序）
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;

template <typename T> void __QuickSort(T arr[], int l, int r);
template <typename T> int __partition(T arr[], int l, int r);
template <typename T> void insertSort(T arr[], int startindex, int endindex);
double gettime(int restart=0);


template <typename T> void GetMemory(T *&data, T *&data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(data0!=NULL) delete [] data0;								// 先释放原先所"拥有"的堆空间资源
	if(data !=NULL) delete [] data;
	data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
	data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// 释放指针所"拥有"的堆空间资源
{
	if(data0!=NULL) delete [] data0;
	if(data !=NULL) delete [] data;
	data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

template <typename T> void ReSet(T *data, const T *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	for(int i=0; i<n; i++)
		data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// 检验数组元素是否已按升序排列
{
	for(int i=1; i<size; i++)
		if(a[i-1] > a[i])
			return false;
	return true;
}

// 三种优化的排序算法
template <typename T> void Bubble(T* a, int size)	// 冒泡排序
{
	T temp;										// 定义一个局部变量，数据类型与形式数据类型相同
	int j = 0;
	int n = 0;                                   //同时进行双向冒泡需要两个下标遍历
	int flag;
	int pos;//用来记录最后一次交换的位置
	int k = size - 1;
	int l = 0;
	int cmp = 0;
	while (n < k)//确定排序趟数
	{
		pos = 0;
		flag = 0;
		//正向冒泡
		for (j = n; j < k; j++)//确定比较次数
		{
			cmp++;
			if (a[j] > a[j + 1])
			{
				//交换
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;//加入标记
				pos = j;//交换元素，记录最后一次交换的位置
			}
		}
		if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
		{
			return;
		}
		k = pos;//下一次比较到记录位置即可
		//反向冒泡
		for (j = k; j > n; j--)
		{
			cmp++;
			if (a[j] < a[j - 1])
			{
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
				flag = 1;
			}
		}
		n++;
		if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
		{
			return;
		}
	}
}

template <typename T> void Select(T *a, int size)	// 选择排序
{
	T temp;
	int min = 0, max = 0;
	int j = 0;
	int k = size;
	for (int i = 0; i < k; ++i, --k) {
		min = i;
		max = i;
		for (j = i + 1; j < k; ++j) {
			if (a[j] < a[min]) {
				min = j;
			}
			if (a[j] > a[max]) {
				max = j;
			}
		}
		if (min != i) {
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
		if (max == i) {
			max = min;
		}
		if (max != k - 1) {
			temp = a[k - 1];
			a[k - 1] = a[max];
			a[max] = temp;
		}
	}
}

template <typename T> void Qsort(T* a, int size)	// 快速排序
{
	__QuickSort(a, 0, size - 1);
}

template <typename T> void __QuickSort(T arr[], int l, int r)
{

	//优化1：近乎有序时使用 插入排序 加快排序速度
	if (l >= r) {
		insertSort(arr, l, r);
		return;
	}
	int p = __partition(arr, l, r);
	__QuickSort(arr, l, p - 1);
	__QuickSort(arr, p + 1, r);
}

template <typename T> int __partition(T arr[], int l, int r) {
	//优化2：使用随机哨兵，进化为随即快速排序
	swap(arr[l], arr[rand() % (r - r + 1) + l]);
	T tmp = arr[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (arr[i] < tmp) {
			j++;
			swap(arr[j], arr[i]);
		}
	}
	swap(arr[l], arr[j]);
	return j;
}

template <typename T> void insertSort(T arr[], int startindex, int endindex)
{
	T tmp ;
	int i = startindex + 1;
	int j = i - 1;
	for (i; i <= endindex; ++i)
	{
		tmp = arr[i];
		for (j = i - 1; j >= startindex && arr[j] > tmp; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
	}
}

#endif
