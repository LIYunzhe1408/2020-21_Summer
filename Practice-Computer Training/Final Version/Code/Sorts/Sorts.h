// Sorts.h		���֣�ð�ݡ�ѡ�񡢿��٣����������㷨������
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;

template <typename T> void __QuickSort(T arr[], int l, int r);
template <typename T> int __partition(T arr[], int l, int r);
template <typename T> void insertSort(T arr[], int startindex, int endindex);
double gettime(int restart=0);


template <typename T> void GetMemory(T *&data, T *&data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{																	// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(data0!=NULL) delete [] data0;								// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(data !=NULL) delete [] data;
	data0 = new T[n];												// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(data0!=NULL) delete [] data0;
	if(data !=NULL) delete [] data;
	data0 = data = NULL;											// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

template <typename T> void ReSet(T *data, const T *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	for(int i=0; i<n; i++)
		data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// ��������Ԫ���Ƿ��Ѱ���������
{
	for(int i=1; i<size; i++)
		if(a[i-1] > a[i])
			return false;
	return true;
}

// �����Ż��������㷨
template <typename T> void Bubble(T* a, int size)	// ð������
{
	T temp;										// ����һ���ֲ�������������������ʽ����������ͬ
	int j = 0;
	int n = 0;                                   //ͬʱ����˫��ð����Ҫ�����±����
	int flag;
	int pos;//������¼���һ�ν�����λ��
	int k = size - 1;
	int l = 0;
	int cmp = 0;
	while (n < k)//ȷ����������
	{
		pos = 0;
		flag = 0;
		//����ð��
		for (j = n; j < k; j++)//ȷ���Ƚϴ���
		{
			cmp++;
			if (a[j] > a[j + 1])
			{
				//����
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;//������
				pos = j;//����Ԫ�أ���¼���һ�ν�����λ��
			}
		}
		if (flag == 0)//���û�н�����Ԫ�أ����Ѿ�����,ֱ�ӽ���
		{
			return;
		}
		k = pos;//��һ�αȽϵ���¼λ�ü���
		//����ð��
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
		if (flag == 0)//���û�н�����Ԫ�أ����Ѿ�����,ֱ�ӽ���
		{
			return;
		}
	}
}

template <typename T> void Select(T *a, int size)	// ѡ������
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

template <typename T> void Qsort(T* a, int size)	// ��������
{
	__QuickSort(a, 0, size - 1);
}

template <typename T> void __QuickSort(T arr[], int l, int r)
{

	//�Ż�1����������ʱʹ�� �������� �ӿ������ٶ�
	if (l >= r) {
		insertSort(arr, l, r);
		return;
	}
	int p = __partition(arr, l, r);
	__QuickSort(arr, l, p - 1);
	__QuickSort(arr, p + 1, r);
}

template <typename T> int __partition(T arr[], int l, int r) {
	//�Ż�2��ʹ������ڱ�������Ϊ�漴��������
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
