 ///
 /// @file    txtQuery.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-25 20:07:53
 ///
#include<string> 
#include <iostream>
#include<map>
#include<vector>
#include<set>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<math.h>
#include<utility>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;


using std::map;
using std::set;
using std::vector;

class TextQuery
{
public:
	
	void readFile(const string filename);
	void query(const string &word);

private:
	vector<string> _lines;
	map<string, set<int> > _word2Line;
	map<string,size_t>  _word_count;
	

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

};

void TextQuery::readFile(const string filename)
{
	ifstream ifs(filename);

	if(!ifs)
	{
		cout<<"ifstream open error!"<<endl;
		return;
	}

	string line;
	int line_cnt=0;
	while(std::getline(ifs,line))
	{
		line_cnt++;
		istringstream iss(line);
		_lines.push_back(" ");
		_lines.push_back(line);
		string word;

		while(iss>>word)
		{
			if(isWord(word))
			{
				++_word_count[word];
				if(0==_word_count.count(word))
				{
				set<int> a;
				a.insert(line_cnt);
				_word2Line.insert(
						std::make_pair(word,a));

				}else{
					auto it=_word2Line.find(word);
					(mit->second).insert(line_cnt);

				}
		}

	}

	ifs.close();

}

void TextQuery::query(const string &word)
{
	int ret=_word_count[word];
	cout<<word<" occurs "<<ret<<" times."<<endl;
	set<int>set_Line=_word2Line[word];
	
	set::const_iterator cit=set_Line.begin();
	while(cit!=set.end())
	{
		cout<<"(line "<<*cit<<")"<<_lines[*cit]<<endl;
		++cit;
	}
	
}

int main(int argc,char **argv)
{
	string queryWord("hello");

	TextQuery tq;
	tq.readFile("china_daily.txt");
	tq.query(queryWord);

	return 0;
}

