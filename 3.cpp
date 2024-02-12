#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
void Swap(int& a, int& b)
{
	//
}
using namespace std;
int main()
{
	// 引用
	//int a = 0;
	//int& b = a;

	// b就是a的别名

	//别名可以无限制起名， 也可以给别名起别名



	//引用做参数
	
	//Swap(a, b);

	//引用必须初始化
	//引用不能改变指向
	//一个变量可以有多个引用
	/*int a = 0;
	int& b = a;
	int c = 2;
	b = c; */  
	//以上代码意思是只是改变值，不改变地址
	


	//指针和引用功能是类似的  C++引用，对指针复杂的场景可以替换，但不能代替指针

	//引用1、做参数（a、输出型参数 b、对象比较大，减少拷贝，提高效率）


	//引用的第二个作用是做返回值


	return 0;
}