 ///
 /// @file    abstractClass.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-03 15:16:25
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

protected:
	A()
	{
		cout<<"A()"<<endl;
	}
};

class B
:public A
{
public:
	B()
	{
		cout<<"B()"<<endl;
	}
};

int main(void)
{
	A *pA=new B;
	pA->display();

	return 0;
}
