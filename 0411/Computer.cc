 ///
 /// @file    Computer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-11 20:45:12
 ///
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;


class Computer
{
public:

	void setBrand(const char *brand)
	{
		::strcpy(_brand,brand);

	}
	void setPrice(float price)
	{
		_price=price;
	}
private:
	char _brand[20];
	float _price;
};

int main(void)
{
	Computer com;
	com.setBrand("macbook");
	com.setPrice(10000);

	return 0;
}
