 ///
 /// @file    Threadpool.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-08 21:34:19
 ///
#include"Threadpool.h"
#include"Thread.h"
#include<unistd.h>

#include<iostream>

using std::cout;
using std::endl;

using namespace wd;

Threadpool::Threadpool(size_t threadNum,size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false):
{
	_threads.reserve


}
