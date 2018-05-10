 ///
 /// @file    Thread.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-07 20:22:29
 ///
#include"Thread.h"

namespace wd
{
Thread::Thread()
:_pthid(0)
,_isRunning(false)
{}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthid);
		_isRunning=false;
	}
}

void Thread::start()
{
	pthread_create(&_pthid,NULL,threadFunc,this);
	_isRunning=true;
}

void* Thread::threadFunc(void *arg)
{
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread)
	{
		pthread->run();
	}
	return NULL;
}

void Thread::join()
{
	if(_isRunning)
	{
		pthread_join(_pthid,NULL);
	}
}


}
