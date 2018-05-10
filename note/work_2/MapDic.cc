 ///
 /// @file    MapDic.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-24 21:53:14
 ///
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

using std::map;


class mapDic
{
public:
	mapDic()
	{}
	void read(const string &filename)
	{
		ifstream ifs(filename);
		if(!ifs)
		{
			cout<<"ifstream open error!";
			return;
		}

		string line;
		int count=0;

		while(getline(ifs,line))
		{
			istringstream iss(line);
			string word;

			while(iss>>word)
			{
				if(isWord(word))
				{
					++_work_count[word];
				}
			}

			++count;
			if((count%1000)==0)
			{
				cout<<"count="<<count<<endl;
			}

		}

		ifs.close();
		
	}
	void store(const string &filename)
	{
		ofstream ofs(filename);
		if(!ofs)
		{
			cout<<"ofstream open error!"<<endl;
			return;
		}

		for(const auto &w:_work_count)
		{
			ofs<<w.first<<" "<<w.second<<"\n";
		}

		ofs.close();
	}

private:
	bool isWord(const string &word)
	{
		for(size_t idx=0;idx!=word.size();++idx)
		{
			if(isdigit(word[idx]))
			{
				return false;
			}

			return true;
		}
	}
private:
	map<string,size_t> _work_count;
};

int main(void)
{
	mapDic mapdic;
	mapdic.read("The_Holy_Bible.txt");
	mapdic.store("mapdic.dat");
	return 0;
}
