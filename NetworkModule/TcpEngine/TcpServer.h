#pragma once
#include <hpsocket/HPSocket.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "CListenerImpl.h"

/* Listener Class */
class CTcpServerDeamon {

public:
	CTcpServerDeamon()=default;
	CTcpServerDeamon(const char * ip, int port): m_ip(ip), m_port(port){};

	~CTcpServerDeamon()=default;
public:
	// start tcp server daemon
	bool Run();

	//TODO
	// stop tcp server daemon
	// void Stop();
	//
	// thread pool set
	// package parse
private:
	const char * m_ip;
	int m_port;
};

