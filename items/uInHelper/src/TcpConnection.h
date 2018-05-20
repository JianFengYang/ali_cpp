 ///
 /// @file    TcpConnection.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-17 16:53:10
 ///
 //
#ifndef _WD_TCPCONNCETION_H
#define _WD_TCPCONNCETION_H

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace wd
{
class EpollPoller;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpCpnnectionPtr;

class TcpConnection
:Noncopyable
,public std::enable_shared_from_this<TcpConnection>
{

public:
	typedef std::function<void(const TcpConnectionPtr &)> 
		TcpConnectionCallback;
	~TcpConnection();

	std::string receive();
	void send(const std::string &msg);
	void sendInLoop(const std::string &msg);

	void shutdown();

	std::string toString();

	void setConnectionCallback(
			TcpConnectionCallback cb);
	void setMessageCallback(
			TcpConnectionCallback cb);
	void setCloseCallback(
			TcpConnectionCallback cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

private:
	Socket _sockfd;
	SocketIO _sockIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;
	EpollPoller *_loop;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;



};
}

#endif
