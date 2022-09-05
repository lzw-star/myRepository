#include<spider.h>

int spider_controler(const char * origin_url)
{
	//临时节点传入u_ct
	url_t temp;
	//传出的url从u_ct
	url_t node;
	//安全认证
	ssl_t * ssl = NULL;
	data_fd = open("resdate",O_RDWR|O_CREAT,0664); //创建存储文件
	//请求头
	char * request[4096];
	//辨别类型
	ssl_t * ssl = NULL;
	//存储标题 介绍 链接
	char title[4096];
	char introduce[4096];
	char url[4096];
	//拷贝种子url
	strcpy(temp.origin_url,origin_url);
	//创建容器
	container_t * u_ct = spider_create_container(1000);  //未处理容器
	container_t * p_ct = spider_create_container(100000); //已处理容器
	//种子url添加去重 重复返回-1 不重复返回0 
	if((spider_remove_duplication(u_ct,p_ct,temp.origin_url))!=-1)
	{
		spider_container_setnode(u_ct,&temp); //添加种子url
	}
	//爬虫持续 当前爬虫数量不为0
	while((u_ct->cur != 0))
	{
		//创建一次性链接socket
		int webfd = spider_net_init();
		//传出一个url
		spider_container_getnode(u_ct,&node);
		//进行url解析
		spider_analytical_url(&node);
		//链接web服务器
		spider_connect_webserver(webfd,&node);
		//创建请求头
		spider_create_requestHead(request,node);
		//辨别http
		if(http_type)
		{
			ssl = spider_openssl_init(webfd);
		}
		//判断是否下载成功
		if((spider_download(webfd,request,node,ssl))==-1)
		{
			continue; //下载失败结束本次处理
		}
		//下载成功放到已处理容器
		spider_container_setnode(p_ct,&node);
		//解析网页源码(解析更多链接)
		spider_analytical_html(&node,u_ct,p_ct);
		//保存内容
		spider_save_data(title,introduce,url);
	}
	close(webfd);
	return 0;
}	
