 ///
 /// @file    safeFile.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-30 16:00:58
 ///
#include<stdio.h>
#include<string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class SafeFile
{
public:
	SafeFile(FILE *fp)
	:_fp(fp)
	{
		cout<<"SafeFile(FILE*)"<<endl;
	}

	void write(const string &msg)
	{
		fwrite(msg.c_str(),msg.size(),1,_fp);
	}

	~SafeFile()
	{
		if(_fp)
		{
			fclose(_fp);
		}
		cout<<"SafeFile()"<<endl;

	}

private:
	FILE *_fp;

};
int main(void)
{
	SafeFile sf(fopen("test.txt","w+"));
	sf.write("hello,world\n");

	return 0;
}
