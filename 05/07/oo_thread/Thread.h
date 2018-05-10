 ///
 /// @file    Thread.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-07 20:12:45
 ///
 //
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include"Noncopyable.h"
#include<pthread.h>

namespace wd
{
class Thread
:Noncopyable
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

	bool isRunning() const
	{
		return _isRunning;
	}

private:
	virtual void run()=0;

	static void *threadFunc(void *arg);

private:
	pthread_t _pthid;
	bool _isRunning;
};


#endif
}
