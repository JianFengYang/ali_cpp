 ///
 /// @file    WebPage.cc
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-18 22:09:11
 ///
#include "WebPage.h" 
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::pair;
bool cmp(pair<string,int> a, pair<string,int> b)
{
	if(a.second != b.second)
		return a.second > b.second;
	else
		return a.first.size() < b.first.size();
}
const string& WebPage::getUrl() const
{
	return _docUrl;
}
const string& WebPage::getTitle() const
{
	return _docTitle;
}
WebPage::WebPage(string doc,Configuration& config,WordSegmentation& jieba)
	:_doc(std::move(doc))
	,_conf(config)
{
	auto n1 = _doc.find("<docid>");     //在格式化字符串中取得id
	auto cit1 = _doc.begin() + n1 + 7;
	auto n2 = _doc.find("</docid>");
	auto cit2 = _doc.begin() + n2;
	string docId(cit1,cit2);
	_docId = ::atoi(docId.c_str());
	n1 = _doc.find("<url>");           //在格式化字符串中取得url
	cit1 = _doc.begin() + n1 + 5;
	n2 = _doc.find("</url>");
	cit2 = _doc.begin() + n2;
	_docUrl.insert(_docUrl.end(),cit1,cit2);
	n1 = _doc.find("<title>");       //在格式化字符串中取得title
	n2 = _doc.find("</title>");
	cit1 = _doc.begin() + n1 + 7;
	cit2 = _doc.begin() + n2;
	_docTitle.insert(_docTitle.end(),cit1,cit2);
	n1 = _doc.find("<content>");     //在格式化字符串中取得content
	n2 = _doc.find("</content>");
	cit1 = _doc.begin() + n1 + 9;
	cit2 = _doc.begin() + n2;
	_docContent.insert(_docContent.end(),cit1,cit2);
	processDoc(_docContent,jieba);	
}
void WebPage::processDoc(string& doc,WordSegmentation& jieba)
{
	vector<string> results = jieba.Cut(doc);
	for(auto myresult:results)
	{
		auto cit = _wordsMap.find(myresult);
		if(cit == _wordsMap.end())
			_wordsMap.insert(std::make_pair(myresult,1));
		else
			++ cit->second;
	}
}
int WebPage::getDocId() 
{
	return _docId;
}
const string& WebPage::getDoc() const
{
	return _doc;
}
map<string,int>& WebPage::getWordsMap() 
{
	return _wordsMap;
}
WebPage& WebPage::operator=(WebPage&& rhs)
{
	_doc = std::move(rhs._doc);
	_docId = std::move(rhs._docId);
	_docTitle = std::move(rhs._docTitle);
	_docUrl = std::move(rhs._docUrl);
	_docSummary = std::move(rhs._docSummary);
	_docContent = std::move(rhs._docContent);
	_wordsMap = std::move(rhs._wordsMap);
	_conf = rhs._conf;
	return *this;
}

WebPage& WebPage::operator=(const WebPage& rhs)
{
	_doc = rhs._doc;
	_docId = rhs._docId;
	_docTitle = rhs._docTitle;
	_docUrl = rhs._docUrl;
	_docSummary = rhs._docSummary;
	_docContent = rhs._docContent;
	_wordsMap = rhs._wordsMap;
	_conf = rhs._conf;
	return *this;
}
WebPage::WebPage(const WebPage& rhs)
	:_conf(rhs._conf)
{
	_doc = rhs._doc;
	_docId = rhs._docId;
	_docUrl = rhs._docUrl;
	_docTitle = rhs._docTitle;
	_docContent = rhs._docContent;
	_docSummary = rhs._docSummary;
	_wordsMap = rhs._wordsMap;
}
WebPage::WebPage(WebPage&& rhs)
	:_conf(std::ref((rhs._conf)))
{
	_doc = std::move(rhs._doc);
	_docId = std::move(rhs._docId);
	_docUrl = std::move(rhs._docUrl);
	_docTitle = std::move(rhs._docTitle);
	_docContent = std::move(rhs._docContent);
	_docSummary = std::move(rhs._docSummary);
	_wordsMap = std::move(rhs._wordsMap);
}
