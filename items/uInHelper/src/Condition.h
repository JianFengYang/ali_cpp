 ///
 /// @file    Condition.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-18 18:41:47
 ///


#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h" 
#include <pthread.h>

namespace wd
{
class MutexLock;
class Condition
:Noncopyable
{
public:
	Condition(MutexLock &mutex);
	~Condition();

	void wait();
	void notify();
	void notifyAll();

private:
	MutexLock &_mutex;
	pthread_cond_t _cond;
};
}

#endif
