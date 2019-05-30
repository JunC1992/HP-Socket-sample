#pragma once

#include "WSServerEngine.h"

// default serv_ip & serv_port
#define DEFAULT_HTTP_IP "127.0.0.1"
#define DEFAULT_HTTP_PORT 8080

class CWSServerDaemon{

public:
	CWSServerDaemon():CWSServerDaemon(DEFAULT_HTTP_IP, DEFAULT_HTTP_PORT){};
	CWSServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){};
	~CWSServerDaemon()=default;

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
