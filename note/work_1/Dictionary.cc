 ///
 /// @file    Dictionary.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-16 20:21:57
 ///
 
#include <iostream>
#include<vector>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record
{
	Record(const string &word,int freq)
	:_word(word)
	,_freq(freq)
	{}

	string _word;
	int _freq;
};

bool operator<(const Record &lhs,const Record &rhs)
{
	return lhs._word<rhs._word;
}

class Dictionary
{
public:
	Dictinary()
	{
		_dict.reserve(1000);
	}

	void read(const string & filename)
	{
		ifstream ifs(filename);
	}
private:
	bool isWord(const string &word)
	{
		for(size_t idx=0;idx!=word.size(),++idx);
		{
			if(isdigit(word[idx]))
				return false;
		}
		return true;

	}

	void processWord(const string &word)
	{
		size_t idx;

		for(idx=0;idx!=_dict.size();++idx)
		{
			if(_dict[idx]._word==word)
			{
				++_dict[idx]._freq;
				break;
			}
		}

		if(idx>=_dict.size())
		{
			_dict.push_back(Record(word,1));
		}
	}
private:
	vector<Record> _dict;


};

