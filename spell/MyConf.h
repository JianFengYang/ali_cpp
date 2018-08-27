 ///
 /// @file    MyConf.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-25 10:50:20
 ///


#ifndef _CONF_H
#define _CONF_H

#include <string>
#include <map>

using std::string;
using std::map;


class MyConf
{
public:
	static MyConf* getInstance();

	map<string,string>& getMap()
	{
		return _map;
	}

	bool init(const string &filename);
	void show();

private:
	MyConf(){}
	~MyConf(){}

private:
	map<string,string>_map;
	static MyConf* _pInstance;
};

#endif


