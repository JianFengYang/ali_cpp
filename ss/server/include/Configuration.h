 ///
 /// @file    Configuration.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:33:10
 ///
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include <string>
#include <map>
#include <set>
using std::string;
using std::map;
using std::set;
class Configuration
{
public:
	Configuration(const string& filePath);
	map<string,string>& getConfigMap();
	set<string>& getStopWordList();
	Configuration& operator=(const Configuration& rhs);
	string getIp() const;
	unsigned short getPort() const;
private:
	string _filepath;
	map<string,string> _configMap;
	set<string> _stopWordList;
};
template<typename T>
class Singleton
{
public:
	template<typename ...Args>
	static T* getInstance(Args ...args)
	{
		if(!_pInstance)
			_pInstance = new T(args...);
		return _pInstance;
	}
	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
private:
	Singleton();
	~Singleton();
	static T *_pInstance;
};
template<typename T>
T * Singleton<T>::_pInstance = NULL;

#endif
