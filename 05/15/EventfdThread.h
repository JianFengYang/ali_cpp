 ///
 /// @file    EventfdThread.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-16 10:06:44
 ///


#ifndef __WD_EVENTFD_THREAD_H__
#define __WD_EVENTFD_THREAD_H__

#include "Thread.h"
#include "Eventfd.h"


namespace wd
{
class EventfdThread
{
public:
	using EventfdCallback=std::function<void()>;
	EventfdThread(EventfdCallback &&cb);

	void start();
	void stop();
	void wakeup();
private:
	Eventfd _eventfd;
	Thread _thread;
};
}
