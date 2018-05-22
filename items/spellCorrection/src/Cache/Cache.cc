 
 
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-22 11:43:47
 ///
#include"Cache.h"
#include <iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;  

void Cache::addElement(const string &key,const string &value)
{
	_hashMap[key]=value;
}

string Cache::query(const string &word)
{
	auto iter=_hashMap.find(word);

	if(iter!=_hashMap.end())
	{
		return iter->second;
	}else{
		return string();
	}
}

void Cache::readFromFile(const string &filename)
{
	ofstream ofs(filename.c_str());
	if(!ofs.good())
	{
		cout<<"ofstream:write cache file error"<<endl;

		return;
	}

	auto iter=_hashMap.begin();

	for(;iter!=_hashMap.end();++iter)
	{
		ofs<<iter->first<<"\t"<<iter->second<<endl;
	}

	ofs.close();

}

void Cache::update(const Cache &rhs)
{
	auto iter=rhs._hashMap.begin();
	for(;iter!=rhs._hashMap.end();++iter)
	{
		_hashMap.insert(*iter);
	}
}

void Cache::debug()
{
	cout<<"Cache begin:"<<endl;
	for(auto &elem:_hashMap)
	{
		cout<<elem.first<<"-->"<<elem.second<<endl;
	}

	cout<<"Cache end:"<<endl;
}
