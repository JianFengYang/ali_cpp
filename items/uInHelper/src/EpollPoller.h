 ///
 /// @file    EpollPoller.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-17 20:22:51
 ///
#ifndef __WD_EPOLLPOLLER_H
#define __WD_EPOLLPOLLER_H

#include "Noncopyable.h"
#include "TcpConnection.h"
#include "MutexLock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

namespace wd
{
class Acceptor;
class EpollPoller
:Noncopyable
{
public:
	typedef TcpConnection::
		TcpConnectionCallback EpollCallback;
	typedef std::function<void()> Functor;

	EpollPoller(Acceptor &acceptor);
	~EpollPoller();

	void loop();
	void unloop();
	void runInLoop(const Functor &&cb);
	void doPendingFunctors();
	void wakeup();

	void setConnectionCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage();
	void handleRead();

private:
	Acceptor & _acceptor;
	int _epollfd;
	int _eventfd;
	int _listenfd;
	bool isLooping;

	MutexLock _mutex;
	std::vector<Functor> _pendingFunctors;

	typedef std::vector<struct epoll_event>
		EventList;
	EventList _eventsList;

	typedef std::map<int,TcpConnectionPtr>
		ConnectinMap;
	ConnectionMap _connMap;

	EpollCallback _onConnectionCb;
	EpollCallback _onMessageCb;
	EpollCallback _onCloseCb;

};
}

#endif
