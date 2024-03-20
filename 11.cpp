#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


class A
{
public:
	A(int a = 0) {
		_a1 = a;
	}
	/*class B
	{
	public:
		B()
		{
			_a1 = _a2;
		}
	private:
		int _b1;
	};*/
private:
	 int _a1;
	 int _a2;
};
class SLoutiojn
{
public: int func() {
	return 0;
}
};
//int A::_a1 = 0; //只能在外部进行定义
int main()
{
	
	cout << sizeof(A) << endl;  //8  

	//受到封装的影响
	//A::B b;

	//内部类天生是外部类的友元类
	
	//基本上用不上  能看懂就行



	//匿名对象
	A();
	SLoutiojn().func();  //可以这样直接调用
	//有名对象-
	A aa1;


	A aa3 = 5; // 先构造后拷贝直接优化
	const A& aa5 = 4; //无法优化 因为只有一个构造


	//优化也意味着激进， 可能会导致bug， 因为有时可能需要这个对象，但是没能构造出来
	//release 优化最激烈
	return 0;
}