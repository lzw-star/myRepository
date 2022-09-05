#include<spider.h>

int spider_create_requestHead(char * request_head,url_t node)
{
	//请求头
	//初始化空间
	bzero(request_head,4096);
	//将请求头中的数据存放到request_head
	sprintf(request_head,"GET %s HTTP/1.1\r\n"\
			     "ACCEPT:text/html.application/xhtmk+xml,application/xml;q=0.9,image/webq;q=0.8\r\n"\
			     "User_Agent:Mozilla/5.0 (X11; Linux x86_64)\r\n"\
			     "Host:%s\r\n"\
			     "Connection:close\r\n\r\n",node.origin_url,node.domain);
	printf("[4] 请求头创建成功..\n%s",request_head);
}
	
