 ///
 /// @file    MutexLock.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-26 10:14:34
 ///


#include"MutexLcok.h"
#include<iostream>

namespace wd
{
MutexLock::MutexLock()
:_isLocking(false)
{
	pthread_mutex_init(&_mutex,NULL);
}

MutexLock::~MutexLcok()
{
	pthread_mutex_destroy(&_mutex);
}

void MutexLcok::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking=true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking=false;
}

pthread_mutex_t * MutexLock::getMutexLockPtr()
{
	return &_mutex;
}


}
