 ///
 /// @file    AuReSin2.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-21 13:17:42
 ///
#include<stdlib.h>
#include<pthread.h>

#include <iostream>
using std::cout;
using std::endl;

//单例对象自动释放方法第二：
//
//必须要在Linux环境下使用，因为关联了POSIX的线程库
//
//atexit +_pthread_once
//
class Singleton
{
public:	//在多线程下是安全的
	static Singleton *getInstance()
	{
		pthread_once(&_once,init);
		return _pInstance;
	}

	static void init()
	{
		_pInstance=new Singleton;
		::atexit(destroy);
	}

	static void destroy()
	{
		if(_pInstance)
		{
			delete _pInstance;
		}
	}

private:
	Singleton()
	{
		cout<<"Singleton()"<<endl;
	}

	~Singleton()
	{
		cout<<"~Singleton()"<<endl;

	}

	static Singleton *_pInstance;
	static pthread_once_t  _once;

};

Singleton *Singleton::_pInstance=NULL;
//懒汉模式，懒加载
//
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;

int main(void)
{
	Singleton *p1=Singleton::getInstance();
	Singleton *p2=Singleton::getInstance();

	cout<<"p1="<<p1<<endl;
	cout<<"p2="<<p2<<endl;

	return 0;
}
