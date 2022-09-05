#include<spider.h>

int spider_remove_duplication(container_t* u_ct,container_t* p_ct,const char * url)
{
	int flag = u_ct->rear;
	/*
	printf("未处理容器尾位置:[%d]\n",u_ct->rear);
	printf("未处理容器头位置:[%d]\n",u_ct->front);
	printf("已处理容器尾位置:[%d]\n",p_ct->rear);
	printf("已处理容器头位置:[%d]\n",p_ct->front);
	*/
	//从尾向头遍历u_ct 尾是先入的url 拿时先拿尾
	while(flag % u_ct->max != u_ct->front)
	{
		//相等
		if(strncmp(u_ct->node_queue[flag].origin_url,url,strlen(url))==0)
		{
			/*
			printf("u_ct去重开始,去重链接为:[%s]\n",url);
			printf("u_ct去重开始,已存在链接为:[%s] 位置[%d]\n",u_ct->node_queue[flag].origin_url,flag);
			*/
			return 0;
		}
		flag++;
	}
	flag = p_ct->rear;
	//从尾向头遍历p_ct 尾是先入的url 拿时先拿尾
	while(flag % p_ct->max != p_ct->front)
	{
		//相等
		if(strncmp(p_ct->node_queue[flag].origin_url,url,strlen(url))==0)
		{
			//printf("p_ct中去重开始..............................\n");
			return -1;
		}
		flag++;
	}
	return 1;
}
