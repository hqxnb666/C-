#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//class
//{
//public:
//	int _a;
//	char _i;
//	//�ڴ���룺�ᵼ�¿ռ��˷ѣ�ΪʲôҪ�ڴ����
//};



class Date
{
public:
	void Init(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;//   1.���ס��������ô�ӡ������private�е� ����yearû���κι�ϵ  
	}
private:
	int _year;// ��
	int _month;// ��
	int _day; // ��
};
int main()
{
	Date d1, d2;          //2.�����Ƕ��壬���ٿռ�  ����ʵ������������thisָ�룬����C���Լ�
	d1.Init(2022, 1, 11);   
	d2.Init(2022, 1, 12);
	d1.Print();
	d2.Print();
	return 0;
}//this ����ջ
//1. thisָ������ͣ�������* const������Ա�����У����ܸ�thisָ�븳ֵ��
//2. ֻ���ڡ���Ա���������ڲ�ʹ��
//3. thisָ�뱾�����ǡ���Ա���������βΣ���������ó�Ա����ʱ���������ַ��Ϊʵ�δ��ݸ�this�βΡ����Զ����в��洢thisָ�롣
//4. thisָ���ǡ���Ա��������һ��������ָ���βΣ�һ������ɱ�����ͨ��ecx�Ĵ����Զ����ݣ�����Ҫ�û�����