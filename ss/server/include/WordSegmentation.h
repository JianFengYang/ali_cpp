 ///
 /// @file    WordSegmentation.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-18 21:49:19
 ///
#ifndef __WORDSEGMENTATION_H__
#define __WORDSEGMENTATION_H__
#include "/home/xubo/C++_programme/program2/cppjieba/include/cppjieba/Jieba.hpp"
#include <string>
#include <vector>
using std::string;
using std::vector;
const char* const DICT_PATH = "/home/xubo/C++_programme/program2/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/xubo/C++_programme/program2/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/xubo/C++_programme/program2/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/xubo/C++_programme/program2/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/xubo/C++_programme/program2/cppjieba/dict/stop_words.utf8";

class WordSegmentation
{
public:
	WordSegmentation()
		:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
	{}
	vector<string>  Cut(string &sentence)
	{
		vector<string> tmp;
		_jieba.Cut(sentence,tmp);
		return tmp;
	}
private:
	cppjieba::Jieba _jieba;
};
#endif
