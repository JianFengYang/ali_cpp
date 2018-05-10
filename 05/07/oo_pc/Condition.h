 ///
 /// @file    Condition.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-07 22:14:19
 ///
#ifndef __WD_CONDITION_H__
#define _WD_CONDITION_H__

#include"Noncopyable.h"
#include<pthread.h>

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
