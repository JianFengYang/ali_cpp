 ///
 /// @file    templateAdd.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 13:10:35
 ///
#include<string.h> 
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
T add(T x,T y);//函数模板的声明

template<typename T>
T add(T x,T y,T z)
{
	return x+y+z;
}

template <>
const char *add<const char *>(const char *p1,const char *p2)
{
	char *ptmp=new char[strlen(p1)+strlen(p2)+1]();
	strcpy(ptmp,p1);
	strcat(ptmp,p2);
	return ptmp;
}
