#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


class A
{
public:
	A(int a = 0) {
		_a1 = a;
	}
	/*class B
	{
	public:
		B()
		{
			_a1 = _a2;
		}
	private:
		int _b1;
	};*/
private:
	 int _a1;
	 int _a2;
};
class SLoutiojn
{
public: int func() {
	return 0;
}
};
//int A::_a1 = 0; //ֻ�����ⲿ���ж���
int main()
{
	
	cout << sizeof(A) << endl;  //8  

	//�ܵ���װ��Ӱ��
	//A::B b;

	//�ڲ����������ⲿ�����Ԫ��
	
	//�������ò���  �ܿ�������



	//��������
	A();
	SLoutiojn().func();  //��������ֱ�ӵ���
	//��������-
	A aa1;


	A aa3 = 5; // �ȹ���󿽱�ֱ���Ż�
	const A& aa5 = 4; //�޷��Ż� ��Ϊֻ��һ������


	//�Ż�Ҳ��ζ�ż����� ���ܻᵼ��bug�� ��Ϊ��ʱ������Ҫ������󣬵���û�ܹ������
	//release �Ż����
	return 0;
}