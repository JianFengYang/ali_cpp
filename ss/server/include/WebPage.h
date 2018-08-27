 ///
 /// @file    WebPage.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-18 21:37:22
 ///
#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__
#include "WordSegmentation.h"
#include "Configuration.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::string;
class WebPage
{
public:
	WebPage(string doc,Configuration& config,WordSegmentation& jieba);
	int getDocId() ;
	const string& getDoc() const;
	map<string,int>& getWordsMap() ;  //获取文档的词频统计map
	const string& getTitle() const;
	const string& getUrl() const;

	WebPage(const WebPage & rhs);
	WebPage(WebPage && rhs);

	WebPage& operator=(WebPage&& rhs);
	WebPage& operator=(const WebPage& rhs);
	string _docSummary;

private:
	void processDoc(string& doc,WordSegmentation&);
	string _doc;
	int _docId;	
	string _docTitle;
	string _docUrl;
	string _docContent;
	map<string,int> _wordsMap;
	Configuration& _conf;
};

#endif
