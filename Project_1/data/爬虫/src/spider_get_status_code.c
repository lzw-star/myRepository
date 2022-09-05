#include<spider.h>

int spider_get_status_code(char *response_head)
{
	//获取响应码 HTTP/1.1 200 OK
	//定义变量
	int code;
	//存储状态码
	char status_code[100];
	bzero(status_code,100);
	//使用正则
	regex_t reg;
	regmatch_t match[2];
	//使用正则 \r\n代表空格  \r\n\r\n代表空行 +?非贪婪模式
	regcomp(&reg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n",0);
	if((code = regexec(&reg,response_head,2,match,0))==0)
	{
		//将状态码保存到status_code中
		snprintf(status_code,match[1].rm_eo-match[1].rm_so+1,"%s",response_head+match[1].rm_so);
		//将格式转换 由字符串转换为整型,
		//参数1：要转换的内容 参数2：要转换的格式 参数3：返回值
		sscanf(status_code,"%d",&code);
		regfree(&reg);
		return code;
	}
	regfree(&reg);
	return -1;
}
	
