#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


//ģ��
//����ģ��
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



//��ģ��

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
	////�ڴ�й©  
	////һ���Ѿ�����ʹ�õĿռ䣬û���ͷ�
	//// �ڴ�й©��Σ���� 
	////int* p = new int[1024 * 1024 * 100];


	//int a1 = 10, a2 = 20;
	//double d1 = 10.1, d2 = 20.2l;

	////1.���ֳɣ����ֳɵ�
	//cout << Add(a1, a2) << endl;

	////2.���ֳɣ����ǲ���ƥ�䣬��ģ�壬�ͻ�ѡ���Լ�ʵ����

	//cout << Add(d1, d2) << endl;

	////3.��ʾʵ����  Ҳ����ǿ�Ƶ���ģ��
	//cout << Add<int>(a1, a2) << endl;


	Stack<int> s1;
	Stack<double>s2;//��������ͬһ����ģ��ʵ����������������

	test_string1();
	return 0;
}