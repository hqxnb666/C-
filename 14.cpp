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
	//reserve���ֶ�����
//resizeҲ��

	//reserve�õıȽϴ��������Ч��
	//֪��Ҫ����������ݣ���ǰ���ÿռ�
	//�����˶�����ݣ����Ч��

	string s1("abcdef");
	s1.resize(7,'x');   //��sizeС��������   ������֮������   �������+��� 
	cout << s1 << endl;
}


void test_string6()
{
	string s1("hello word");
	cout << s1[5] << endl;
	cout << s1.at(6) << endl;

//	s1[15];
	//s1.at(15);//ʵ��������һ�����ճ��л���ϰ����[]

}

void test_string7()
{
	string s1("ssdsdsds");
	s1.push_back('!');  //Ҫ���ǲ���һ���ַ�
	s1.append("hellow bot");
	cout << s1 << endl;


	//ʵ��������õ��� operate +=

	s1 += "appel";
	cout << s1 << endl;
}


void test_string8()
{
	string s1("dsdsdsd");
	s1.assign("xxxx");  //����  
	cout << s1 << endl;
}

void test_string9()
{
	string s1("ssssssssssss");
	s1.insert(1, "ddd");  //����  posλ��
	cout << s1 << endl;
	s1.clear();
	cout << s1 << endl;
}
int main()
{
	test_string9();
	return 0;
}