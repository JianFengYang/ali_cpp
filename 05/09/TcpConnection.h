 ///
 /// @file    TcpConnection.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-10 15:00:51
 ///


#ifndef __WD_TCPCONNCTION_H__
#define __WD_TCPCONNCTION_H__

#include"Noncopyable.h"
#include"InetAddress.h"
#include"Socket.h"
#include"SocketIO.h"

#include<string>
#include<memory>
#include<functional>

namespace wd
{
class TcpConnection
:Noncopyable
{
public:
	TCPConnection(int sockfd);
	~TcpConnetion();

	std::string receive();
	void send(const std::string &msg);
	void shutdown();

	std::string toString();

private:
	Socket sockfd_;
	SocketIO sockIO_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	bool isShutdownWrite_;
};
}

#endif
