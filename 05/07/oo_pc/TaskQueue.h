 ///
 /// @file    TaskQueue.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-07 22:35:11
 ///
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include"Condition.h"
#include<queue>

namespace wd
{


class TaskQueue
{
public:
	using Type=int;
	TaskQueue(int queSize);

	bool full() const;
	bool empty() const;

	void push(Type &type);
	Type pop();

private:
	size_t _queSize;
	std::queue<Type> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
};

}


#endif
