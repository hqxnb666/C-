#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


void test_string3()
{
	string s1("hellow world");
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit;
		//rit++;
	}
	cout << endl;
}


void test_string4()
{
	string s1("abcdef");
	cout << s1.size() << endl;
	
	cout << s1.capacity() << endl;
	
}


void test_string5()
{
	//reserve是手动扩容
//resize也是

	//reserve用的比较大，用来提高效率
	//知道要插入多少数据，提前开好空间
	//避免了多次扩容，提高效率

	string s1("abcdef");
	s1.resize(7,'x');   //比size小，就缩减   在两者之间就填充   大就扩容+填充 
	cout << s1 << endl;
}


void test_string6()
{
	string s1("hello word");
	cout << s1[5] << endl;
	cout << s1.at(6) << endl;

//	s1[15];
	//s1.at(15);//实际上他俩一样，日常中还是习惯用[]

}

void test_string7()
{
	string s1("ssdsdsds");
	s1.push_back('!');  //要求是插入一个字符
	s1.append("hellow bot");
	cout << s1 << endl;


	//实际上最好用的是 operate +=

	s1 += "appel";
	cout << s1 << endl;
}


void test_string8()
{
	string s1("dsdsdsd");
	s1.assign("xxxx");  //覆盖  
	cout << s1 << endl;
}

void test_string9()
{
	string s1("ssssssssssss");
	s1.insert(1, "ddd");  //插入  pos位置
	cout << s1 << endl;
	s1.clear();
	cout << s1 << endl;
}
int main()
{
	test_string9();
	return 0;
}