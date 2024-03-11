#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class A
{
public:
	A(int a = 1 , int b = 1)
		:_a(a)
		,_b(b)
	{}
private:
	int _a;
	int _b;
};
class Date
{
public:
	//初始化列表
	//能用初始化列表就建议用初始化列表
	Date(int year, int month, int day, int& x)
		:_year(year)
		,_month(month)
		,_day(day)
		,_ref(x)
		,_n(1)
		,d2(1,1)
	{}
private:
	//声明
	int _year = 1; //这里缺省值服务的就是初始化列表
	int _month;
	int _day;
	A d2;

	//必须走初始化列表
	const int _n;
	int& _ref; //引用必须在定义初始hua
};
int main()
{
	int x = 10;
	//对象实例化
	Date d1(2024,1,1,x);
	
	return 0;
}
class C
{
public:
	C(int x = 10)
		:_x(x)
	{}
	C(const C& cc)
	{
		cout << "C(const C& cc)" << endl;
	}
private:
	int _x;
};

class B
{
private:
	int a = 1;
	int* p1 = nullptr;
};
int main()
{
	//实际上我们在传参过程中， 单参数构造函数支持隐式类型的转换
	//2先构造一个临时对象，再拷贝构造  编译器实际上会优化，
	C cc = 2;
	const C& cc3 = 2;
	//这也就意味着我们在传参时可以直接传参数
	C cc1(1);//如果不喜欢就可以加入explicit 关键词
}
	

class A
{
public:
	//explicit A(int a1, int a2)
		A(int a1, int a2)
		:_a1(a1)
		,_a2(a2)
	{}
private:
	int _a1;
	int _a2;
};

class B
{
private:
	//缺省值
	int _a = 1;
	int* p = (int*)malloc(4);
	A aa1 = { 1,2 };
};
int main()
{
	A aa1 = { 1, 2 };  //多参数隐式传参也可以这样
}

class A
{
public:
	A(int a)
		:_a1(a)
		, _a2(_a1)
	{}

	void Print() {
		cout << _a1 << " " << _a2 << endl;
	}
private:
	//声明顺序来初始化
	int _a2;
	int _a1;
};
int main() {
	A aa(1);
	aa.Print();
}  //结果是1  随机值
