#include "CHttpServerListenerImpl.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 80

class CHttpServerDaemon{

public:
	CHttpServerDaemon():CHttpServerDaemon(DEFAULT_IP, DEFAULT_PORT){};
	CHttpServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){};
	~CHttpServerDaemon()=default;

public:
	bool Init();
	bool Start();
	bool Stop();
	bool SetHandleFactory();

private:
	const char* m_ip;
	const int m_port;
};
