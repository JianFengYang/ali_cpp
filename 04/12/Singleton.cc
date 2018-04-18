 ///
 /// @file    Singleton.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-13 13:47:15
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
public:
	static Singleton *getInstance()
	{
		if(_pInstance==NULL)
		{
			_pInstance=new Singleton;
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
		{
			delete _pInstance;
		}
	}

private:
	static Singleton *_pInstance;
	
	Singleton()
	{
		cout<<"Singleton()"<<endl;
	}

	~Singleton()
	{
		cout<<"~Singleton()"<<endl;
	}
};

Singleton *Singleton::_pInstance=NULL;

int main(void)
{
	Singleton *p1=Singleton::getInstance();
	Singleton *p2=Singleton::getInstance();

	cout<<"p1="<<p1<<endl;
	cout<<"p2="<<p2<<endl;

	Singleton::destroy();

	return 0;
}
