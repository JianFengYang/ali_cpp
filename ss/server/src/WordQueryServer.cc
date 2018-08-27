 ///
 /// @file    WordQueryServer.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-23 15:03:46
 ///
#include "WordQueryServer.h" 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <string>
#define THREADNUM 4
#define QUESIZE 10
using std::cout;
using std::endl;
using std::string;
using namespace wd;
WordQueryServer::WordQueryServer(const string& filename)
	:_conf(filename)
	,_wordQuery(_conf)
	,_tcpServer(_conf.getIp(),_conf.getPort())
	,_pool(THREADNUM,QUESIZE)
{}

void WordQueryServer::onConnection(const TcpConnectionPtr& conn)
{
	cout << conn->toString() << endl;
	conn->send("hello,welcome to Chat Server.\r\n");
}
void WordQueryServer::onMessage(const TcpConnectionPtr& conn)
{
	string s(conn->receive());
	_pool.addTask(std::bind(&WordQuery::doQuery,&_wordQuery,s,conn));
	cout << "> add task to threadpool" << endl;
}
void WordQueryServer::onClose(const TcpConnectionPtr& conn)
{
	::printf("%s close\n",conn->toString().c_str());
}
void WordQueryServer::start()
{
	_pool.start();
	_tcpServer.setConnectionCallback(std::bind(&WordQueryServer::onConnection,this,std::placeholders::_1));
	_tcpServer.setMessageCallback(std::bind(&WordQueryServer::onMessage,this,std::placeholders::_1));
	_tcpServer.setCloseCallback(std::bind(&WordQueryServer::onClose,this,std::placeholders::_1));
	_tcpServer.start();
}

