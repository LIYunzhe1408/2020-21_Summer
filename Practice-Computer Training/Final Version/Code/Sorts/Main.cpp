// Main.cpp
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"
using namespace std;

double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	const double c = 1.0/CLOCKS_PER_SEC;
	static double t = double(clock());				// ��̬�ֲ���������һ�ε���ʱ��ȷ����ʱ���
	if(restart) t = double(clock());				// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c*(double(clock())-t);					// ����һ��ʱ�㵽������������ʱ��
}

template <typename T> void InitData(T *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = T(T(n)-1-i);				break;	// ���򣨴Ӵ�С��
	case 0:	 for(i=0; i<n; i++) data[i] = T(i);					break;	// ˳�򣨴�С����
	case 1:  for(i=0; i<n; i++) data[i] = (T)UniformRand(54.0,90.0);break;	// [54,90]�ϵľ��ȷֲ�
	default: for(i=0; i<n; i++) data[i] = (T)GaussRand(72.0, 6.0*6.0);break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

template <typename T> void Test(const T &x)					// ���ñ�������ʵ�ε�ֵ����Ҫ����Ҫ����ʵ�ε���������
{
	T *data0=NULL, *data=NULL;								// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = {"��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�"};	// C-�ַ�������
	char algo[][20] 	= {"ð������", "ѡ������", "��������"};				// C-�ַ�������
	void (*f[])(T*, int) = {Bubble, Select, Qsort};			// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, j, n, m = sizeof(f)/sizeof(*f);					// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	bool flag[20];											// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];											// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��
	int cmp = 0;
	for(j=2; j>=-1; j--)									// ���ݷֲ�����
	{
		cout << "\n��������: " << typeid(T).name() << " (" << InitConf[j+1] << ")" << endl;
		for(i=0; i<m; i++)
			cout << '\t' << algo[i];
		cout << endl;
		for(n=1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// �������ѿռ�
			InitData(data0, n, j);							// ����ԭʼ����
			cout << n;
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
//					break;
				ReSet(data, data0, n);						// �ָ�ԭʼ����
				gettime(1);									// ���ü�ʱ���
				f[i](data, n);								// �� i �������㷨
				t[i] = gettime();							// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i] = Check(data, n);					// �����������ȷ��
			}
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
//					cout << "\t" << endl;
//				else
					cout <<'\t' << t[i] << '\t';
			}
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
//					cout << "\t�����������ڵݹ���̫����ܵ���ջ�������������";
//				else
					cout << '\t' << algo[i] << (flag[i]?": ��ȷ":": ����");
			}
			cout << endl;
			FreeMemory(data, data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

int main()						// ������
{
	void TestString();			// ����ԭ�ͣ���������
	srand((unsigned int)time(NULL));			// ���������������������
	int choice;
	char quit_sign = 'Y';
	while (quit_sign != 'n' && quit_sign != 'N')
	{
		cout << "                       Please input the number you want." << std::endl << std::endl << std::endl;
		cout << "                      ******************   �����Ż�   ******************" << std::endl;
		cout << "                      *               Patch 1.5 2021.7.5               *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *                1.����int��������               *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *               2.����double��������             *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *               3.����Score��������              *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *              4.����C-�ַ�����������            *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *                     5. �˳�                    *" << std::endl;
		cout << "                      *                Thank you for using             *" << std::endl;
		cout << "                      **************************************************" << std::endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case(1):
			Test(int(0));				// ����int��������
			break;
		case(2):
			Test(double(0));			// ����double��������
			break;
		case(3):
			TestScore();				// ����Score��������
			break;
		case(4):
			TestString();				// ����C-�ַ����������򣨶��ִ洢��ʽ��
			break;
		case(5):
			return 0;
		default:
			break;
		}
		system("pause");
		cout << "Do you want to see another one?" << std::endl;
		cin >> quit_sign;
		system("cls");
	}
	cout << "******************   �����Ż�   ******************" << std::endl;
	cout << "*               Patch 1.5 2021.7.5               *" << std::endl;
	cout << "*                                                *" << std::endl;
	cout << "*                Thank you for using             *" << std::endl;
	cout << "*                                                *" << std::endl;
	cout << "**************************************************" << std::endl;
	return 0;
}
