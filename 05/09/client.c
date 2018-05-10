 ///
 /// @file    client.c
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-10 16:17:58
 ///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
	    do { \
			        perror(m);\
			        exit(EXIT_FAILURE);\
			    }while(0)

void do_service(int sockfd);

int main(int argc,const char **argv)
{
	int peerfd=socket(AF_INET,SOCK_STREAM,0);
	if(peerfd==-1)
	{
		ERR_EXIT("socket");
	}

	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(192.168.30.128);

	addr.sin_port=htos(9999);
	socklen_t len=sizeof(addr);
	if(connect(peerfd,(struct sockaddr*)&addr,len)==-1)
		ERR_EIT("Connect");
	

	char buf[1024];
	memset(buf,0,sizeof(buf));
	read(buf,0,sizeof(buf));
	printf("%s\n",buf);

	do_service(peerfd);

	return 0;
}

void do_service(int sockfd)
{
	char recvbuf[1024]={0};
	char sendbuf[1024]={0};

	while(1)
	{
		fgets(sendbuf,sizeof(send),stdin);
		write(sockfd,sendbuf,strlen(sendbuf));

		int nread=read(sockfd,recvbuf,sizeof(recvbuf));

		if(nread==-1)
		{
			if(errno==EINTR)
				continue;
			ERR_EXIT("read");
		}else if(0==nread){
			printf("server close!\n");
			close(sockfd);
			exit(EXIT_SUCCESS);
		}

		printf("receive msg:%\n",recvbuf);

		memset(recvbuf,0,sizeof(recvbuf));
		memset(sendbuf,0,sizeof(sendbuf));


	}
}
