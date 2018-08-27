 ///
 /// @file    WordQueryServer.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-23 14:53:50
 ///
#ifndef __WORDQUERYSERVER_H__
#define __WORDQUERYSERVER_H__
#include "TcpServer.h"
#include "Condition.h"
#include "WordQuery.h"
#include "Threadpool.h"
#include "TcpConnection.h"
#include <iostream>
#include <utility>
using std::cout;
using std::endl;
using std::pair;
namespace wd{
class WordQueryServer
{	
public:
	WordQueryServer(const string& filename);
	void start();
private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn);
	void onClose(const TcpConnectionPtr& conn);
	void doTaskThread(const TcpConnectionPtr& conn,const string& msg);

	Configuration _conf;
	WordQuery _wordQuery;
	TcpServer _tcpServer;
	Threadpool _pool;
};

}; // end of namespace wd
#endif
