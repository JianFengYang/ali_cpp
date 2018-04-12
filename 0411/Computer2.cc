 ///
 /// @file    Computer2.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-11 22:04:29
 ///
#include<string.h>

#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Computer
{
public:
	Computer(const char *brand,float price)
	: _brand(new char[strlen(brand)+1]())
	,_price(price)
	{
		strcpy(_brand,brand);
		cout<<"Computer(const char*,float)"<<
			endl;
	}
	void setBrand(const char* brand);
	void setPrice(float price);

	void print()
	{
		cout<<"品牌："<<_brand<<endl
		<<"价格："<<_price<<endl;
	}
	~Computer()
	{
		delete []_brand;
		cout<<"~Computer()"<<endl;
	}
private:
	char *_brand;
	float _price;
};
void Computer::setBrand(const char *brand)
{
	::strcpy(_brand,brand);
}
void Computer::setPrice(float price)
{
	_price=price;
}
int test0(void)
{
	return 0;
}

Computer com2("小米"，6666);
static Computer com3("Thinkpad",8888);

int main(void)
{
	Computer com("战神",9000);
	com.print();

	int *p=new int(1);

	Computer *pc=new Computer("Macbook",10000);
	pc->print();

	delete pc;
	delete p;

	return 0;

}
