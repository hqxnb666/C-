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
	//��ʼ���б�
	//���ó�ʼ���б�ͽ����ó�ʼ���б�
	Date(int year, int month, int day, int& x)
		:_year(year)
		,_month(month)
		,_day(day)
		,_ref(x)
		,_n(1)
		,d2(1,1)
	{}
private:
	//����
	int _year = 1; //����ȱʡֵ����ľ��ǳ�ʼ���б�
	int _month;
	int _day;
	A d2;

	//�����߳�ʼ���б�
	const int _n;
	int& _ref; //���ñ����ڶ����ʼhua
};
int main()
{
	int x = 10;
	//����ʵ����
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
	//ʵ���������ڴ��ι����У� ���������캯��֧����ʽ���͵�ת��
	//2�ȹ���һ����ʱ�����ٿ�������  ������ʵ���ϻ��Ż���
	C cc = 2;
	const C& cc3 = 2;
	//��Ҳ����ζ�������ڴ���ʱ����ֱ�Ӵ�����
	C cc1(1);//�����ϲ���Ϳ��Լ���explicit �ؼ���
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
	//ȱʡֵ
	int _a = 1;
	int* p = (int*)malloc(4);
	A aa1 = { 1,2 };
};
int main()
{
	A aa1 = { 1, 2 };  //�������ʽ����Ҳ��������
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
	//����˳������ʼ��
	int _a2;
	int _a1;
};
int main() {
	A aa(1);
	aa.Print();
}  //�����1  ���ֵ
