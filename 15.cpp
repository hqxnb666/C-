#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
	//string  ��  basic string Ҳ�Ǹ�ģ��
	//wstring   wchar_t   ��Ͽ��ַ���ص� ���� wprintf  


	char ch1;
	wchar_t ch2;
	char16_t ch3;
	char32_t ch4;

	cout << sizeof(ch1) << endl;
	cout << sizeof(ch2) << endl;
	cout << sizeof(ch3) << endl;
	cout << sizeof(ch4) << endl;

	//����  ���ּ�����Ĵ洢��ʾ
	// ������򵥵�ASCII����  ����������׼�Ļ���������ĸ�ĵ��Ա���
	// ����ASCII����ʱ��ķ�չ������Ҫ�����������ҵ����� ������������������
	// ��ʱ���Ƴ��� unicode  ����룬������ʾȫ��������֣������ַ��������롢������
	//  �����ֽ��������ɴ��������
	// 
	// ���������˾ͷ����� Utf-8  utf-16 
	// utf8�ܺܺõļ�����Щ����
	// 
	// ����gbk  
	// ����ǹ��� �����ϱ�����������еĹ���
	// �����Լ�ҲҪ�������Լ��ı���
	// �����Ϊʲô�ַ�����Ҫд��ģ��
	// ����utf8 ��Ӧ�ľ���string  �õ���basic 
	// ������Щ�ط��漰��utf16  ���� ��Ӧ��stringģ��
	//
	return 0;
}