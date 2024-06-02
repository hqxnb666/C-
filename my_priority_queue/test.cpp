#include "my_prioity_queue.h"
#include <iostream>
using namespace std;
#include<algorithm>
#include<queue>
void test_priority_queue1()
{
	// 
	// 默认大的优先级高，底层是个大堆
	//priority_queue<int> pq;


	// 牛肉 人造牛肉
	// 小堆

	//bit::priority_queue<int, deque<int>> pq;
	//bit::priority_queue<int, vector<int>> pq;
	// 大堆
	//bit::priority_queue<int> pq;

	// 小堆
	bit::priority_queue<int, vector<int>> pq;
	pq.push(2);
	pq.push(1);
	pq.push(4);
	pq.push(3);
	pq.push(7);
	pq.push(8);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;


	// 仿函数
	//vector<int> v = { 3,1,7,4,6,3 };
	//// 升序
	//sort(v.begin(), v.end());
	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	//// 降序 >
	////greater<int> gt;
	////sort(v.begin(), v.end(), gt);
	//sort(v.begin(), v.end(), greater<int>());
	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
}
int main()
{
	test_priority_queue1();
	return 0;
}
