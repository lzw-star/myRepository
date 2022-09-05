#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h> //网络
#include<arpa/inet.h>  //大小端转换
#include<ctype.h>
#include<netdb.h>      //DNS域名解析函数
#include<regex.h>      //正则
#include<openssl/ssl.h>
#include<openssl/err.h>
#include<sys/mman.h>

int data_fd;
//1. 解析url后将详细信息存储在url_t中 定义结构体，只有原始url有值，其它都为空
typedef struct
{
	char origin_url[4096]; 		//存储原始url  http://......
	int  http_type;	       		//传输类型 0:http,1:https
	char domain[1024];     		//存储域名
	char path[1024];       		//存储路径
	char filename[1024];		//目标文件名
	char ip[16];			//ip
	int port;			//port
}url_t;
//用于https进行安全验证
typedef struct
{
	SSL * ssl_socket;
	SSL_CTX * ssl_ctx;
}ssl_t;
//结构体 用于容器的添加和取出
typedef struct
{
	url_t * node_queue; //url的结构体内容
	int front; //容器开始url
	int rear;//容器末尾url
	int max; //容器能容纳最大url个数
	int cur; //当前容器中url个数
}container_t;

//爬虫下载器函数
int spider_net_init();			//爬虫网络初始化
int spider_analytical_url(url_t *);	//解析函数，传入解析原始url，传出完整的结构体
int spider_connect_webserver(int ,url_t *);	//连接web服务器
int spider_create_requestHead(char *,url_t);    //传入数组地址，传出请求头
int spider_download(int ,char *, url_t,ssl_t*);	//发送连接请求给Web服务器
int spider_get_status_code(char *);		//传入响应头，获取状态码
ssl_t * spider_openssl_init(int);			//安全认证

//容器和去重和html解析
//容器创建初始化 参数为个数
container_t* spider_create_container(int);
//url去重 与未处理容器和已处理容器进行查重,传入的是url
int spider_remove_duplication(container_t*,container_t*,const char*);
//向容器添加节点(添加的是url解析html经过去重校验后的url)
int spider_container_setnode(container_t*,url_t *);
//从容器拿出节点(按顺序拿出url)
int spider_container_getnode(container_t*,url_t *);
//url解析获得到的html资源 并分成url(需要经过去重，不重复放到容器中)和内容(标题和介绍)
int spider_analytical_html(int ,url_t *,container_t*,container_t*);
//保存解析后的内容进行持久化 内容包括标题 介绍 链接
int spider_save_data(const char*,const char*,const char*);
//控制器 种子URL
int spider_controler(const char * origin_url);
//写内容到html
int spider_result_filehead(int);
int spider_result_filemid(int,char*,char*,char*);
int spider_result_fileend(int);
