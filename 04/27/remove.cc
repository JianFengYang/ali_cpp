 ///
 /// @file    remove.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-27 19:31:2> 
#include <iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using std::cout;
using std::endl;
using std::vector;
using std::remove;

void test(void)
{
	vector<int>numbers{1,2,3,4,5,6,7,8,9,10};
	numbers[3]=numbers[6]=numbers[8]=66;

	numbers.erase(remove(numbers.begin(),numbers.end(),
				66),numbers.end());
	copy(numbers.begin(),numbers.end(),
			std::ostream_iterator<int>(cout,","));
	cout<<endl;
}
int main(void)
{
	test();
	return 0;
}

