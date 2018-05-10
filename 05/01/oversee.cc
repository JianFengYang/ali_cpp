 ///
 /// @file    oversee.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-01 19:43:57
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base(int ix)
	:_ix(ix)
	{
		cout<<"Base(int)"<<endl;
	}

	void func(int y)
	{
		cout<<"Base::func()"<<endl;
	}

protected:
	int _ix;
};

class Derived
:public Base
{
public:
	Derived(int ix1,int ix2)
	:Base(ix1)
	,_ix(ix2)
	{
		cout<<"Derived(int,int)"<<endl;
	}

	void func()
	{
		cout<<"Derived::func()"<<endl;
		cout<<"Derived::_ix="<<_ix<<endl;
		cout<<"Base::_ix="<<Base::_ix<<endl;
	}

private:
	int _ix;
};

int main(void)
{
	Derived d(1,2);
	d.func();
	
	return 0;
}
