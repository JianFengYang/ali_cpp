 ///
 /// @file    varTemp.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 17:43:31
 ///
#include<string> 
#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename... Args>//Args 模板参数包
void display(Args... args)//args 函数参数包
{
	cout<<"sizeof(Args)="<<sizeof...(Args)<<endl;
	cout<<"sizeof(args)="<<sizeof...(args)<<endl;



}	

void test()
{
	display(1);
	display(1,'a');
	display(1,'a',string("hell"));
	display(1,'a',"hell",1.1);
	return 0;
}

void test1()
{
	print(1,2,3,4);
	print(2,3,4);
}

template<typename T>
T sum(T t)
{
	return t;
}

template <typename T,typename... Args>
T sum(T t,Args... args)
{
	return t+sum(args...);
}

void test2()
{
	int ret=sum(1,2,3,4);
	cout<<ret<<endl;
}

int main()
{
	test2()
		return 0;
}
