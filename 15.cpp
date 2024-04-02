#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
	//string  是  basic string 也是个模板
	//wstring   wchar_t   配合宽字符相关的 比如 wprintf  


	char ch1;
	wchar_t ch2;
	char16_t ch3;
	char32_t ch4;

	cout << sizeof(ch1) << endl;
	cout << sizeof(ch2) << endl;
	cout << sizeof(ch3) << endl;
	cout << sizeof(ch4) << endl;

	//编码  文字计算机的存储表示
	// 早期最简单的ASCII编码  就是美国标准的基于拉丁字母的电脑编码
	// 但是ASCII随着时间的发展，我们要表述各个国家的文字 例如我们是象形文字
	// 这时候推出了 unicode  万国码，用来表示全世界的文字，包括字符集、编码、方案等
	//  两个字节足以容纳大多数文字
	// 
	// 其他的有人就发明了 Utf-8  utf-16 
	// utf8能很好的兼容这些东西
	// 
	// 还有gbk  
	// 这个是国标 国际上编码是针对所有的国家
	// 我们自己也要搞我们自己的编码
	// 这就是为什么字符数组要写成模板
	// 所以utf8 对应的就是string  用的是basic 
	// 比如有些地方涉及到utf16  就用 对应的string模板
	//
	return 0;
}