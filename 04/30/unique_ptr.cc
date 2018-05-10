///

/// @file    auto_ptr.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-04-30 21:22:18
///
#include<memory>
#include <iostream>
#include<vector>
using std::cout;
using std::endl;
using std::auto_ptr;
using std::vector;
using std::unique_ptr;
class Point
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

unique_ptr<Point> getPoint()
{
	unique_ptr<Point>up(new Point(5,6));
	return up;
}
int main(void)
{
	unique_ptr<Point> up(new Point(1,2));
	cout<<"*up="<<*up<<endl;
	cout<<"up'get="<<up.get()<<endl;

	unique_ptr<Point> up3(new Point(3,4));
	cout<<"*up3="<<*up3<<endl;
	up3=getPoint();
	cout<<"*up3"<<*up3<<endl;

	vector<unique_ptr<Point>> points;
	points.push_back(std::move(up));
	points.push_back(std::move(up3));

	up.reset(new Point(10,11));
	cout<<"*up="<<*up<<endl;
	return 0;
	
}
