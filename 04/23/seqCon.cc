 ///
 /// @file    seqCon.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-23 20:33:08
 ///
 
#include <iostream>
#include<vector>
#include<list>
#include<deque>

using std::cout;
using std::endl;
using std::deque;
using std::list;
using std::vector;

int test0(void)
{
	int arr[5]={10,11,12,13,14};

	vector<int> vecInt{1,2,3,4};
	cout<<"vector:"<<endl;
	for(auto &number:vecInt)
	{
		cout<<number<<" ";
	}
	cout<<endl;

	cout<<vecInt[3]<<endl;
	auto it=vecInt.begin();
	++it;

	cout<<"vecInt'size="<<vecInt.size()<<endl;
	cout<<"capacity="<<vecInt.capacity()<<endl;
	vecInt.insert(it,3,5);
	it=vecInt.begin();
	_++it;
	cout<
}

int main(void)
{
	test0();
	return 0;
}
