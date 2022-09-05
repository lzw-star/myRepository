#include<spider.h>

container_t * spider_create_container(int size)
{
	//定义变量
	container_t * ct = NULL;
	//申请容器
	ct = (container_t*)malloc(sizeof(container_t));
	//多少个url 就定义多少的空间
	ct->node_queue = (url_t *)malloc(size * sizeof(url_t));
	//初始化
	ct->front = 0;
	ct->rear = 0;
	ct->max  =size;
	ct->cur = 0;
	return ct;
}
	
