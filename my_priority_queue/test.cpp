#include "my_prioity_queue.h"
#include <iostream>
using namespace std;
#include<algorithm>
#include<queue>
void test_priority_queue1()
{
	// 
	// Ĭ�ϴ�����ȼ��ߣ��ײ��Ǹ����
	//priority_queue<int> pq;


	// ţ�� ����ţ��
	// С��

	//bit::priority_queue<int, deque<int>> pq;
	//bit::priority_queue<int, vector<int>> pq;
	// ���
	//bit::priority_queue<int> pq;

	// С��
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


	// �º���
	//vector<int> v = { 3,1,7,4,6,3 };
	//// ����
	//sort(v.begin(), v.end());
	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	//// ���� >
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
