#include<spider.h>

int spider_download(int sockfd,char * request_head,url_t node,ssl_t * ssl)
{
	//通过请求头，获取响应头和响应体
	//定义存储响应头空间
	char response_head[4096];
	//定义存储响应体空间
	char recv_buffer[8192];
	//初始化
	bzero(response_head,4096);
	bzero(recv_buffer,8192);
	//定义变量
	int sendsize;
	int recvsize;
	int fd;
	//指针
	char * pos = NULL;
	if(!ssl)
	{
		//发送请求头给Web服务器
		if((sendsize = send(sockfd,request_head,strlen(request_head),0))>0)
		{
			printf("[5] 发送请求头到Web服务器成功..\n");
		}
		//判断是否接收到响应
		if((recvsize = recv(sockfd,recv_buffer,sizeof(recv_buffer),0))<=0)
		{
			printf("FAILED：接收Web服务器响应失败..\n");
			exit(-1);
		}
		//接收响应，提取响应头
		//判断是否存在子字符串 参数1:输入字符串，参数2:子字符串 返回子字符串的首地址
		if((pos = strstr(recv_buffer,"\r\n\r\n"))==NULL)
		{
			printf("接收响应头失败...\n");
			exit(-1);
		}
		//存在子字符串,提取响应头
		//snprintf 参数1：存储空间，参数2：存储长度，参数3：存储格式，参数4：存储内容
		snprintf(response_head,pos - recv_buffer+4,"%s",recv_buffer);
		printf("[6] 接收响应头成功,为:\n%s",response_head);

		//获取响应码
		int code;
		if((code = spider_get_status_code(response_head)) == 200)
		{
			printf("[7] 获取statuscode[%d] 获取响应体成功\n",code);
			//将目标图像存放
			fd = open(node.filename,O_RDWR|O_CREAT,0775);
			write(fd,pos+4,recvsize-(pos-recv_buffer+4));
			//有值循环读取
			while((recvsize = recv(sockfd,recv_buffer,sizeof(recv_buffer),0))>0)
			{
				write(fd,recv_buffer,recvsize);
				bzero(recv_buffer,recvsize);
			}
			close(fd);
			printf("[8] 交互完毕 下载[%s]成功\n",node.filename);
		}
		else
		{
			printf("获取statuscode[%d] 获取响应体失败\n",code);
			close(sockfd);
			return -1;
		}
		close(sockfd);
		return 0;
	}
	else
	{
		//发送请求头给Web服务器
		if((sendsize = SSL_write(ssl->ssl_socket,request_head,strlen(request_head)))>0)
		{
			printf("[5] 发送请求头到Web服务器成功..\n");
		}
		//判断是否接收到响应
		if((recvsize = SSL_read(ssl->ssl_socket,recv_buffer,sizeof(recv_buffer)))<=0)
		{
			printf("FAILED：<HTTPS> 接收Web服务器响应失败..\n");
			exit(-1);
		}
		//接收响应，提取响应头
		//判断是否存在子字符串 参数1:输入字符串，参数2:子字符串 返回子字符串的首地址
		if((pos = strstr(recv_buffer,"\r\n\r\n"))==NULL)
		{
			printf("<HTTPS> 接收响应头失败...\n");
			exit(-1);
		}
		//存在子字符串,提取响应头
		//snprintf 参数1：存储空间，参数2：存储长度，参数3：存储格式，参数4：存储内容
		snprintf(response_head,pos - recv_buffer+4,"%s",recv_buffer);
		printf("[6] <HTTPS> 接收响应头成功,为:\n%s",response_head);

		//获取响应码
		int code;
		if((code = spider_get_status_code(response_head)) == 200)
		{
			printf("[7] <HTTPS> 获取statuscode[%d] 获取响应体成功\n",code);
			//将目标图像存放
			fd = open(node.filename,O_RDWR|O_CREAT,0775);
			write(fd,pos+4,recvsize-(pos-recv_buffer+4));
			//有值循环读取
			while((recvsize = SSL_read(ssl->ssl_socket,recv_buffer,sizeof(recv_buffer)))>0)
			{
				write(fd,recv_buffer,recvsize);
				bzero(recv_buffer,recvsize);
			}
			close(fd);
			printf("[8] <HTTPS> 交互完毕 下载[%s]成功\n",node.filename);
		}
		else
		{
			printf("<HTTPS> 获取statuscode[%d] 获取响应体失败\n",code);
			free(ssl);
			ssl = NULL;
			close(sockfd);
			return -1;
		}
	}
	free(ssl);
	ssl = NULL;
	close(sockfd);
	return 0;
}

