#include<spider.h>

int spider_container_setnode(container_t *ct,url_t * node)
{
	//当前个数为所能添加的最大个数
	if(ct->max == ct->cur)
	{
		return -1; //添加失败
	}
	ct->node_queue[ct->front] = *node;
	++ct->cur;
	ct->front = (ct->front+1) % ct->max;
	return 0;
}
