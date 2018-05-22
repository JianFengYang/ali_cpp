 ///
 /// @file    CacheManager.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-22 15:54:31
 ///
#include "CacheManager.h"
#include "MyConf.h"
#include <iostream>
using std::cout;
using std::endl;

vector<Cache> CacheManager::_cacheList;

void CacheManager::initCache(size_t sz,const string &filename)
{
	Cache cache;
	cache.readFromFile(filename);

	for(size_t idx=0;idx!=sz;++idx)
	{
		_cacheList.push_back(cache);
	}
}

Cache & CacheManager::getCache(size_t idx)
{
	return _cacheList[idx];
}

void CacheManager::
