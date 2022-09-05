#include<spider.h>

int spider_analytical_html(int savefd,url_t * node,container_t * u_ct,container_t * p_ct)
{
	int fd;
	int filesize;
	char * string = NULL;
	char * jstring = NULL;
	url_t tmpnode;
	//1. 打开百科词条网页源码
	fd = open(node->filename,O_RDONLY);
	filesize = lseek(fd,0,SEEK_END);
	//2. 对网页源码进行私有映射
	string = mmap(NULL,filesize,PROT_READ,MAP_PRIVATE,fd,0);
	jstring = string;
	close(fd);
	//3. 创建正则语句(匹配主标题 词条描述 匹配更多词条链接)
	regex_t hreg,dreg,lreg;
	regmatch_t hmatch[2];
	regmatch_t dmatch[2];
	regmatch_t lmatch[2];
	//1). 标题		<h1>词条标题</h1>
	regcomp(&hreg,"<h1[^>]\\+\\?>\\([^<]\\+\\?\\)</h1>",0);
	//2). 介绍		<meta name="description" content="词条描述">
	regcomp(&dreg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">",0);
	//3). 匹配更多链接	<a 特殊字段A href="/item/词条链接" 特殊字段B>超链接标题</a>
	regcomp(&lreg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>",0);
	//**注意事项：匹配到新链接后，要对其进行拼接标准前缀 https://baike.baidu.com

	//4. 描述与主标题与本词条链接进行持久化存储(数据库or磁盘)
	//4.1 定义持久化存放空间
	char h1[1024];
	char d1[4096];
	char l1[8192];
	//4.2 空间初始化
	bzero(h1,sizeof(h1));
	bzero(d1,sizeof(d1));
	bzero(l1,sizeof(l1));
	//4.3 执行匹配
	if((regexec(&hreg,string,2,hmatch,0))==0)
		snprintf(h1,hmatch[1].rm_eo-hmatch[1].rm_so+1,"%s",string+hmatch[1].rm_so);
	printf("[Analytical HTML] 解析的词条标题 [%s]\n",h1);
	if((regexec(&dreg,string,2,dmatch,0))==0)
		snprintf(d1,dmatch[1].rm_eo-dmatch[1].rm_so+1,"%s",string+dmatch[1].rm_so);
	printf("[Analytical HTML] 解析的描述 [%s]\n",d1);
	printf("[URL] 本词条的URL链接 [%s]\n",node->origin_url);

	char * htmlh1 = h1;
	char * htmld1 = d1;
	char * htmll1 = node->origin_url;
	//添加词条信息到html文件中
	spider_result_filemid(savefd,htmlh1,htmld1,htmll1);
	//未处理容器小于200 才解析
	if(u_ct->cur <= 200)
	{
		while((regexec(&lreg,string,2,lmatch,0))==0)
		{
			//**注意事项：匹配到新链接后，要对其进行拼接标准前缀 https://baike.baidu.com
			snprintf(l1,lmatch[1].rm_eo-lmatch[1].rm_so+24,"https://baike.baidu.com%s",string+lmatch[1].rm_so);
			printf("[Analytical HTML] 解析的词条新链接 [%s]\n",l1);
			//5.将解析后的新链接进行去重
			if(spider_remove_duplication(u_ct,p_ct,l1))
			{
				//不重复
				strcpy(tmpnode.origin_url,l1);
				if((strstr(tmpnode.origin_url,"秒懂"))==NULL)
					spider_container_setnode(u_ct,&tmpnode);
			}
			bzero(l1,sizeof(l1));
			//防止一直循环第一条，利用jstring进行string偏移
			string += lmatch[0].rm_eo;
		}
	}
	//内容处理完毕 删除源文件
	unlink(node->filename);
	//6. 分析出的更多新词条连接去重加入到未处理容器中
	regfree(&hreg);
	regfree(&dreg);
	regfree(&lreg);
	munmap(jstring,filesize);
	return 0;
}
