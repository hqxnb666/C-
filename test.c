#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//int main()
//{
//	int num =  0;
//	printf("%d", num);
//	return 0;
//}

//int main()
//{
//	//����һ���������ж��Ƿ�Ϊ����
//	int num = 0;
//	scanf("%d", &num);
//	if (num % 2 == 1)
//		printf("%d ������\n", num);
//	else
//		printf("%d ��ż��\n", num);
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age >= 18)
//	{
//		printf("������\n");
//		printf("����̸������\n");
//	}
//		
//	else
//	{
//		printf("δ����\n");
//		printf("��ò�Ҫ̸����\n");
//	}
//		
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num == 0)
//		printf("�����������0\n");
//	else
//	{
//		if (num > 0)
//			printf("�������������\n");
//		else
//			printf("����ĵ����Ǹ���\n");
//	}
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num == 0)
//		printf("�����������0\n");
//	else if (num > 0)
//		printf("���������������\n");
//	else
//		printf("����������Ǹ���\n");
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num > 0)
//	{
//		if (num % 2 == 0)
//			printf("ż��\n");
//		else
//			printf("����\n");
//	}
//	else
//	{
//		printf("��������\n");
//	}
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age < 18)
//		printf("����\n");
//	else
//	{
//		if (age <= 44)
//		{
//			printf("����\n");
//		}
//		else
//		{
//			if (age <= 59)
//				printf("������\n");
//			else
//			{
//				if (age < 89)
//					printf("����\n");
//				else
//					printf("������\n");
//			}
//		}
//	}
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age < 18)
//		printf("����\n");
//	else if (age <= 44)
//		printf("����\n");
//	else if (age < 59)
//		printf("������\n");
//	else if (age <= 89)
//		printf("����\n");
//	else
//		printf("������\n");
//	return 0;
//}

//int main()
//{
//	int a = 0;
//	int b = 2;
//	if (a == 1)
//		if (b == 2)
//			printf("hehe\n");
//		else
//			printf("haha\n");
//	return 0;
//}

//int main()
//{
//	int r = 3 > 5;
//	printf("%d", r);
//	return 0;
//}

//int main()
//{
//	int a = 4;
//	if (3 == a)
//		printf("hehe\n");
//	return 0;
//}


//int main()
//{
//	int i = 8;
//	int j = 10;
//	int k = 9;
//	if (i < j  && j < k)
//		printf("hehe\n");
//	else
//		printf("haha\n");
//
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age >= 18 && age <= 36)
//		printf("����\n");
//	else
//		printf("������\n");
//	return 0;
//}

//int main()
//{
//	int flag = 0;
//	if (!flag)
//		printf("hehe\n");
//
//	return 0;
//}

//int main()
//{
//	int month = 0;
//	scanf("%d", &month);
//	//3~5�Ǵ���
//	if (month >= 3 && month <= 5)
//	{
//		printf("����\n");
//
//	}
//	return 0;
//}

//int main()
//{
//	int month = 0;
//	scanf("%d", &month);
//	//12  1  2�Ƕ���
//	if (month == 12 || 1 == month || 2 == month)
//	{
//		printf("����\n");
//	}
//	return 0;
//}

//int main()
//{
//	int year = 0;
//	scanf("%d", &year);
//	if (year % 4 == 0 && year % 100 != 0)
//	{
//		printf("yes\n");
//	}
//	else
//	{
//		if (year % 400 == 0)
//			printf("yes\n");
//	}
//	return 0;
//}

//int main()
//{
//	int year = 0;
//	scanf("%d", &year);
//	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
//	{
//		printf("yes\n");
//	}
//	return 0;
//}

int main()
{
	int num = 0;
	scanf("%d", &num);
	switch(num % 3)
	{
		case 0:
			printf("������0\n");
			break;
		case 1:
			printf("������1\n");
			break;
		case 2:
			printf("������2\n");
			break;
		default:
			printf("����\n");
	}
	return 0;
}