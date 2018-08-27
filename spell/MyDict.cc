///
/// @file    MyDict.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-05-25 10:14:26
///


#include "MyDict.h"
#include <iostream>
#include <fstream>
#include <sstream>

MyDict *MyDict::pInstance=NULL;

MyDict* MyDict::createInstance()
{
	if(NULL==pInstance)
	{
		pInstance=new MyDict;
	}

	return pInstance;
}

	std::vector<std::pair<std::string,int>>& 
MyDict::get_dict()
{
	return _dict;
}

	std::map<std::string,std::set<int>>& 
MyDict::get_index_table()
{
	return _index_table;
}

void MyDict::show_dict()
{
	auto iter=_dict.begin();
	for(;iter!=_dict.end();++iter)
	{
		std::cout<<iter->first<<"-->"
			<<iter->second<<std::endl;
	}
}

void MyDict::show_index_table()
{
	auto iter=_index_table.begin();
	for(;iter!=_index_table.end();++iter)
	{
		std::cout<<iter->first<<"-->"
			auto sit=iter->second.begin();
		for(;sit!=iter->second.end();++sit)
		{
			std::cout<<*sit<<" ";
		}

		std::cout<<std::endl;
	}
}

void MyDict::read_from(const char *dictpath)
{
	std::ifstream in(dictpath);
	if(!in)
	{
		std::cout<<__DATE__<<" "<<
			__TIME__<<__FILE__<<" "<<
			<<__LINE__<<":dict read error"<<endl;

		exit(-1);
	}

	std::string line;
	while(getline(in,line))
	{
		std::stringstream ss(line);
		std::string key;
		int value;

		ss>>key>>value;

		_dict.push_back(make_pair(key,value));
	}

	in.close();
}

MyDict::MyDict(){}

void MyDict::init(const char *dictpath,const
		char *cnDictPath)
{
	read_from(dictpath);
	read_from(cnDictPath);

	for(size_t idx=0;idx!=_dict.size();++idx)
	{
		record_to_index(idx);
	}
}

void MyDict::record_to_index(int idx)
{
	std::string key;
	std::string word=_dict[idx].first;

	for(std::size_t iidx = 0; iidx != word.size(); ++iidx)
	{
		char ch = word[iidx];
		if(ch & (1 << 7))
		{//存储utf-8编码的中文字符
			if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
			{
				key = word.substr(iidx, 2);
				++iidx;
			}
			else if((ch & 0xF0) == 0xE0)
			{
				key = word.substr(iidx, 3);
				iidx += 2;
			}
			else if((ch & 0xFF) == 0xF0 || 
					(ch & 0xFF) == 0xF1 || 
					(ch & 0xFF) == 0xF2 || 
					(ch & 0xFF) == 0xF3 || 
					(ch & 0xFF) == 0xF4 || 
					(ch & 0xFF) == 0xF5 || 
					(ch & 0xFF) == 0xF6 || 
					(ch & 0xFF) == 0xF7)
			{
				key = word.substr(iidx, 4);
				iidx += 3;
			}
			else if((ch & 0xFF) == 0xF8 ||
					(ch & 0xFF) == 0xF9 || 
					(ch & 0xFF) == 0xFA || 
					(ch & 0xFF) == 0xFB) 
			{
				key = word.substr(iidx, 5);
				iidx += 4;
			}
			else if((ch & 0xFF) == 0xFC)
			{
				key = word.substr(iidx, 6);
				iidx += 5;
			}
		}
		else
		{
			key = word.substr(iidx, 1);
		}
		index_table_[key].insert(idx);
	}
}

