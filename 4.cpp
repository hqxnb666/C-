#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//C++ 结构体不仅可以定义变量，还可以定义函数
//C++ 兼容C   但是同时升级成累
struct Stack
{
	//成员变量
	int* s;
	int top;

	//成员函数
	
};


// 对于结构体的定义，C++更喜欢用class代替

class className
{
	//类体：由成员函数和成员变量组成
}; // 一定要注意后面的分号

class Date
{
public:
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;

	}

	int _year;  //这个也只是声明，那定义是什么， 开空间才叫定义
	int _month;
	int _day;
};
int main()
{
	//int j = 0;
	//int i = j;
	//auto k = i;
	//必须初始化

	//如果不加访问限定符，默认私有，无法访问
	// struct默认公有， class默认私有
	Date t1;
	t1.Init(2004, 1, 2);
	t1._day++;

	//Date:;_year++;   会报错，因为只是声明，没有开空间
	//但是如果  Date d1;    d1._year++    就可以   因为   Date d1 就叫定义，也就是 对象实例化


	//同时类就是作用域    
	// //当进行函数的声明与定义分离时， 我们要进行 ：：  域值搜索
	// 这样才能做到函数分离
	// 
	//auto不能做参数




	//封装 继承 多态

	//以上是面向对象的三大特性
	//封装的本质是一种管控
	//C++数据和方法都放在类里 C是分离的
	//C++访问限制符去对成员限制
	



	cout << sizeof(t1) << endl;
	//要不要算函数呢，还是只算成员变量呢
	//没有成员变量的大小是1byte

	return 0;
}