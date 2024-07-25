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
//	//输入一个整数，判断是否为奇数
//	int num = 0;
//	scanf("%d", &num);
//	if (num % 2 == 1)
//		printf("%d 是奇数\n", num);
//	else
//		printf("%d 是偶数\n", num);
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age >= 18)
//	{
//		printf("成年了\n");
//		printf("可以谈恋爱了\n");
//	}
//		
//	else
//	{
//		printf("未成年\n");
//		printf("最好不要谈恋爱\n");
//	}
//		
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num == 0)
//		printf("输入的数字是0\n");
//	else
//	{
//		if (num > 0)
//			printf("输入的数是正数\n");
//		else
//			printf("输入的的数是负数\n");
//	}
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num == 0)
//		printf("输入的数字是0\n");
//	else if (num > 0)
//		printf("输入的数字是正数\n");
//	else
//		printf("输入的数字是负数\n");
//	return 0;
//}

//int main()
//{
//	int num = 0;
//	scanf("%d", &num);
//	if (num > 0)
//	{
//		if (num % 2 == 0)
//			printf("偶数\n");
//		else
//			printf("奇数\n");
//	}
//	else
//	{
//		printf("不是正数\n");
//	}
//	return 0;
//}

//int main()
//{
//	int age = 0;
//	scanf("%d", &age);
//	if (age < 18)
//		printf("少年\n");
//	else
//	{
//		if (age <= 44)
//		{
//			printf("青年\n");
//		}
//		else
//		{
//			if (age <= 59)
//				printf("中老年\n");
//			else
//			{
//				if (age < 89)
//					printf("老年\n");
//				else
//					printf("老寿星\n");
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
//		printf("少年\n");
//	else if (age <= 44)
//		printf("青年\n");
//	else if (age < 59)
//		printf("中老年\n");
//	else if (age <= 89)
//		printf("老年\n");
//	else
//		printf("老寿星\n");
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
//		printf("青年\n");
//	else
//		printf("非青年\n");
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
//	//3~5是春季
//	if (month >= 3 && month <= 5)
//	{
//		printf("春季\n");
//
//	}
//	return 0;
//}

//int main()
//{
//	int month = 0;
//	scanf("%d", &month);
//	//12  1  2是冬季
//	if (month == 12 || 1 == month || 2 == month)
//	{
//		printf("冬季\n");
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
			printf("余数是0\n");
			break;
		case 1:
			printf("余数是1\n");
			break;
		case 2:
			printf("余数是2\n");
			break;
		default:
			printf("错误\n");
	}
	return 0;
}