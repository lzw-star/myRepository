#include<spider.h>

int main()
{
	//char * URL = "http://c-ssl.duitang.com/uploads/blog/202106/14/20210614060633_74f83.jpeg";
	//char * URL = "https://chuangshi.qq.com/bk/ds/41680176.html";
	//char * URL = "https://baike.baidu.com/item/%E9%87%8F%E5%AD%90%E8%AE%A1%E7%AE%97%E6%9C%BA";

	//未处理和已处理容器初始化
	container_t * u_ct = spider_create_container(1000);
	container_t * p_ct = spider_create_container(100000);
	ssl_t * ssl = NULL;
	char request_head[4096];
	int webfd;
	int htmlfd;
	//1. 选择种子url
	//深度学习百度百科
	//char * URL = "https://baike.baidu.com/item/%E6%B7%B1%E5%BA%A6%E5%AD%A6%E4%B9%A0/3729729";
	//卷积神经网络
	//char * URL = "https://baike.baidu.com/item/%E5%8D%B7%E7%A7%AF%E7%A5%9E%E7%BB%8F%E7%BD%91%E7%BB%9C";
	char * URL = "https://baike.baidu.com/item/%E5%8D%B7%E7%A7%AF%E5%B1%82";
	//char * URL = "https://baijiahao.baidu.com/s?id=1700267963266515446&wfr=spider&for=pc";
	//2. 种子url去重 添加到未处理容器
	url_t node;
	//拿出
	url_t tmpnode;
	strcpy(node.origin_url,URL);
	if(spider_remove_duplication(u_ct,p_ct,URL))
	{
		spider_container_setnode(u_ct,&node);
	}
	//将爬取内容写入文件
	int savefd;
	savefd = open("result_files.html",O_RDWR);
	spider_result_filehead(savefd);
	//循环范围拿取
	while(u_ct->cur >0 && p_ct->cur <100000)
	{
		spider_container_getnode(u_ct,&tmpnode);
		webfd = spider_net_init();
		spider_analytical_url(&tmpnode);
		spider_connect_webserver(webfd,&tmpnode);
		spider_create_requestHead(request_head,tmpnode);
		//如果https协议 进行安全认证
		if(tmpnode.http_type)
		{
			ssl = spider_openssl_init(webfd);
		}
		if((spider_download(webfd,request_head,tmpnode,ssl))==-1)
		{
			continue;
		}
		//下载完毕 将node存入到已处理容器
		spider_container_setnode(p_ct,&tmpnode);
		//解析html
		spider_analytical_html(savefd,&tmpnode,u_ct,p_ct);
		
	//	spider_result_fileend(savefd);
		//spider_controler("https://baike.baidu.com/item/%E9%87%8F%E5%AD%90%E8%AE%A1%E7%AE%97%E6%9C%BA");
	}
	spider_result_fileend(savefd);
	return 0;
}


