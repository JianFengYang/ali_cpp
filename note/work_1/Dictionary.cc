#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>

#include<string.h>

using std::cout;
using std::endl;

using std::string;

using std::ifstream;
using std::ofstream;
using std::istringstream;

using std::vector;

struct Record
{
	Record(const string &word,int freq)
		:_word(word)
		 ,_freq(freq)
	{
	}
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
		Dictionary()
		{
			_dict.reserve(1000);
		}

		void read(const string &filename)
		{
			ifstream ifs(filename);
			if(!ifs)
			{
				cout<<"ifstream open error"<<endl;
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
						processWord(word);
					}
				}

				++count;
				if((count%1000)==0)
				{
					cout<<"count="<<count<<endl;
				}
			}

			ifs.close();
			std::sort(_dict.begin(),_dict.end());

		}


		void store(const string &filename)
		{
			ofstream ofs(filename);
			if(!ofs)
			{
				cout<<"ofstream open error"<<endl;
				return;
			}

			for(auto &record:_dict)
			{
				ofs<<record._word<<" "<<record._freq<<"\n";


			}

			ofs.close();

		}
	private:
		bool isWord(const string &word)
		{
			for(size_t idx=0;idx!=word.size();++idx)
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

int main(void)
{
	Dictionary dictionary;
	dictionary.read("The_Holy_Bible.txt");
	dictionary.store("dictionary.dat");
	return 0;
}

