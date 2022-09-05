#include<spider.h>

ssl_t * spider_openssl_init(int webfd)
{
	//申请空间
	ssl_t * ssl = (ssl_t*)malloc(sizeof(ssl_t));
	//加载初始化ss错误处理函数
	SSL_load_error_strings();
	//初始化openssl库函数
	SSL_library_init();
	//初始化算法模块
	OpenSSL_add_ssl_algorithms();
	
	//先创建上下文信息
	ssl->ssl_ctx = SSL_CTX_new(SSLv23_method());
	//创建套接字
	ssl->ssl_socket = SSL_new(ssl->ssl_ctx);
	//使用webfd对sslsocket进行信息设置
	SSL_set_fd(ssl->ssl_socket,webfd);
	//通过sslsocket与webserver安全认证
	SSL_connect(ssl->ssl_socket);
	return ssl;
}
	
