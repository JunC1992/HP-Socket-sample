#pragma once
#include <hpsocket/HPSocket.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "TcpServerEngine.h"

/* Listener Class */
class CTcpServerDeamon {

public:
	CTcpServerDeamon()=default;
	CTcpServerDeamon(const char * ip, const int port): m_ip(ip), m_port(port){};

	~CTcpServerDeamon()=default;
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
	const char * m_ip;
	const int m_port;
};

