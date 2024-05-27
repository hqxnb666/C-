#include "my_stack.h"
#include <iostream>

int main()
{
	bit::stack<int> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	while (!s1.empty())
	{
		int i = 0;
		std::cout << s1 << std::endl;
	}
	return 0;
}
