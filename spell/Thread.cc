 ///
 /// @file    Thread.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-26 09:56:35
 ///


#include "Thread.h"
#include <iostream>

namespace wd
{


namespace current_thread
{
	__thread const char *threadName="wd";
}


struct ThreadDate
{
	typedef Thread::ThreadCallback ThreadCallback;
	ThreadCallback _cb;
	string _name;

	ThreadDate(const ThreadCallback &cb,
	const string &name)
	:_cb(cb)
	,_name(name)
	{}

	void runInThread()
	{
		current_thread::threadName=_name.empty()?"wd":
			_name.c_str();

		if(_cb)
			_cb();

	}
};

Thread::Thread(ThreadCallback cb,const string &name)
:_pthId(0)
,_isRunning(false)
,_cb(cb)
,_name(name)
{

}

Thread::~Thread()
{
	if(_isRunning)
		pthread_detach(_pthId);
}

void Thread::start()
{
	ThreadDate *pdata=new ThreadData(_cb,name);
	pthread_create(&_pthid,NULL,&Thread::threadFunc,pdata);

	_isRunning=true;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthId,NULL);
}

void* Thread::threadFunc(void *arg)
{
	ThreadData *pdata=static_cast<ThreadData*>(arg);
	if(pdata)
		pdata->runInThread();

	delete pdata;
}
}
