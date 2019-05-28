#pragma once
#include <iostream>
#include <hpsocket/HPSocket.h>

#include "TcpServerEngine.h"

// default serv_ip & serv_port
#define DEFAULT_TCP_IP "127.0.0.1"
#define DEFAULT_TCP_PORT 8081

/* Listener Class */
class CTcpServerDaemon {

public:
	CTcpServerDaemon():CTcpServerDaemon(DEFAULT_TCP_IP, DEFAULT_TCP_PORT){};
	CTcpServerDaemon(const char* ip, const int port): m_ip(ip), m_port(port){};
	~CTcpServerDaemon()=default;

public:
	// init tcp daemon
	bool Init(int threads);
	// start tcp server daemon
	bool Start();

	// register handler
	bool SetHandleFactory();

	//TODO
	// stop tcp server daemon
	// void Stop();
	//
	// thread pool set
	// package parse
private:
	const char* m_ip;
	const int m_port;
};
