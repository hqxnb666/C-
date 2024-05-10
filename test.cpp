#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"
#include <iostream>
using namespace std;
void test1()
{
	bit::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(4);
	v1.push_back(4);
	print_vector(v1);
	
}
int main()
{
	test1();
	return 0;
}