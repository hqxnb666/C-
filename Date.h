#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

class Date
{
public:
	bool CheckInvalid();
	Date(int year = 1, int month = 1, int day = 1);

	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	
	int GetMonthDay(const int& year,const int& month)
	{
		assert(month > 0 && month < 13);
		int monthDays[13] = { 0,31, 28, 31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 &&(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			return 29;
		}
		return monthDays[month];
	}

	Date& operator+=( int day);   //这里可以传引用返回是因为没产生临时变量，d1出了作用域没被销毁
	Date operator+(int day);
	Date operator-(int day);//日期-天数
	int operator-(const Date& d); //日期-日期  //函数重载
	Date& operator-=(int day);
	Date& operator=(const Date& d);

	Date& operator++(); 
	Date& operator--();
	//特殊处理: 解决语法逻辑不自洽，自相矛盾的问题
	//为了跟前置++区分，强行增加int形参，构成重载区分
	Date operator++(int);
	Date operator--(int);

	void Print() const
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in,  Date& d);
