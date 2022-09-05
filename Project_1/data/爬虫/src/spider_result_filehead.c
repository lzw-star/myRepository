#include<spider.h>
int spider_result_filehead(int savefd)
{
	int headfd;
	//文件描述符
	headfd = open("filehead.html",O_RDONLY);
	//定义空间
	char headbuf[1024];
	//初始化
	bzero(headbuf,sizeof(headbuf));
	//定义变量
	int headlen;
	if((headlen = read(headfd,headbuf,sizeof(headbuf)))>0)
	{
		write(savefd,headbuf,strlen(headbuf));
	}
	return 0;
}

