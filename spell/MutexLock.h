 ///
 /// @file    MutexLock.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-26 10:10:22
 ///


#ifndef __MY_MUTEXLOCK_H_
#define __MY_MUTEXLOCK_H_


#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
public:
	MutexLock();
	~MutexLcok();

	void lock();
	void unlock();
	pthread_mutex_t * getMutexLockPtr();

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};

class MutexLcokGuard
{

public:
	MutexLcokGuard(MutexLock &mutex)
	:_mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLcok &_mutex;
};

#endif
