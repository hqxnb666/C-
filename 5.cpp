#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//class
//{
//public:
//	int _a;
//	char _i;
//	//内存对齐：会导致空间浪费，为什么要内存对齐
//};



class Date
{
public:
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;//   1.请记住，这里调用打印函数跟private中的 ——year没有任何关系  
	}
private:
	int _year;// 年
	int _month;// 月
	int _day; // 日
};
int main()
{
	Date d1, d2;          //2.这里是定义，开辟空间  ，其实是依靠隐含的this指针，就是C语言简化
	d1.Init(2022, 1, 11);   
	d2.Init(2022, 1, 12);
	d1.Print();
	d2.Print();
	return 0;
}//this 存在栈
//1. this指针的类型：类类型* const，即成员函数中，不能给this指针赋值。
//2. 只能在“成员函数”的内部使用
//3. this指针本质上是“成员函数”的形参，当对象调用成员函数时，将对象地址作为实参传递给this形参。所以对象中不存储this指针。
//4. this指针是“成员函数”第一个隐含的指针形参，一般情况由编译器通过ecx寄存器自动传递，不需要用户传递