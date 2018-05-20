 ///
 /// @file    Socket.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-11 16:11:17
 ///

#ifndef __WD_SOCKET_H
#define __WD_SOCKET_H

#include "Noncopyable.h"

namespace wd
{
class InetAddress;
class Socket
:Noncopyable
{
public:
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
	static InerAddress getPeerAddr(int sockfd);

private:
	int _sockfd;
};
}

#endif

