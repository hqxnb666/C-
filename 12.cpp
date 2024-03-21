//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//
//using namespace std;
//void Test()
//{
//	static int staticVar = 1;
//	int localVar = 1;
//	int num1[10] = { 1, 2, 3, 4 };
//	char char2[] = "abcd";
//	const char* pChar3 = "abcd";
//	int* ptr1 = (int*)malloc(sizeof(int) * 4);
//	int* ptr2 = (int*)calloc(4, sizeof(int));
//	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
//	free(ptr1);
//	free(ptr3);
//}
////int main()
////{
////	int globalVar = 1;
////	static int staticGlobalVar = 1;
////	
////	/*1. 选择题：
////		选项 : A.栈  B.堆  C.数据段(静态区)  D.代码段(常量区)
////		globalVar在哪里？__C__   staticGlobalVar在哪里？__C__
////		staticVar在哪里？__C__   localVar在哪里？__A__
////		num1 在哪里？__A__
////
////		char2在哪里？__A__ * char2在哪里？_A__
////		pChar3在哪里？__A__ * pChar3在哪里？__D__
////		ptr1在哪里？__A__ * ptr1在哪里？__B	__
////		2. 填空题：
////		sizeof(num1) = _40___;*/
////
////	
////	//重点应该关注堆这个区域
////	//malloc calloc realloc的区别是什么
////	//calloc 在malloc的基础上会初始化成0
////	//realloc是扩容   一种原地扩容  和异地扩容
////
////
////
////	//C++内存管理方式
////
////	//C语言中有些地方略显无力，所以C++提出了自己的内存管理方式
////	//new    delete 
////
////	
////}
//
////void Test1()
////{
////	// 动态申请一个int类型的空间
////	int* ptr4 = new int;
////	
////	// 动态申请一个int类型的空间并初始化为10
////	int* ptr5 = new int(10);
////
////	// 动态申请10个int类型的空间
////	int* ptr6 = new int[3] {1,2,3};
////	delete ptr4;
////	delete ptr5;
////	delete[] ptr6;
////}
//
//
//
////C语言搞结构体
//struct  ListNode
//{
//	ListNode* next;
//	ListNode* prev;
//	int _val;
//
//	ListNode(int val = 1)
//		:next(nullptr)
//		, prev(nullptr)
//		, _val(val)
//	{}
//};
//struct  ListNode* CreateNode(int val)
//{
//	struct  ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
//	if (newnode == NULL)
//	{
//		perror("malloc fail");
//	}
//	newnode->next = NULL;
//	newnode->prev = NULL;
//	newnode->_val = val;
//	return newnode;
//}
//
////C++实现创建链表   还涉及到哑节点 也就是局部哨兵位
//ListNode* CreateList(int n = 1)
//{
//	int val;
//	ListNode dummy(-1);
//	ListNode* tail = &dummy;
//	printf("请依此输入%d个节点的值:> ", n);
//	for (int i = 0; i < n; i++) {
//		cin >> val;
//		tail->next = new ListNode(val);//失败不用检查  -- 抛异常
//		tail = tail->next;
//	}
//	return dummy.next;
//}
//int main()
//{
//	ListNode* node1 = new ListNode(1);
//	//现在只需要这样就可以开辟空间，而不需要在搞一个开辟函数
//	//new 失败了以后抛异常  不需要手动检查
//	//Test1();
//	return 0;
//}
#include <iostream>

int n; // 目标数
class Solution {
public:
    static int sum;
    static int counter;
    Solution() {
        ++counter;
        sum += counter;
    }
};

int Solution::sum = 0;
int Solution::counter = 0;

int main() {
    std::cin >> n;
    Solution* solutions = new Solution[n]; // 动态分配内存来创建对象数组
    std::cout << Solution::sum << std::endl;
    delete[] solutions; // 清理动态分配的内存
    return 0;
}
