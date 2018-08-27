 ///
 /// @file    WordQuery.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-23 13:56:21
 ///
#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__
#include "Configuration.h"
#include "WordSegmentation.h"
#include "WebPage.h"
#include "TcpConnection.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
namespace wd
{
class WordQuery
{
public:
	WordQuery(Configuration& conf);
	void doQuery(string& str,TcpConnectionPtr& conn);
private:
	void loadLibary();
	map<string,int> getQueryWordsMap(vector<string>& queryWords);
	vector<pair<string,double> > getQueryWordsWeightVector(map<string,int>&);
	bool executeQuery(const vector<pair<string,double>>&,vector<pair<int,vector<double>>>&);
	string createJson(vector<pair<int,double>>&);
	string returnNoAnswer();
	int sumApperaance(const string& word);
	void processQuery(string& line);


	Configuration& _conf;
	WordSegmentation _jieba;
	unordered_map<int,WebPage> _pageLib;
	unordered_map<int,pair<int,int> > _offsetLib;
	unordered_map<string,set<pair<int,double>>> _inverIndexTable;
};

}; //end of namespace wd

#endif
