// Main.cpp
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"
using namespace std;

double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0/CLOCKS_PER_SEC;
	static double t = double(clock());				// 静态局部变量。第一次调用时，确定计时起点
	if(restart) t = double(clock());				// 根据实参决定是否重新确定计时起点
	return c*(double(clock())-t);					// 从上一计时点到现在所经历的时间
}

template <typename T> void InitData(T *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = T(T(n)-1-i);				break;	// 逆序（从大到小）
	case 0:	 for(i=0; i<n; i++) data[i] = T(i);					break;	// 顺序（从小到大）
	case 1:  for(i=0; i<n; i++) data[i] = (T)UniformRand(54.0,90.0);break;	// [54,90]上的均匀分布
	default: for(i=0; i<n; i++) data[i] = (T)GaussRand(72.0, 6.0*6.0);break;	// 正态分布，均值72，方差36（根方差6）
	}
}

template <typename T> void Test(const T &x)					// 调用本函数的实参的值不重要，重要的是实参的数据类型
{
	T *data0=NULL, *data=NULL;								// 两个指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组
	char algo[][20] 	= {"冒泡排序", "选择排序", "快速排序"};				// C-字符串数组
	void (*f[])(T*, int) = {Bubble, Select, Qsort};			// 函数指针数组（元素为一系列函数的入口地址）
	int i, j, n, m = sizeof(f)/sizeof(*f);					// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	bool flag[20];											// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];											// 同上。记录不同算法的执行时间
	int cmp = 0;
	for(j=2; j>=-1; j--)									// 数据分布类型
	{
		cout << "\n数据类型: " << typeid(T).name() << " (" << InitConf[j+1] << ")" << endl;
		for(i=0; i<m; i++)
			cout << '\t' << algo[i];
		cout << endl;
		for(n=1024; n<=65536; n*=2)
		{
			GetMemory(data, data0, n);						// 申请分配堆空间
			InitData(data0, n, j);							// 设置原始数据
			cout << n;
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
//					break;
				ReSet(data, data0, n);						// 恢复原始数据
				gettime(1);									// 设置计时起点
				f[i](data, n);								// 第 i 种排序算法
				t[i] = gettime();							// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = Check(data, n);					// 检验排序的正确性
			}
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
//					cout << "\t" << endl;
//				else
					cout <<'\t' << t[i] << '\t';
			}
			for(i=0; i<m; i++)
			{
//				if(n>=65536 && j<=0 && i==m-1)				// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
//					cout << "\t快速排序：由于递归层次太深，可能导致栈溢出，故跳过。";
//				else
					cout << '\t' << algo[i] << (flag[i]?": 正确":": 错误");
			}
			cout << endl;
			FreeMemory(data, data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

int main()						// 主函数
{
	void TestString();			// 函数原型，用于声明
	srand((unsigned int)time(NULL));			// 设置随机数发生器的种子
	int choice;
	char quit_sign = 'Y';
	while (quit_sign != 'n' && quit_sign != 'N')
	{
		cout << "                       Please input the number you want." << std::endl << std::endl << std::endl;
		cout << "                      ******************   排序优化   ******************" << std::endl;
		cout << "                      *               Patch 1.5 2021.7.5               *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *                1.测试int类型数据               *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *               2.测试double类型数据             *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *               3.测试Score类型数据              *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *              4.测试C-字符串数组排序            *" << std::endl;
		cout << "                      *                                                *" << std::endl;
		cout << "                      *                     5. 退出                    *" << std::endl;
		cout << "                      *                Thank you for using             *" << std::endl;
		cout << "                      **************************************************" << std::endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case(1):
			Test(int(0));				// 测试int类型数据
			break;
		case(2):
			Test(double(0));			// 测试double类型数据
			break;
		case(3):
			TestScore();				// 测试Score类型数据
			break;
		case(4):
			TestString();				// 测试C-字符串数组排序（多种存储方式）
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
	cout << "******************   排序优化   ******************" << std::endl;
	cout << "*               Patch 1.5 2021.7.5               *" << std::endl;
	cout << "*                                                *" << std::endl;
	cout << "*                Thank you for using             *" << std::endl;
	cout << "*                                                *" << std::endl;
	cout << "**************************************************" << std::endl;
	return 0;
}
