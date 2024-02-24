#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//class Date
//{
//public:
//	
//	// 如果用户显式定义了构造函数，编译器将不再生成
//	Date(int year =1, int month =1, int day =1)
//	{
//	_year = year;
//	_month = month;
//	_day = day;
//	}
//	
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//
//	Date(Date& d)  //必须引用
//	{
//		_year = d._year;
//		_day = d._day;
//		_month = d._month;
//	}
//private:
//	int _year = 1;
//	int _month = 1; // 缺省值，默认构造函数会调用缺省值
//	int _day = 1;
//};
//
////一切自定义类型的尽头是内置类型，最终还是要靠自己初始化
//
//
//
////析构函数顺序
////  局部对象 ->   局部的静态   ->  全局对象（后定义先析构） -> 全局静态
//
//
////拷贝构造
//
//int main()
//{
//	Date d1(2024,2,25);
//	Date d2(d1);//拷贝构造也是一个构造函数  
//	
//
//
//	//为什么传引用呢
//	//C++定义所有的自定义类型传值传参都会调用拷贝构造
//	//而传引用传参就不需要再搞一个函数，
//	return 0;
//}


//typedef int DataType;
//class Stack
//{
//public:
//	Stack(size_t capacity = 10)
//	{
//		_array = (DataType*)malloc(capacity * sizeof(DataType));
//		if (nullptr == _array)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_size = 0;
//		_capacity = capacity;
//	}
//	void Push(const DataType& data)
//	{
//		// CheckCapacity();
//		_array[_size] = data;
//		_size++;
//	}
//	~Stack()
//	{
//		if (_array)
//		{
//			free(_array);
//			_array = nullptr;
//			_capacity = 0;
//			_size = 0;
//		}
//	}private:
//		DataType* _array;
//		size_t _size;
//		size_t _capacity;
//};
//int main()
//{
//	Stack s1;
//	s1.Push(1);
//	s1.Push(2);
//	s1.Push(3);
//	s1.Push(4);
//	Stack s2(s1);
//	return 0;
//}
//在编译器生成的默认拷贝构造函数中，内置类型是按照字节方式直接拷贝的，而自定
//义类型是调用其拷贝构造函数完成拷贝的。

//这属于浅拷贝，当涉及到malloc开辟的指针时，浅拷贝会将同一个指针的地址拷贝给多个对象，这意味着多个对象指向同一块空间
//而当调用析构函数时，会导致一块空间释放两次
//所以这时候要用深拷贝
//就是开辟一块空间，将内容拷贝到这个新的空间后再返回
//这样析构各自的空间，就不会出错


//所以以后传参尽量用引用传参
