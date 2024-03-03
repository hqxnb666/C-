#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

int main()
{
	const Date d1(2024, 1, 1);
	
	d1.Print();//这里为什么不能调用呢，因为d1的类型是cosnt 而这里的隐含this 是Date  
	//权限只能缩小，不能放大
	


//  我们可以在 print定义中 在后面加入const   void Print() cosnt    
	//这样就可以了




	//权限的平移
	Date d2(2024, 5, 5);
	d2.Print();
	//const可以调用，非const也可以


	//如果是一个对成员函数只进行读访问的函数，建议加const  
	//如果要对成员变量进行读写访问，不能加cosnt 否则不能加const修改成员变量




	const int i = 0;
	int j = i;
	//这里是拷贝，不存在权限放大缩小

	//权限放大
	//只有指针和引用的赋值才存在权限放大




	//取地址重载 日常用编译器默认生成的就够用
	//比如我不想普通对象拿到地址，只允许const的对象取地址才需要我们自己生成，或者返回假地址

	return 0;
}