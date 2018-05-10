 ///
 /// @file    pureVirtual.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-03 15:05:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	virtual void display()=0;
	virtual void print()=0;
	virtual void show()=0;
};

class B
:public A
{
public:
	void display()
	{
		cout<<"B::display()"<<endl;
	}

	void print()
	{
		cout<<"B::print()"<<endl;
	}

	virtual void func1(){};
};

class C
:public B
{
public:
	void show()
	{
		cout<<"C::show()"<<endl;
	}
};

int main(void)
{
	A *pA=new C;
	pA->display();
	pA->print();
	pA->show();

	return 0;
}

