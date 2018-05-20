 ///
 /// @file    Dictionary.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-14 15:24:09
 ///


#include"Dictionary.h"

void Dictionary::read(const string &filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout<<"ifstream open error!"<<endl;
		return;
	}

	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string word;

		while(iss>>word)
		{
			++_dict[word];
		}
	}

	ifs.close();
}

void Dictionary::store(const string &filename)
{
	ofstream ofs(fliename);
	if(!ofs)
	{
		cout<<"ofstream open error!"<<endl;
		return;
	}

	for(auto&record:_dict)
	{
		ofs<<record.first<<" "<<record.second<<"\n";
	}

	ofs.close();
}

void Dictionary::index(const string &filename)
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
		++count;
		char f=line.front();

		auto it=_index.find(f);
		if(it!=_index.end())
		{
			it->second.insert(count);	
		}else{
			auto ret=_index.insert(std::make_pair
					(f,count));
		}
	}
	ifs.close();

	ofstream ofs("index.dat");
	if(!ofs)
	{
		cout<<"ofstream open error!"<<endl;

		return;
	}

	for(auto &re:_index)
	{
		ofs<<re.first<<" ";
		for(auto it=re->second.begin();it!=re->second.end())
		{
			ofs<<*it<<" ";
		}
		ofs<<"\n";
	}

	ofs.close();

}





