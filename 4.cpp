#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//C++ �ṹ�岻�����Զ�������������Զ��庯��
//C++ ����C   ����ͬʱ��������
struct Stack
{
	//��Ա����
	int* s;
	int top;

	//��Ա����
	
};


// ���ڽṹ��Ķ��壬C++��ϲ����class����

class className
{
	//���壺�ɳ�Ա�����ͳ�Ա�������
}; // һ��Ҫע�����ķֺ�

class Date
{
public:
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;

	}

	int _year;  //���Ҳֻ���������Ƕ�����ʲô�� ���ռ�Žж���
	int _month;
	int _day;
};
int main()
{
	//int j = 0;
	//int i = j;
	//auto k = i;
	//�����ʼ��

	//������ӷ����޶�����Ĭ��˽�У��޷�����
	// structĬ�Ϲ��У� classĬ��˽��
	Date t1;
	t1.Init(2004, 1, 2);
	t1._day++;

	//Date:;_year++;   �ᱨ����Ϊֻ��������û�п��ռ�
	//�������  Date d1;    d1._year++    �Ϳ���   ��Ϊ   Date d1 �ͽж��壬Ҳ���� ����ʵ����


	//ͬʱ�����������    
	// //�����к����������붨�����ʱ�� ����Ҫ���� ����  ��ֵ����
	// ��������������������
	// 
	//auto����������




	//��װ �̳� ��̬

	//����������������������
	//��װ�ı�����һ�ֹܿ�
	//C++���ݺͷ������������� C�Ƿ����
	//C++�������Ʒ�ȥ�Գ�Ա����
	



	cout << sizeof(t1) << endl;
	//Ҫ��Ҫ�㺯���أ�����ֻ���Ա������
	//û�г�Ա�����Ĵ�С��1byte

	return 0;
}