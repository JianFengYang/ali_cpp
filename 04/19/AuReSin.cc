 ///
 /// @file    AuReSin.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-21 10:26:31
 ///
 //单例对象自动释放方法第一：
 //嵌套类+静态对象
#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
	class AutoRelease
	{
		public:
			AutoRelease()
			{
				cout<<"AutoRelease()"<<endl;
			}
		~AutoRelease()
		{
			if(_pInstance)
			{
				delete _pInstance;
				cout<<"~AutoRelease()"<<endl;
			}
		}
	};
public:
	static Singleton *getInstance()
	{
		if(NULL==_pInstance)
		{
			_pInstance=new Singleton;
		}

		return _pInstance;

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
	static AutoRelease _auto;

};
//懒汉模式（懒加载），如果使用，必须加锁 //非线程安全
//Singleton *Singleton::_pInstance=NULL;//饿汉模式
//
//
//线程安全，饱汉模式
Singleton *Singleton::_pInstance=getInstance();


Singleton::AutoRelease Singleton::_auto;


int main(void)
{
	Singleton *p1=Singleton::getInstance();
	Singleton *p2=Singleton::getInstance();
	cout<<"p1="<<p1<<endl;
	cout<<"p2="<<p2<<endl;

	return 0;
}
