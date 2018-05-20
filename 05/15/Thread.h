 ///
 /// @file    Thread.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-15 21:34:59
 ///

#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace wd
{
class Thread
:Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback &&cb);
	~Thread();

	void start();
	void join();

	bool isRunning() const
	{
		return _isRunning;
	}

private:
	static void* threadFunc(void *arg);
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
};
}

#endif
