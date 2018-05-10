 ///
 /// @file    MutexLock.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-08 15:56:02
 ///


#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include"Noncopyable.h"
#include<pthread.h>

namespace wd
{
class MutexLock
:Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();

	bool isLocking() const
	{
		return _isLocking;
	}

	 pthread_mutex_t* getMutexLockPtr()
	 {
		 return &_mutex;
	 }

private:
	 pthread_mutex_t _mutex;
	 bool _isLocking;
};

}


#endif
