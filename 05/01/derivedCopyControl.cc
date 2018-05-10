 ///
 /// @file    derivedCopyControl.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-01 21:49:21
 ///
#include<string.h> 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base()
	:_pdata(new char[1])
	{
		cout<<"Base()"<<endl;
	}

	Base(const char *pdata)
	:_pdata(new char[strlen(pdata)+1]())
	{
		strcpy(_pdata,pdata);
		cout<<"Base(const char *)"<<endl;
	}

	Base(const Base &rhs)
	:_pdata(new char[strlen(rhs._pdata)+1]())
	{
		strcpy(_pdata,rhs._pdata);
		cout<<"Base(const Base &)"<<endl;
	}

	Base& operator=(const Base &rhs)
	{
		cout<<"Base& operator=(const Base &)"<<endl;

		if(this!=&rhs)
		{
			delete []_pdata;
			_pdata=new char[strlen(rhs._pdata)+1]();
			strcpy(_pdata,rhs._pdata);
		}

		return *this;
	}

	~Base()
	{
		cout<<"~Base()"<<endl;
		delete []_pdata;
	}

	friend std::ostream& operator<<(std::ostream &os,
			const Base &rhs)
	{
		os<<rhs._pdata;
		return os;
	}
private:
	char *_pdata;
};

class Derived
:public Base
{

}
