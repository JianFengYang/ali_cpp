 ///
 /// @file    main.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-13 11:01:15
 ///
#include "WordQueryServer.h"
#include "Configuration.h"
#include "CacheManger.h"
#include "TimerThread.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using namespace wd;
int main()
{
	WordQueryServer wordQueryServer("./conf/configure.txt");
	wordQueryServer.start();
	return 0;
}
