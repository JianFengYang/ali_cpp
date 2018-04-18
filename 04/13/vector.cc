 ///
 /// @file    vector.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-18 16:13:14
 ///
 
#include <iostream>
#include<vector>
using std::cout;
using std::endl;
using std::vector;

void printVectorCapacity(vector<int> &vec)
{
	cout<<"vec's size="<<vec.size()
		<<"vec's capacity="<<vec.capacity()<<endl;
}

int main(void)
{
	vector<int> numbers;
	cout<<"sizeof(numbers)"<<sizeof(numbers)<<endl;
	numbers.reserve(1000);

	printVectorCapacity(numbers);

	numbers.push_back(1);	
	printVectorCapacity(numbers);
	numbers.push_back(2);	
	printVectorCapacity(numbers);

	numbers.push_back(3);	
	printVectorCapacity(numbers);
	numbers.pop_back();

	cout<<"sizeof(numbers)="<<sizeof(numbers)<<endl;
	cout<<endl;
	//遍历方式
	
	for(size_t idx=0;idx!=numbers.size();++idx)
	{
		cout<<numbers[idx]<<" ";
	}
	cout<<endl;

	//c++遍历方式
	for(auto &number:numbers)
	{
		cout<<number<<" ";
	}
	cout<<endl;

	//迭代器（指针）
	vector<int>::iterator it;
	for(it=numbers.begin();it!=numbers.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;

	return 0;
}
