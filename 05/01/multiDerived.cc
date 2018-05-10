 ///
 /// @file    multiDerived.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-01 13:06:50
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void display() const
	{
		cout<<"A::display()"<<endl;
	}

	void setA(int ia)
	{
		_ia=ia;
	}
private:
	int _ia;
};

class B
:virtual public A
{
public:
	void show() const
	{
		cout<<"B::show()"<<endl;
	}
};

class C
:virtual public A
{
public:

};

class D
:public B
,public C
{};

int main()
{
	D d;
	d.setA(10);
	d.display();

	return 0;
}

