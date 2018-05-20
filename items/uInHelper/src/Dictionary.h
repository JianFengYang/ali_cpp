 ///
 /// @file    Dictionary.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-14 15:30:27
 ///

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include<string.h>
#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<alogrithm>
#include<utility>

using std::cout;
using std::endl;

using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

class Dictionary
{
public:
	Dictionary()
	{}

	void read(const string &filename);
	void store(const string &filename);
	void index(const string &filename);

private:
	map<string,int> _dict;
	map<char,set<int>> _index;
}


#endif
