 ///
 /// @file    reference.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-10 22:52:35
 ///
 
#include <iostream>
using std::cout;
using std::endl;
void swap(int  *px,int *py)
{
	int temp=*px;
	*px=*py;
	*py=temp;
}
void swap(int &x ,int &)
{
	int temp=x;
	x=y;
	y=temp;
}

