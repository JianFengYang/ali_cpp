 ///
 /// @file    test.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-27 21:03:36
 ///
#include<algorithm> 
#include<string>

#include<vector>
#include<numeric>
#include <iostream>
#include<list>
using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::list;
void test0(void)
{

	vector<int> numbers{1,2,3,4,5,6,7,8,9,0};
	int sum=accumulate(numbers.cbegin(),numbers.cend(),0);
	cout<<"sum="<<sum<<endl;
}
void test1(void)
{
	vector<string>vec{"hello","world","i am ","friends"};
	string sum=accumulate(vec.cbegin(),vec.cend(),string(""));
	cout<<sum<<endl;
}
void test2()
{
	
	vector<string>vec{"hello","world","i am ","friends"};
	list<string>list{"hello","world","i am ","friends"};
	bool a=equal(vec.cbegin(),vec.cend(),list.cbegin());
	cout<<a<<endl;
}
int main()
{
	test2();
	return 0;
}

