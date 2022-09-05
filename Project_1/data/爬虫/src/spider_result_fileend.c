#include<spider.h>

int spider_result_fileend(int savefd)
{
	int endfd;
	//文件描述符
	endfd = open("fileend.html",O_RDONLY);
	//定义空间
	char endbuf[1024];
	//初始化
	bzero(endbuf,sizeof(endbuf));
	//定义变量
	int endlen;
	if((endlen = read(endfd,endbuf,sizeof(endbuf)))>0)
	{
		write(savefd,endbuf,strlen(endbuf));
	}
	return 0;
}

