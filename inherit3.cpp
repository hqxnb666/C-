#include<iostream>
using namespace std;
class Student;
class Person
{
public:
	friend void display(const Person& p, Student& s);
protected:
	string _name;
};
class Student : public Person
{
	friend void display(const Person& p, Student& s);
protected:
	int _numl;
};

void display(const Person& p, Student& s)
{
	cout << p._name << s._numl << endl;
}
int main()
{
	Person p1;
	Student s1;
	display(p1, s1);
	return 0;
}