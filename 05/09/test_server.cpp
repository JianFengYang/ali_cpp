 ///
 /// @file    test_server.cpp
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-10 15:26:03
 ///


#include"SockerUtil.h"
#include"InetAddress.h"
#include"SocketIO.h"
#include"Acceptor.h"
#include"TcpConnection.h"

#include<string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main(int argc,char const **argv)
{
	wd::InetAddress addr("192.168.22.22".9996);
	wd::Acceptor acceptor(wd::createSocketFd(),addr);
	acceptor.ready();

	int peerfd=acceptor.accept();
	wd::TcpConnection conn(peerfd);
	conn.send("welcome to chat server!");

	while(1)
	{

		string msg=conn.receive();
		cout<<"server receive:"<<msg<<endl;

		conn.send(msg);
	}
	return 0;
}
