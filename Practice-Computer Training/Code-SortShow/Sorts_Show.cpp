// Sorts_Show.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h中）
#include "SortShow.h"
#include <conio.h>

void Bubble_Sort(int *array, int length)
{
	int n = 0;
	int h = 0;
	int pos;
	int k = length - 1;
	ShowText(col1-4, top-1, 0, 15, "︻");
	ShowText(col1-4, top+length, 0, 15, "︼");
	/******************************************/
	for(int i=0; i<k; i++)
	{
		pos = 0;
		for(int j=n; j<k; j++)
		{
			if(array[j] > array[j+1])		// 有元素需要交换时
			{
				SWAP(array, j, j+1);
				pos = j;
			}
			else							// 无元素需要交换时，展示曾比较过
				ShowBars(col1, top+j, array[j], col1, top+j+1, array[j+1]);
		}
		ShowText(col1-4, top+length-i+1, 0, 15, "  ");
		ShowText(col1-4, top+length-i, 0, 15, "︼");
		
		k = pos;
		for(int j=k; j>n; j--)
		{
			if(array[j] < array[j-1])		// 有元素需要交换时
				SWAP(array, j, j-1);
			else							// 无元素需要交换时，展示曾比较过
				{ShowBars(col1, top+j, array[j], col1, top+j-1, array[j-1]);}
				h = j;
		}
		
		ShowText(col1-4, top-h+1, 0, 15, "  ");
		ShowText(col1-4, top-h, 0, 15, "︻");
	}
	
	ShowText(col1-4, top+1, 0, 15, "  ");
	ShowText(col1-4, top-1, 0, 15, "  ");
}

void Select_Sort(int *array, int length)	// 选择排序
{
	int start = 0;
	int end = length - 1;
	while (end > start + 1) 
	{
		ShowText(col1 - 4, start , 0, 15, "︻ ");
		ShowText(col1 - 4, end+2 , 0, 15, "︼ ");
		int minIndex = start;
		int maxIndex = start;

		ShowText(col1 - 4, minIndex + 1, 0, 15, "min");
		ShowText(col1 - 8, maxIndex + 1, 0, 15, "max");

		for (int i = start + 1; i <= end; i++) {
			if (array[i] < array[minIndex]) {
				ShowText(col1 - 4, minIndex + 1, 0, 15, "   ");
				minIndex = i;
				ShowText(col1 - 4, minIndex +1, 0, 15, "min");
			}
			else if (array[i] >= array[maxIndex]) {
				ShowText(col1 - 8, maxIndex + 1, 0, 15, "   ");
				maxIndex = i;
				ShowText(col1 - 8, maxIndex + 1, 0, 15, "max");
			}
		}

		if (minIndex != start) {
			SWAP(array, start, minIndex);
			ShowText(col1 - 4, minIndex + 1, 0, 15, "   ");
			ShowText(col1 - 4, start + 1, 0, 15, "min");
		}

		if (maxIndex == start) {
			ShowText(col1 - 4, minIndex + 1, 0, 15, "   ");
			ShowText(col1 - 8, maxIndex + 1, 0, 15, "   ");
			maxIndex = minIndex;
			ShowText(col1 - 4, minIndex + 1, 0, 15, "min");
			ShowText(col1 - 8, maxIndex + 1, 0, 15, "max");
		}
		if (maxIndex != end) {
			SWAP(array,end, maxIndex);
			ShowText(col1 - 8, maxIndex + 1, 0, 15, "   ");
			ShowText(col1 - 8, end + 1, 0, 15, "max");
		}

		for (int k = 0; k <= length; k++)
		{
			ShowText(col1 - 8, k + 1, 0, 15, "   ");
			ShowText(col1 - 4, k + 1, 0, 15, "   ");

			ShowText(col1 - 4, k, 0, 15, "   ");
			ShowText(col1 - 4, k + 2, 0, 15, "   ");
		}
		start++;
		end--;
	}

	if (end == start + 1) {
		if (array[end] < array[start]) {

			SWAP(array,start, end);
			ShowText(col1 - 8, end + 1, 0, 15, "max");
			ShowText(col1 - 4, start + 1, 0, 15, "min");
		}
	}
	

}

void Merge_Sort(int *a, int size)
{
	int r = 2;
	if(size<=1)
		return;
	if(size==2)
	{
		if(a[0] > a[1])
			SWAP(a, 0, 1);
		else
			ShowBars(col1, top+a-array, a[0], col1, top+a-array+1, a[1]);
		return;
	}
	int i=0, j=0, k=0, len1=size/2, len2=size-size/2;
	int *b=a+len1;
	Merge_Sort(a, len1);
	Merge_Sort(b, len2);

	ShowText(col1-3, top+a-array, 0, 15, "︻");
	ShowText(col1-3, top+b-array, 0, 15, "—");
	ShowText(col1-3, top+b-array+len2, 0, 15, "︼");

	for(i=0; i<len1; i++)
	{
		MoveBar(col1, a-array+i+top, r*a[i], col2, i+top);
		temp[i] = a[i];
	}
	getch();

	i = j = k = 0;
	for(i=j=0; i<len1 && j<len2; k++)
	{
		if(temp[i]<=b[j])
		{
			MoveBar(col2, i+top, r*temp[i], col1, a-array+k+top);
			a[k] = temp[i++];
		}
		else
		{
			MoveBar(col1, b-array+j+top, r*b[j], col1, a-array+k+top);
			a[k] = b[j++];
		}
		getch();
	}
	while(i<len1)
	{
		MoveBar(col2, i+top, r*temp[i], col1, a-array+k+top);
		a[k++] = temp[i++];
	}
	while(j<len2)
	{
		MoveBar(col1, b-array+j+top, r*b[j], col1, a-array+k+top);
		a[k++] = b[j++];
	}
	ShowText(col1-3, top+a-array, 0, 15, "  ");
	ShowText(col1-3, top+b-array, 0, 15, "  ");
	ShowText(col1-3, top+b-array+len2, 0, 15, "  ");
}

void Quick_Sort(int *a, int size)
{
	char lStr[]="{[(<abcdefghijkl", rStr[]="}])>ABCDEFGHIJKL";	// 展示递归过程中的"层次"
	int left=0, right=size-1;
	int pivot = a[right];			// 以右端的值为轴（值）
	static int layer=-1;			// 局部静态变量，记录递归的层数

	layer++;
	if(size<=1)
	{
		layer--;
		return ;
	}
	ShowChar(col1-6-2*layer, top+a-array, 0, 15, lStr[layer]);
	ShowChar(col1-6-2*layer, top+a-array+size-1, 0, 15, rStr[layer]);
	ShowText(col1-2, top+a-array+size-1, 0, 15, "*");
	if(size==2)
	{
		if(a[0] > a[1])
		{
			SWAP(a, 0, 1);
		}
		ShowText(col1-2, top+a-array+size-1, 0, 15, " ");
		layer--;
		return;
	}
	do
	{
		ShowText(col1-4, top+a-array+left, 0, 15, "L");
		ShowText(col1-3, top+a-array+right, 0, 15, "R");
		while(left < right && (a[left] <= pivot))
		{
			ShowBars(col1, top+a-array+left, a[left], col1, top+a-array+size-1, pivot);
			left++;						// 找到左侧严格大于轴值的元素（下标）
			ShowText(col1-4, top+a-array+left-1, 0, 15, " ");
			ShowText(col1-4, top+a-array+left, 0, 15, "L");
		}
		while(left < right && (pivot <= a[right]))
		{
			ShowBars(col1, top+a-array+right, a[right], col1, top+a-array+size-1, pivot);
			right--;					// 找到右侧严格小于轴值的元素（下标）
			ShowText(col1-3, top+a-array+right+1, 0, 15, " ");
			ShowText(col1-3, top+a-array+right, 0, 15, "R");
		}
		if(left < right)
		{
			SWAP(a, left, right);
		}
	}while(left < right);
	SWAP(a, left, size-1);				// 至此，left以左全不超过轴值，left到位，left以右全部小于轴值
	ShowText(col1-1, top+a-array+left, 0, 15, "-");
	ShowText(col1-4, top+a-array+left, 0, 15, " ");
	ShowText(col1-3, top+a-array+right, 0, 15, " ");

	ShowText(col1-2, top+a-array+size-1, 0, 15, " ");

	Quick_Sort(a, left);				// 递归处理a[0],...,a[left-1]（长度left）
	ShowText(col1-1, top+a-array+left, 0, 15, " ");
	Quick_Sort(a+left+1, size-left-1);	// 递归处理a[left+1],...,a[size-1]（长度size-left-1）
	layer--;
}
