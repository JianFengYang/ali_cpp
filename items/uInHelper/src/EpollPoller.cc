 ///
 /// @file    EpollPoller.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-17 21:10:51
 ///


#include "EpollPoller.h"
#include "SocketUtil.h"
#include "Acceptor.h"
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
EpollPoller::EpollPoller(Acceptor &acceptor)
:_acceptor(acceptor)
,_epollfd(createEpollFd())
,_eventfd(createEventFd())
,_listenfd(_acceptor.fd())
,_isLooping(false)
,_eventsList(1024)
{
	addEpollFdRead(_epollfd,_listenfd);
	addEpollFdRead(_epollfd,_eventfd);
}

EpollPoller::~EpollPoller()
{
	::close(_epollfd);
}

void EpollPoller::loop()
{
	_isLooping=true;
	while(_isLooping)
	{
		waitEpollfd();
	}
}

void EpollPoller::unloop()
{
	if(_isLooping)
		_isLooping=false;
}

void EpollPoller::setConnectionCallback(
		EpollCallback cb)
{
	_onConnectionCb=cb;
}

void EpollPoller::setMessageCallback(
		EpollCallback cb)
{
	_onMessageCb=cb;
}

void EpollPoller::setCloseCallback(
		EpollCallback)
{
	_onCloseCb=cb;
}

void EpollPoller::waitEpollfd()
{
	int nready;
	do{
		nready=::epoll_wait(_epollfd,
				&(*_eventsList.begin()),
				_eventsList.size(),5000);

	}while(nready==-1&&errno==EINTR);

	if(nready==-1)
	{
		perror("epoll_wait error");
		exit(EXIT_FAILURE);
	}

	else if(0==nready)
	{
		printf("epoll_wait timeout\n");
	}
	else
	{
		if(nready==static_cast<int>(_eventsList.size()))
		{
			_eventsList.resize(_eventsList.size()*2);
		}

		for(int idx=0;idx!=nready;++idx)
		{
			if(_eventsList[idx].data.fd==_listenfd)
			{
				if(_eventsList[idx].events&EPOLLIN)
				{
					handleConnectin();
				}

			}else if(_eventsList[idx].data.fd==_eventfd)
			{
				handleRead();
				cout<<"> doPendingFuctors()"<<endl;
				doPendingFuctors();
			}else{
				if(_eventsList[idx].events&EPOLLIN)
				{
					handleMessage(_eventsList[idx].data.fd);
				}
			}
		}
	}

	
}

void EpollPoller::handleConnection()
{
	int peerfd=_acceptor.accept();
	addEpollFdRead(_epollfd,peerfd);

	TcpConnectionPtr connection(new TcpConnection(
			peerfd,this));

	conn->setConnectionCallback(_onConnectionCb);
	conn->setMessageCallback(_onMessageCb);
	conn->setCloseCallback(_onCloseCb_);

	std::pair<ConnectionMap::iterator,bool> ret;
	ret=_connMap.insert(std::make_pair(peerfd,conn));
	assert(ret.second==true);
	(void)ret;

	conn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int peerfd)
{
	bool isClosed=isConnectionClosed(peerfd);
	ConnectionMap::iterator it=_connMap.find(peerfd);
	assert(it!=_connMap.end());

	if(isClosed)
	{
		it->second->handleCloseCallback();
		delEpollReadFd(_epollfd,peerfd);
		_connMap.erase(it);
	}else{
		it->second->handleMessageCallback();
	}
}

void EpollPoller::runInLoop(const Functor &&cb)
{
	{
		MutexLockGuard mlg(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	}

	wakeup();
}

void EpollPoller::doPendingFunctors()
{
	std::vector<Functor> tmp;
	{
		MutexLockGuard mlg(_mutex);
		tmp.swap(_pendingFunctors);
	}

	for(auto &functor:tmp)
	{
		functor();
	}
}

void EpollPoller::handleRead()
{
	uint64_t howmany;
	int ret=::read(_eventfd,&howmany,
			sizeof(howmany));
	if(ret!=sizeof(howmany))
	{
		perror("read error");
	}
}

void EpollPoller::wakeup()
{
	uint64_t one=1;
	int ret=::write(_eventfd,&one,sizeof(one));
	if(ret!=sizeof(one))
	{
		perror("write error");
	}
}
}
