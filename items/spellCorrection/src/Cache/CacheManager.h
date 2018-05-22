 ///
 /// @file    CacheManager.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-22 15:52:20
 ///



#ifndef __WD_CACHEMANAGER_H__
#define __WD_CACHEMANAGER_H__
 
#include "Cache.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class CacheManager
{
public:
	static void initCache(size_t sz,const string &filename);
	static Cache& getCache(size_t idx);
	static void periodicUpdateCaches();

private:
	static vector<Cache>_cacheList;
};

#endif
