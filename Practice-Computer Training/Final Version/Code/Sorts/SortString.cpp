// SortString.cpp
/* ˼����
1.	����Ĳ��Ժ����У�strA��strB��strC��strD��ϵ��C-�ַ�����������ݴ洢���ڴ��ʲô����
2.	���BubbleA��BubbleB��������֮ǰ��˼��
	(1) ��αȽ������ַ��������ݣ�
	(2) �洢��ʲô������ַ����ܽ��������ݣ�
	(3) �����ܽ����ַ��������ݣ���������н���ʲô��
3.	GetStringsΪʲôҪ��Ƴɺ���ģ�壬���ε���ʱ����ڶ��������ֱ���ʵ������ʲô��
4.	GetStrings��FreeStrings�����ĵ�һ������ΪʲôҪʹ�������Ͳ������ݶ���ָ�룿������������Ͳ���������ʲô�����
�ɴ˿ɼ�����ָ��������˵����������һ�����飬�����Ԫ�ض���ָ�룬Ҳ����˵������洢����ָ�룬����ռ���ٸ��ֽ������鱾�������
��������ָ����˵����������һ��ָ�룬��ָ��һ�����飬Ҳ����˵����ָ�������ָ�룬�� 32 λϵͳ����Զռ 4 �ֽڣ�������ָ�������ռ�����ֽڣ�������ܹ�ȷ����Ҫ���������



*/
#include <iostream>
#include <cstring>
using namespace std;

#define NUM 20

void BubbleA(char (*str)[NUM], int size)			// ����ָ��    ��ָ��һ������ NUM�� char �������ݵ�����
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
						if (str[j][k] > str[j + 1][k])      //�Ƚ�����ĸ���ÿһ����ĸ
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

void BubbleB(char *str1[], int size)					// ָ������   ���������NUM��ָ��char�������ݵ�ָ��
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
						if (*(str1[j] + k) > *(str1[j+1] + k))      //�Ƚ�����ĸ���ÿһ����ĸ
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

	cout << "\n\t*** ���ֲ�ͬ�洢��ʽ��C-�ַ������������ ***" << endl;
	ShowStrings("\nԭʼ����: ", strA, n1);
	BubbleA(strA, n1);
	ShowStrings("������: ",   strA, n1);
	

	ShowStrings("\nԭʼ����: ", strB, n2);
	BubbleB(strB, n2);
	ShowStrings("������: ",   strB, n2);
	
	ShowStrings("\nԭʼ����: ", strC, n1);
	BubbleB(strC, n1);						// ����һ��������ִ���������
	ShowStrings("������: ",   strC, n1);

	ShowStrings("\nԭʼ����: ", strD, n2);
	BubbleB(strD, n2);						// ����һ��������ִ���������
	ShowStrings("������: ",   strD, n2);

	FreeStrings(strC, n1);
	FreeStrings(strD, n2);
}
