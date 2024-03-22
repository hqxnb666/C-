#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


//模板
//函数模板
template<typename T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}
template<class T>
T Add(const T& x, const T& y)
{
	return x + y;
}
int Add(const int& x, const int& y)
{
	return x + y;
}



//类模板

template<class T>
class Stack
{
public:
	void push(const T& x)
	{
		//
	}
private:
	T* _a;
	int _top;
	int _capacity;
};



void test_string1()
{
	string s0;
	string s1("hello world");
	string s2(s1);
	string s3(s1, 5, 3);
	string s4(s1, 5, 10);
	string s5(s1, 5);

	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl;
}
int main()
{
	////内存泄漏  
	////一块已经不再使用的空间，没有释放
	//// 内存泄漏的危害： 
	////int* p = new int[1024 * 1024 * 100];


	//int a1 = 10, a2 = 20;
	//double d1 = 10.1, d2 = 20.2l;

	////1.有现成，用现成的
	//cout << Add(a1, a2) << endl;

	////2.有现成，但是不够匹配，有模板，就会选择自己实例化

	//cout << Add(d1, d2) << endl;

	////3.显示实例化  也就是强制调用模板
	//cout << Add<int>(a1, a2) << endl;


	Stack<int> s1;
	Stack<double>s2;//这两个是同一个类模板实例化出的两个类型

	test_string1();
	return 0;
}