#include<iostream>
using namespace std;

//函数参数（T 对象1， T 对象二）
//模板参数 <class 类型1， class 类型二>


//首先是关于我们自己定义一个静态vector的时候，要控制容量，这个时候可以使用非类型模板参数

//namespace bit
//{
//	template <class T, size_t N>
//	class vector
//	{
//	private:
//		T _array[N];
//	};
//}
//int min()
//{
//	bit::vector<int, 10> a1;
//	bit::vector<int, 10000> a2;
//	return 0;
//}


//区别就是，函数传参是运行时传参，模板是编译时传参，他是个半成品，模板的缺省值很多规则基本跟函数相似

int main()
{
	//那么我们封装的和静态的又有什么区别呢
	//array<int,10> a1;
	//int a2[10];  区别就在越界的检查，传统的数组对于越界检查是抽查，越界读，检查不出来
	//越界写，抽查
	//具有局限性，很多位置查不出来
	//所以我们的数组优势是加强对于边界的检查

	return 0;
}


