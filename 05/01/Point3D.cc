 ///
 /// @file    Point3D.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-01 12:36:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix=0,int iy=0)
	:_ix(ix)
	,_iy(iy)
	{
		cout<<"Point(int=0,int=0)"<<endl;
	
	
	}

	void print() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	int getY() const
	{
		return _iy;
	}

protected:
	int getX() const
	{
		return _ix;
	}

	int _ix;
private:
	int _iy;
};

class Point3D
:public Point
{
public:
	Point3D(int ix,int iy,int iz)
	:Point(ix,iy)
	,_iz(iz)
	{
		cout<<"Point3D(int,int ,int)"<<endl;
	}

	void display() const
	{
		cout<<"("<<_ix
			<<","<<getY()
			<<","<<_iz
			<<endl;
	}
private:
	int _iz;
};

int main(void)
{
	Point3D pt3d(1,2,3);
	pt3d.print();
	pt3d.getX();
	pt3d.getY();

	return 0;
}
