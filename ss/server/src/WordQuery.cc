 ///
 /// @file    WordQuery.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-23 14:18:10
 ///
#include "WordQuery.h"
#include "TcpConnection.h"
#include "WebPage.h"
#include "json/json.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>
#include <cctype>
#define DEBUG 0
using std::ifstream;
using std::istringstream;
using std::map;
using std::pair;
using std::cout;
using std::endl;

using namespace wd;

WordQuery::WordQuery(Configuration& conf)
	:_conf(conf)
	,_jieba()
{
	loadLibary();
}
void WordQuery::loadLibary()
{
	map<string,string>& config = _conf.getConfigMap();
	string pageLibPath = config["myPageLib"];
	string offsetLibPath = config["myOffsetLib"];
	string indexLibPath = config["myIndexLib"];
	ifstream ifsPage(pageLibPath);
	ifstream ifsOffset(offsetLibPath);
	ifstream ifsIndex(indexLibPath);
	if(!ifsPage || !ifsOffset ||!ifsIndex)
	{
		cout << "loadLibary file open error" << endl;
		return;
	}
	int offset,len;
	while(ifsOffset >> offset)
	{
		string doc = "";
		ifsOffset >> len;
		ifsPage.seekg(offset,std::ios_base::beg);
		int left = len;
		while(left > 0)
		{
			char tmp;
			ifsPage >> tmp;
			--left;
			doc += tmp;
		}
		WebPage tmpPage(doc,_conf,_jieba);
		int id = tmpPage.getDocId();
		pair<int,int> myoffset = std::make_pair(offset,len);
		_offsetLib.insert(std::make_pair(id,myoffset));
		_pageLib.insert(std::make_pair(id,tmpPage));
	}
	string indexLine;
	while(std::getline(ifsIndex,indexLine))
	{
		istringstream iss(indexLine);
		string word;
		iss >> word;
		int key;
		double value;
		while(iss >> key)
		{
			iss >> value;
			auto cit = _inverIndexTable.find(word);
			if(cit == _inverIndexTable.end()){
				set<pair<int,double>> tmp;
				tmp.insert(std::make_pair(key,value));
				_inverIndexTable.insert(std::make_pair(word,tmp));
			}else{
				cit->second.insert(std::make_pair(key,value));
			}
		}
	}
}
void WordQuery::processQuery(string& line)
{
	auto cit = line.begin();
	for(;cit != line.end(); ++cit)
	{
		if(isspace(*cit)){
			cit = line.erase(cit);
			--cit;
		}
	}
}
void WordQuery::doQuery(string& str,TcpConnectionPtr& conn)
{
#if 0  //DEBUG
	cout << "In WordQuery:: doQuery" << endl;
#endif
	processQuery(str);   //将str中的空白符去除
	vector<string> queryWords = _jieba.Cut(str);
	for(auto word:queryWords)
		cout << ">>> cut word is " << word << endl;
	map<string,int> processedQueryWords = getQueryWordsMap(queryWords);    //返回处理过的查询词（合并相同的查询词）
	vector<pair<string,double>> queryWordsWeightVec = getQueryWordsWeightVector(processedQueryWords);
#if 0 //DEBUG
	for(auto a:queryWordsWeightVec)
	{
		cout << ">>>> in queryWordsWeightVec   " << a.first << " " << a.second << endl;
	}
#endif
	string firstQueryWord = queryWordsWeightVec.begin()->first;
	double moduleQuery = 0;
	for(auto queryPair:queryWordsWeightVec)
			moduleQuery += queryPair.second * queryPair.second;
	moduleQuery = ::sqrt(moduleQuery);
#if DEBUG
	cout << ">>>>moduleQuery is " << moduleQuery << endl;
#endif
	vector<pair<int,vector<double>>> resultVec;
	bool flag = executeQuery(queryWordsWeightVec,resultVec);
	if(flag){
#if DEBUG
		cout << "flag is true" << endl;
#endif
		vector<pair<int,double>> cosinRes;
		for(auto myres:resultVec)  //生成摘要并计算模
		{
			double moduleRes = 0;
			double sum = 0;
			int docId = myres.first;
			auto pageIter = _pageLib.find(docId);
			WebPage& mypage = pageIter->second;
			string pagedoc = mypage.getDoc();   //一篇pagedoc就是一行
			int  pos = pagedoc.find(firstQueryWord);
			string docline(pagedoc.begin() + pos -50,pagedoc.begin() + pos +50);
			mypage._docSummary = docline;
#if DEBUG
			cout << ">>>> SUMMARY IS " << docline << endl;
#endif
			for(size_t i=0;i<myres.second.size();++i)
			{
				sum += myres.second[i]*(queryWordsWeightVec[i].second);
				moduleRes += (myres.second)[i] * (myres.second)[i];
			}
			moduleRes = ::sqrt(moduleRes);
			cosinRes.push_back(std::make_pair(docId,sum/(moduleRes * moduleQuery)));
		}
		string jsonResult = createJson(cosinRes);
		conn->sendInLoop(jsonResult);
#if DEBUG
		cout << ">>>JsonResult is " << jsonResult << endl;
#endif
	}else{
#if DEBUG
		cout << "flag is false" << endl;
#endif 
		string jsonResult = returnNoAnswer();
		conn->sendInLoop(jsonResult);
	}
}
string WordQuery::returnNoAnswer()
{
	Json::FastWriter writerinfo;
	Json::Value obj,new_item;
	new_item["标题"] = "404,not found";
	new_item["摘要"] = "亲,I cannot find what you want. What a pity";
	obj.append(new_item);
	string strEmail = writerinfo.write(obj);
	return strEmail;
}
bool cmp(pair<int,double> a,pair<int,double> b)
{
	if(a.second!=b.second)
		return a.second > b.second;
	else
		return a.first <= b.first ;
}
string WordQuery::createJson(vector<pair<int,double>>& resultVec)
{
	std::sort(resultVec.begin(),resultVec.end(),cmp);
	Json::FastWriter writerinfo;
	Json::Value arrayObj;
	auto cit = resultVec.begin();
	for(;cit != resultVec.begin() + 10&& cit != resultVec.end(); ++cit)
	{
		auto pageIter = _pageLib.find(cit->first);
		WebPage& mypage = pageIter->second;
		Json::Value new_item;
		new_item["标题"] =  mypage.getTitle();
		new_item["url"] = mypage.getUrl();
		new_item["摘要"] = mypage._docSummary;
		arrayObj.append(new_item);
	}
	string strEmail = writerinfo.write(arrayObj);
	return strEmail;
}
bool WordQuery::executeQuery(const vector<pair<string,double>>& queryWordsWeightVec,vector<pair<int,vector<double>>>& resultVec)
{
#if 1                  //找到文章Id的集合
	auto iter = queryWordsWeightVec.begin();
	auto cit = _inverIndexTable.find(iter->first);
	set<int> docIdGather;
	if(cit == _inverIndexTable.end())
		return false;
	set<pair<int,double>> articleGather = cit->second;   //取出第一个查询词的所有文章
	for(auto oneArticle:articleGather)  //对查询词中的文章进行查询，若其他查询词也在其中，则为结果文章
	{
		bool flag = true;
		int docId = oneArticle.first;
		auto pageIter = _pageLib.find(docId);
		WebPage& tmp = pageIter->second;
		map<string,int>& wordsMap = tmp.getWordsMap();
		for(auto myQueryWord: queryWordsWeightVec)
		{
			auto queryIter = wordsMap.find(myQueryWord.first);
			if(queryIter == wordsMap.end()){    //如果有一篇文章中不包含所有查询词，就返回false
				flag = false;  
			}
		}
		if(flag){
			vector<double> weightVec;
			docIdGather.insert(docId);
		}
	}
#endif
	if(docIdGather.size() == 0)
		return false;
	else{
		for(auto docId: docIdGather)   //查找每一篇文章中对应查询词的权重，构成向量
		{
			vector<double> tmp;
			for(auto myQueryWord:queryWordsWeightVec)
			{
				auto citer = _inverIndexTable.find(myQueryWord.first);
				for(auto mypair:citer->second)
				{
					if(mypair.first == docId){
						tmp.push_back(mypair.second);
						break;
					}
				}
			}
			resultVec.push_back(std::make_pair(docId,tmp));
		}
		return true;
	}
}


vector<pair<string,double> > WordQuery::getQueryWordsWeightVector(map<string,int>& processedQueryWords)
{
#if DEBUG 
	cout << "In WordQuery getQueryWordsWeightVector() " << endl;
#endif
	vector<pair<string,double>> tmp;
	double w_total = 0;
	for(auto& mypair:processedQueryWords)
	{
		int tf = mypair.second;
		int DF = sumApperaance(mypair.first) + 1;
		int N = _pageLib.size() + 1;
#if DEBUG //DEBUG
		cout << " >> N is " << N << endl;
		cout << ">>>> DF is " << DF << endl;
#endif 
		double w = (double)tf * :: log10(N/DF)/ ::log10(2);
#if DEBUG //DEBUG
		cout << ">>>>> w is " << w << endl;
#endif 
		w_total += w*w;
		tmp.push_back(std::make_pair(mypair.first,w));
	}
#if DEBUG
	cout << ">>> w_total is " << w_total << endl;
#endif
	if(w_total)
		for(auto& mypair:tmp)     //归一化处理
		{
			mypair.second /= (::sqrt(w_total));
#if DEBUG
			cout << "In the tmpVec w is " << mypair.second << endl;
#endif
		}
	return tmp;
}
int WordQuery::sumApperaance(const string& word)
{
#if DEBUG
	cout << "In sumApperaance" << endl;
#endif
	int cnt = 0;
	for(auto& mypage:_pageLib)
	{
		map<string,int>& oneArticle = mypage.second.getWordsMap();
		auto cit = oneArticle.find(word);
		if(cit != oneArticle.end())
			++cnt;
	}
	return cnt;
}
map<string,int> WordQuery::getQueryWordsMap(vector<string>& queryWords)
{
#if DEBUG //DEBUG
	cout << "In the getQueryWordsMap" << endl;
#endif
	map<string,int> tmp;
	for(auto word:queryWords)
	{
		auto cit = tmp.find(word);
		if(cit == tmp.end())
		{
			tmp.insert(std::make_pair(word,1));
		}else
			++cit->second;
	}
#if DEBUG //DEBUG
	for(auto mytmp:tmp)
		cout << ">>> In tmp Map " << mytmp.first << " " << mytmp.second << endl;
#endif
	return tmp;
}
