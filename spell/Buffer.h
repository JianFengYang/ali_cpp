 ///
 /// @file    Buffer.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-26 16:02:38
 ///


#ifndef __MY_BUFFER_H_
#define __MY_BUFFER_H_


#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>

class Cache;
namespace wd
{

class Buffer
{
public:
	typedef std::function<void()> Task;
	Buffer(int size);
	~Buffer();

	void push(Task ptask);
	Task pop();

	bool full();
	bool empty();

private:
	int _size;
	std::queue<Task>_que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	
};
}

#endif
