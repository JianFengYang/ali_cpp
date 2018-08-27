 ///
 /// @file    MyConf.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-25 10:53:43
 ///


#include "MyConf.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::ifstream;
using std::cout;
using std::endl;
using std::istringstream;


MyConf* MyConf::_pInstance=getInstance();

MyConf* MyConf::getInstance()
{
	if(NULL==_pInstance)
	{
		_pInstance=new MyConf;

	}

	return _pInstance;
}

bool MyConf::init(const string &filename)
{
	ifstream ifs(filename.c_str());
	if(!ifs)
	{
		cout<<"file read error"<<endl;

		return false;
	}

	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key,value;

		iss>>key>>value;

		_map.insert(make_pair(key,value));
	}

	ifs.close();

	return true;
}

void MyConf::show()
{
	map<string,string>::const_iterator mit _map.begin();
	for(;mit!=_map.end();++mit)
	{
		cout<<mit->first<<"-->"<<mit->second<<endl;
	}
}


