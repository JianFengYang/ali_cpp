 ///
 /// @file    LayoutExam.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 14:22:15
 ///
 
#include <iostream>
#include<log4cpp/Category.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/PatternLayout.hh>
using std::cout;
using std::endl;

int main(int argc,char **argv)
{
	log4cpp::OstreamAppender *osAppender=new
		log4cpp::OstreamAppender("osAppender",&cout);

	log4cpp::PatternLayout *pLayout=new log4cpp::PatternLayout();
	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	osAppender->setLayout(pLayout);

	log4cpp::Category &root=log4cpp::Category::getRoot();
	log4cpp::Category &infoCategory=root.getInstance("infoCategory");
	infoCategory.addAppender(osAppender);
	infoCategory.setPriority(log4cpp::Priority::INFO);

	infoCategory.info("system is running");
	infoCategory.warn("system has a waring");
	infoCategory.error("system has a error");
	infoCategory.fatal("fatal error shutdown");
	infoCategory.info("find some infomation in system log");

	log4cpp::Category::shutdown();

	return 0;
}
