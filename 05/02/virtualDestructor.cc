 ///
 /// @file    virtualDestructor.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-04 16:54:43
 ///
 
#include <iostream>
#include<string.h>
using std::cout;
using std::endl;

class Base
{
public:
	Base(const char *pdata)
	:_pdata(new char[strlen(pdata)+1]())
	{
		strcpy(_pdata,pdata);
		cout<<"Base(const char *)"<<endl;
	}

	virtual
	void display()
	{
		cout<<_pdata<<endl;
	}

	virtual ~Base()
	{
		delete []_pdata;
		cout<<"~Base()"<<endl;
	}
private:
	char *_pdata;
};

class Derived
:public Base
{
public:
	Derived(const char *pdata,const char *pdata2)
	:Base(pdata)
	,_pdata2(new char[strlen(pdata2)+1]())
	{
		strcpy(_pdata2,pdata2);
		cout<<"Derived(const char *,const char *)"<<endl;
	}

	void display()
	{
		Base::display();
		cout<<_pdata2<<endl;
	}

	~Derived()
	{
		delete []_pdata2;
		cout<<"~Derived()"<<endl;
	}

private:
	char *_pdata2;
};

int main(void)
{
	Base *pbase=new Derived("hello","world");
	delete pbase;
	return 0;
}
