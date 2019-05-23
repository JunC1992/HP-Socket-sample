#pragma once

#include "HttpServerEngine.h"

// default serv_ip & serv_port
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 8080

class CHttpServerDaemon{

public:
	CHttpServerDaemon():CHttpServerDaemon(DEFAULT_IP, DEFAULT_PORT){};
	CHttpServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){};
	~CHttpServerDaemon()=default;

public:
	// http server daemon init
	bool Init();
	// http server daemon start
	bool Start();
	// http server daemon stop
	bool Stop();
	// http server daemon handle registed
	bool SetHandleFactory();

private:
	const char* m_ip;
	const int m_port;
};
