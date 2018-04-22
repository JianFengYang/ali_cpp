 ///
 /// @file    helloLog4Cpp.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 14:03:16
 ///
 
#include <iostream>
#include<log4cpp/Category.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/BasicLayout.hh>
#include<log4cpp/Priority.hh>

using std::cout;
using std::endl;

int main(int argc,char **argv)
{
	//创建一个Appender，指定所包含的Layout
	log4cpp::OstreamAppender *osAppender=new 
		log4cpp::OstreamAppender("osAppender",&cout);
	osAppender->setLayout(new log4cpp::BasicLayout());
//从系统得到Category的根，将Appender添加到该Category中
//并设置优先级
	log4cpp::Category &root=log4cpp::Category::getRoot();
	root.addAppender(osAppender);
	root.setPriority(log4cpp::Priority::DEBUG);
//记录日志
	root.error("Hello log4cpp error");
	root.warn("Hello log4cpp warning");
//关闭Category
	log4cpp::Category::shutdown();

	return 0;
}
