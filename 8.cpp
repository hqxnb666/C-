//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//using namespace std;
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	//  d1 < d2   ==     d1.operator<(d2)
//	bool operator<(const Date& d)
//	{
//		if (_year < d._year) {
//			return true;
//		}
//		else if (_year == d._year) {
//			if (_month < d._month) {
//				return true;
//			}
//			else if (_month == d._month) {
//				if (_day < d._day) {
//					return true;
//				}
//			}
//		}
//	}
//	private:
//	int _year;
//	int _month;
//	int _day;
//};


//int main()
//{
//	Date d1(2024, 1, 1);
//	Date d2(2024, 5, 1);
//	d1 < d2;
//	return 0;
//}

#include "Date.h"

int main()
{
	Date d1(2024, 2, 3);
	Date d2  ;
	int d3 = d1 - d2;
	cout << d3 << endl;
	d1.Print();
	return 0;
}