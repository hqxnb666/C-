#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//class Date
//{
//public:
//	
//	// ����û���ʽ�����˹��캯��������������������
//	Date(int year =1, int month =1, int day =1)
//	{
//	_year = year;
//	_month = month;
//	_day = day;
//	}
//	
//
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//
//	Date(Date& d)  //��������
//	{
//		_year = d._year;
//		_day = d._day;
//		_month = d._month;
//	}
//private:
//	int _year = 1;
//	int _month = 1; // ȱʡֵ��Ĭ�Ϲ��캯�������ȱʡֵ
//	int _day = 1;
//};
//
////һ���Զ������͵ľ�ͷ���������ͣ����ջ���Ҫ���Լ���ʼ��
//
//
//
////��������˳��
////  �ֲ����� ->   �ֲ��ľ�̬   ->  ȫ�ֶ��󣨺����������� -> ȫ�־�̬
//
//
////��������
//
//int main()
//{
//	Date d1(2024,2,25);
//	Date d2(d1);//��������Ҳ��һ�����캯��  
//	
//
//
//	//Ϊʲô��������
//	//C++�������е��Զ������ʹ�ֵ���ζ�����ÿ�������
//	//�������ô��ξͲ���Ҫ�ٸ�һ��������
//	return 0;
//}


//typedef int DataType;
//class Stack
//{
//public:
//	Stack(size_t capacity = 10)
//	{
//		_array = (DataType*)malloc(capacity * sizeof(DataType));
//		if (nullptr == _array)
//		{
//			perror("malloc����ռ�ʧ��");
//			return;
//		}
//		_size = 0;
//		_capacity = capacity;
//	}
//	void Push(const DataType& data)
//	{
//		// CheckCapacity();
//		_array[_size] = data;
//		_size++;
//	}
//	~Stack()
//	{
//		if (_array)
//		{
//			free(_array);
//			_array = nullptr;
//			_capacity = 0;
//			_size = 0;
//		}
//	}private:
//		DataType* _array;
//		size_t _size;
//		size_t _capacity;
//};
//int main()
//{
//	Stack s1;
//	s1.Push(1);
//	s1.Push(2);
//	s1.Push(3);
//	s1.Push(4);
//	Stack s2(s1);
//	return 0;
//}
//�ڱ��������ɵ�Ĭ�Ͽ������캯���У����������ǰ����ֽڷ�ʽֱ�ӿ����ģ����Զ�
//�������ǵ����俽�����캯����ɿ����ġ�

//������ǳ���������漰��malloc���ٵ�ָ��ʱ��ǳ�����Ὣͬһ��ָ��ĵ�ַ�����������������ζ�Ŷ������ָ��ͬһ��ռ�
//����������������ʱ���ᵼ��һ��ռ��ͷ�����
//������ʱ��Ҫ�����
//���ǿ���һ��ռ䣬�����ݿ���������µĿռ���ٷ���
//�����������ԵĿռ䣬�Ͳ������


//�����Ժ󴫲ξ��������ô���
