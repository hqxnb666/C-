#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdbool.h>
//int main()
//{
//	int day = 0;
//	scanf("%d", &day);
//	switch (day)
//	{
//	
//	
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//		printf("工作日\n");
//		break;
//	case 6:
//	case 7:
//		printf("休息日\n");
//		break;
//	default:
//		printf("输入错误\n");
//		break;
//	}
//	 
//	return 0;
//}


//int main()
//{
//	while (1)
//		printf("hehe\n"); //while后边的条件满⾜，死循环的打印hehe
//	return 0;
//}


//int main()
//{
//	int i = 1;
//	while (i <= 10)
//	{
//		printf("%d\n", i);
//		i++;
//	}
//	return 0;
//}



//int main()
//{
//	
//	int n = 0;
//	scanf("%d", &n);
//	while (n)
//	{
//		printf("%d\n", n % 10);
//		 n /= 10;
//	}
//	return 0;
//}

//int main()
//{
//	int i = 0;
//	for (i = 1; i<= 10; i++)
//	{
//		printf("%d\n", i);
//	}
//
//     
//	return 0;
//}

//int main()
//{
//	//遍历
//	int i = 0;
//	int sum = 0;
//	for (i = 3; i < 100; i += 3)
//	{
//		sum += i;
//	}
//	printf("sum = %d\n", sum);
//	return 0;
//}

//int main()
//{
//	int i = 1;
//	do {
//		printf("%d\n", i);
//		i++;
//	} while (i <= 10);
//	return 0;
//}

//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	int cnt = 0;
//	do
//	{
//		n /= 10;
//		cnt++;
//	} while (n);
//	printf("%d", cnt);
//	return 0;
//}


//int main()
//{
//	
//	int n = 0;
//	scanf("%d", &n);
//	while (n)
//	{
//		if (n == 12)
//			continue;
//		printf("%d\n", n % 10);
//		 n /= 10;
//	}
//	return 0;
//}


//int main()
//{
//	int i = 0;
//	for (i = 100; i <= 200; i++)
//	{
//		//判断i是否是素数
//		//使用  2~ i-1的数字来试除i
//		int j = 0;
//		int flag = 1; //假设i是素数
//		for (j = 2; j <= i - 1; j++)
//		{
//			if (i % j == 0)
//			{
//				flag = 0;
//				break;
//			}
//		}
//		if (flag == 1)
//		{
//			printf("%d ", i);
//		}
//	}
//	return 0;
//}

//bool isPrime(int num) {
//	if (num <= 1) 
//		return false;
//	for (int i = 2; i * i <= num; i++) {
//		if (num % i == 0)
//			return false;
//	}
//	return true;
//}
//
//int main()
//{
//	int i = 0;
//	for (i = 100; i <= 200; i++) {
//		if (isPrime(i)) {
//			printf("%d ", i);
//		}
//	}
//	printf("\n");
//	return 0;
//}

//int main()
//{
//	/*printf("hehe\n");
//	goto end;
//	printf("haha\n");
//end:
//	printf("跳过haha的打印，直接来到这里");*/
//
//
//again:
//	printf("haha\n");
//	goto again;
//	return 0;
//}