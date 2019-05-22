#include "HttpServer.h"

#define HTTP_NAME "http"

CHttpServerListenerImpl g_listener(HTTP_NAME);
CHttpServerPtr g_http_server(&g_listener);

bool CHttpServerDaemon::Init(){return true;}

bool CHttpServerDaemon::Start(){
	if(g_http_server->Start(m_ip, m_port)) {
		// log error
		return false;
	}
	return true;
}

bool CHttpServerDaemon::Stop(){return true;}

//bool CHttpServerDaemon::SetHandleFactory(){return true;}
