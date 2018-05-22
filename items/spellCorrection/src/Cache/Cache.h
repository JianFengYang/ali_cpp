 ///
 /// @file    Cache.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-22 11:15:21
 ///


#ifndef __MY_CACHE_H_
#define __MY_CACHE_H_

#include <iostream>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Cache
{
public:
	void readFromFile(const string &filename);
	void writeToFile(const string &filename);
	void updata(const Cache &rhs);

	void addElement(const string &key,const
			string &value);
	void debug();
	string query(const string &word);
private:
	unordered_map<string,string> _hashMap;
};

#endif
