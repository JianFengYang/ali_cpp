 ///
 /// @file    Socket.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-15 21:18:22
 ///


#ifndef __SOCKET_H__
#define __SOCKET_H__

#include"Noncopyable.h"

namespace wd
{
class InetAddress;
class Socket
:Noncopyable
{
	Socket(int sockfd);
	Socket();
	~Socket();

	void shutdownWrite();
	int fd() const
	{
		return _sockfd;
	}

	void nonblock();
	
	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);

private:
	int _sockfd;
};
}

#endif
