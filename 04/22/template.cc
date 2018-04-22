 ///
 /// @file    template.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 12:59:02
 ///
 
#include <iostream>
using std::cout;
using std::endl;

template <typename T,int number>
T add(T x,T y)
{
	return x*y*number;
}

int main(void)
{
	int a=10,b=3;
	cout<<add<int,4>(a,b)<<endl;

	return 0;
}
