#include<spider.h>

int spider_container_getnode(container_t* ct,url_t * node)
{
	if(ct->cur == 0)
	{
		return -1; //没有元素 拿失败
	}
	*node = ct->node_queue[ct->rear];
	--ct->cur;
	ct->rear = (ct->rear+1) % ct->max;
	return 0;
}
