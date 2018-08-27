 ///
 /// @file    Configuration.cpp
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:38:54
 ///
#include "Configuration.h"
#include <stdlib.h>
#include <utility>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
Configuration::Configuration(const string& filepath)
	:_filepath(std::move(filepath))
{
	ifstream ifs(_filepath);
	if(!ifs)
		cout << "Configuration file open error" << endl;
	string key,value;
	while(ifs >> key,!ifs.eof())
	{
		ifs >> value;
		_configMap.insert(std::make_pair(key,value));
	}
	ifs.close();
}
map<string,string>& Configuration::getConfigMap()
{
	return _configMap;
}
set<string>& Configuration::getStopWordList()
{
	string stopWordPath = _configMap["myStopWord"];
	ifstream ifs(stopWordPath);
	if(!ifs){
		cout << "getStopWordList file open error" << endl;
		return _stopWordList;
	}
	string stopword;
	while(ifs >> stopword)
	{
		_stopWordList.insert(stopword);
	}
	return _stopWordList;
}
Configuration& Configuration::operator=(const Configuration& rhs)
{
	_filepath = rhs._filepath;
	_configMap = rhs._configMap;
	_stopWordList = rhs._stopWordList;
	return *this;
}
string Configuration::getIp() const
{
	auto cit = _configMap.find("myip");
	if(cit == _configMap.end())
	{
		return "";
	}
	return cit->second;
}
unsigned short Configuration::getPort() const
{
	auto cit = _configMap.find("myport");
	if(cit == _configMap.end())
		return 0;
	return atoi(cit->second.c_str());
}
