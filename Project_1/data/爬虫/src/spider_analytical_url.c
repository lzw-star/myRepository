#include<spider.h>

int spider_analytical_url(url_t * node)
{
	//"https://c-ssl.duitang.com/uploads/blog/202106/14/20210614060633_74f83.jpeg"
	//变量的起始空间位置
	int j = 0;
	//保存长度
	int length;
	//起始位置
	int flags;
	//目标名大小
	int filesize = 0;
	//定义传输类型结构体
	const char * http_array[3] = {"http://","https://",NULL};
	//初始化
	bzero(node->domain,sizeof(node->domain));
	bzero(node->path,sizeof(node->path));
	bzero(node->filename,sizeof(node->filename));
	bzero(node->ip,sizeof(node->ip));
	//1. 判断传输类型
	if(strncmp(node->origin_url,http_array[0],strlen(http_array[0]))==0)
	{
		//如果是http类型
		node->http_type = 0;
		//端口号
		node->port = 80;
		//协议长度
		length = strlen(http_array[0]);
	}
	else
	{
		//如果是http类型
		node->http_type = 1;
		//端口号
		node->port = 443;
		//协议长度
		length = strlen(http_array[1]);
	}
	//2. 域名
	for(flags = length;node->origin_url[flags] != '/' && node->origin_url[flags] != '\0' ;flags++)
	{
		node->domain[j] = node->origin_url[flags];
		j++;
	}
	//3. 目标名 
	j = 0;
	for(flags = strlen(node->origin_url)-1;node->origin_url[flags] != '/';flags--,filesize++);
	int namesize = filesize-1;
	int f = strlen(node->origin_url)-1;
	for(namesize;namesize>=0;namesize--)
	{
		node->filename[namesize] = node->origin_url[f];
		f--;
		//j++;
	}
	//4. 路径
	j = 0;
	for(flags = length+strlen(node->domain);flags <strlen(node->origin_url)-filesize;flags++)
	{
		
		node->path[j] = node->origin_url[flags];
		j++;
	}
	//5. ip
	//获取网站公网ip并以字符串的格式存储
	struct hostent * ent = NULL;
	if((ent = gethostbyname(node->domain))!=NULL)
	{
		inet_ntop(AF_INET,ent->h_addr_list[0],node->ip,16);
		printf("[2] 爬虫URL解析成功 ORIGIN[%s] DOMAIN[%s] PATH[%s] FILENAME[%s] IP[%s] TYPE[%d] PORT[%d]\n",node->origin_url,node->domain,node->path,node->filename,node->ip,node->http_type,node->port);
	}
	return 0;
}
