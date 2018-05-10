///

/// @file    auto_ptr.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-04-30 21:22:18
///
#include<memory>
#include <iostream>
using std::cout;
using std::endl;
using std::auto_ptr;
ass Point
{
	public:
		Point(int ix = 0, int iy = 0)
			: _ix(ix)
			  , _iy(iy)
	{	cout << "Point(int,int)" << endl;	}

		void display() const{
			cout << "(" << _ix
				<< "," << _iy
				<< ")" << endl;
		}

		~Point(){	cout << "~Point()" << endl;}

		friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
	private:
		int _ix;
		int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
		<< "," << rhs._iy
		<< ")";
	return os;
}
int main(void)
{
	auto_ptr<Point> ap(new Point(1,2));
	
}
