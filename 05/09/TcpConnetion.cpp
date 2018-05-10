 ///
 /// @file    TcpConnetion.cpp
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-10 15:10:00
 ///


#include"TcpConnetion.h"
#include<string.h>
#include<stdio.h>

namespace wd
{
TcpConnetion::TcpConnetion(int sockfd)
:sockfd_(sockfd)
,sockIO(sockfd)
,localAddr_(wd::Socket::getLocalAddr(sockfd))
,peerAddr_(wd::Socket::getPeerAddr(sockfd))
,isShutdownwrite_(false)
{}


TcpConnction::~TcpConnection()
{
	if(!isShutdownWrite_)
	{
		isShutdownWrite_=true;
		shutdown();
	}

	printf("~TcpConnection()\n");
}

std::string TcpConnection::receive()
{
	char buf[65536];
	memset(buf.0,sizeof(buf));
	size_t ret=sockIO_.readline(buf,sizeof(buf));
	if(0===ret)
	{
		return std::string();
	}else{

		return std::string(buf);
	}
}

void TcpConnction::send(const std::string &msg)
{
	sockIO.writen(msg.c_ctr(),msg.size());
}

void TcpConnction::shutdown()
{
	if(!isShutdownWrite_)
	{
		sockfd_.shutdownWrite();
		isShutdownWrite_=true;
	}
}

std::string TcpConnection::toString()
{
	char str[100];
	snprintf(str,sizeof(str),"%s:%d->%s:%d",
			localAddr_.ip().c_str(),
			localAddr_.port(),
			peerAddr_.ip().c_str(),
			peerAddr_.port());
	return std::string(str);
}


}

