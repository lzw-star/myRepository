#include<spider.h>

int spider_result_filemid(int savefd,char *h1,char* d1,char *l1)
{
	int midfd;
	//文件描述符
	midfd = open("filemid.html",O_RDONLY);
	//定义空间
	//char midbuf[1024];
	//初始化
	//bzero(midbuf,sizeof(midbuf));
	//定义变量
	int midlen;
	char str[4096];
	bzero(str,sizeof(str));
	strcat(str,"<tr>\
                <td>");
	strcat(str,h1);
	strcat(str,  "</td>\
                <td>");
	strcat(str,d1);
	strcat(str,  "</td>\
                <td><a href=");
	strcat(str,l1);
	strcat(str,">");
	strcat(str,l1);
	char str4[] ="</a></td>\
        </tr>";
	strcat(str,str4);
	//if((midlen = read(midfd,midbuf,sizeof(midbuf)))>0)
	//{
	//printf("midlen ===============%d\n",midbuf);

	if((midlen = write(savefd,str,strlen(str)))>0)
	{
		printf("存储成功..\n");
	}
	else
	{
		printf("存储失败..\n");
	}
	
}

