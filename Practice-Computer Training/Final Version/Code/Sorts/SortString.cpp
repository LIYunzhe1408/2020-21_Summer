// SortString.cpp
/* 思考题
1.	下面的测试函数中，strA、strB、strC、strD联系的C-字符串数组的内容存储在内存的什么区域？
2.	设计BubbleA，BubbleB两个函数之前，思考
	(1) 如何比较两个字符串的内容？
	(2) 存储在什么区域的字符串能交换其内容？
	(3) 若不能交换字符串的内容，排序操作中交换什么？
3.	GetStrings为什么要设计成函数模板，两次调用时，其第二个参数分别是实例化成什么？
4.	GetStrings和FreeStrings函数的第一个参数为什么要使用引用型参数传递二级指针？如果不用引用型参数，会有什么结果？
由此可见，对指针数组来说，首先它是一个数组，数组的元素都是指针，也就是说该数组存储的是指针，数组占多少个字节由数组本身决定；
而对数组指针来说，首先它是一个指针，它指向一个数组，也就是说它是指向数组的指针，在 32 位系统下永远占 4 字节，至于它指向的数组占多少字节，这个不能够确定，要看具体情况



*/
#include <iostream>
#include <cstring>
using namespace std;

#define NUM 20

void BubbleA(char (*str)[NUM], int size)			// 数组指针    它指向一个包含 NUM个 char 类型数据的数组
{
	char temp[20];
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (*str[j] > *str[j + 1])
			{
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
			else if (*str[j] == *str[j + 1])
			{
				int flag = 1;
				while (flag != 0)
				{
					for (int k = 1; ; k++)
					{
						if (str[j][k] > str[j + 1][k])      //比较首字母后的每一个字母
						{
							strcpy(temp, str[j]);
							strcpy(str[j], str[j + 1]);
							strcpy(str[j + 1], temp);
							flag = 0;
							break;
						}
						else if (str[j][k] = str[j + 1][k])
						{
							continue;
						}
					}
				}


			}
		}
	}
}

void BubbleB(char *str1[], int size)					// 指针数组   该数组包含NUM个指向char类型数据的指针
{
	char *temp;
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (*str1[j] > *str1[j + 1])
			{
				temp = str1[j];
				str1[j] = str1[j + 1];
				str1[j+1] = temp;
			}
			else if (*str1[j] == *str1[j + 1])
			{
				int flag = 1;
				while (flag != 0)
				{
					for (int k = 1; ; k++)
					{
						if (*(str1[j] + k) > *(str1[j+1] + k))      //比较首字母后的每一个字母
						{
							temp = str1[j];
							str1[j] = str1[j + 1];
							str1[j + 1] =  temp;
							flag = 0;
							break;
						}
						else if (*(str1[j]+k) == *(str1[j+1]+k))
						{
							continue;
						}
					}
				}

			}
		}
	}

}

template <typename T> void ShowStrings(const char *prompt, const T *strs, int n)
{
	if(n>0)
		cout << prompt << strs[0];
	for(int i=1; i<n; i++)
		cout << ", " << strs[i];
	cout << endl;
}

template <typename T> void GetStrings(char **&dest, const T *source, int n)
{
	dest = new char*[n];
	if(dest == NULL) return;
	int len;
	for(int i=0; i<n; i++)
	{
		len = strlen(source[i]);
		dest[i] = new char[len+1];
		strcpy(dest[i], source[i]);
	}
}

void FreeStrings(char **&strs, int n)
{
	if(strs!=NULL)
	{
		for(int i=0; i<n; i++)
			if(strs[i]!=NULL)
				delete [] strs[i];
		delete [] strs;
		strs = NULL;
	}
}

void TestString()
{
	char strA[][NUM]={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
	char *strB[]    ={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "an", "cake", "side"};
	char **strC, **strD;
	int n1 = sizeof(strA)/sizeof(*strA), n2 = sizeof(strB)/sizeof(*strB);
	GetStrings(strC, strA, n1);
	GetStrings(strD, strB, n2);

	cout << "\n\t*** 多种不同存储方式的C-字符串数组的排序 ***" << endl;
	ShowStrings("\n原始数据: ", strA, n1);
	BubbleA(strA, n1);
	ShowStrings("排序结果: ",   strA, n1);
	

	ShowStrings("\n原始数据: ", strB, n2);
	BubbleB(strB, n2);
	ShowStrings("排序结果: ",   strB, n2);
	
	ShowStrings("\n原始数据: ", strC, n1);
	BubbleB(strC, n1);						// 调用一个排序函数执行排序操作
	ShowStrings("排序结果: ",   strC, n1);

	ShowStrings("\n原始数据: ", strD, n2);
	BubbleB(strD, n2);						// 调用一个排序函数执行排序操作
	ShowStrings("排序结果: ",   strD, n2);

	FreeStrings(strC, n1);
	FreeStrings(strD, n2);
}
