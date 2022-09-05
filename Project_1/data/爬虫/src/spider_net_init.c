#include<spider.h>

int spider_net_init()
{
	//"https://c-ssl.duitang.com/uploads/blog/202106/14/20210614060633_74f83.jpeg"
	//初始化网络
	int sockfd;
	/*
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8080);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	printf("[1] 爬虫网络初始化成功..\n");
	return sockfd;
}
	
