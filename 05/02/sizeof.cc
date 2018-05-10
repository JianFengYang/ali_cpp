 ///
 /// @file    sizeof.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-03 15:00:58
 ///
 
#include <iostream>
using std::cout;
using std::endl;
class E
{
public:E(int &ref)
	   :_ref(ref){}
private:
	   int &_ref;
	   static int _if;
	   int _ia;        // 4
		double _db;	    // 8
			char _carr[3]; 
};
int main(void)
{
	cout<<sizeof(E)<<endl;
}
