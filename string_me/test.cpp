#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"
int main()
{
	my_string::string tmp = my_string::string::string("hello word");
	my_string::string tmp1 = my_string::string::string("xxxxxxx");
	tmp = tmp1;
	for (auto ch : tmp1)
	{
		std::cout << tmp.c_str();
	}
	std::cout <<  std::endl;
	return 0;
}