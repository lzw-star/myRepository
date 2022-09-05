#include<spider.h>

int spider_connect_webserver(int webfd,url_t * node)
{
	//连接浏览器
	struct sockaddr_in webserver;
	bzero(&webserver,sizeof(webserver));
	webserver.sin_family = AF_INET;
	inet_pton(AF_INET,node->ip,&webserver.sin_addr.s_addr);
	webserver.sin_port = htons(node->port);
	if(connect(webfd,(struct sockaddr*)&webserver,sizeof(webserver))==0)
	{
		printf("[3] 爬虫连接Web服务器 Host[%s] 成功...\n",node->domain);
	}
	return 0;
}
	
