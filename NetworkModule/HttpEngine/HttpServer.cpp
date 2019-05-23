#include "HttpServer.h"

#define HTTP_NAME "http"

CHttpServerListenerImpl g_listener(HTTP_NAME);
CHttpServerPtr g_http_server(&g_listener);

bool CHttpServerDaemon::Init(){
	// TODO
	// init http server daemon 
	return true;
}

bool CHttpServerDaemon::Start(){
	// start http server daemon
	Init();
	SetHandleFactory();
	if(g_http_server->Start(m_ip, m_port)) {
		// TODO
		// log launch error
		return false;
	}
	return true;
}

bool CHttpServerDaemon::Stop(){
	// stop http server daemon
	g_http_server->Stop();
	return true;
}

bool CHttpServerDaemon::SetHandleFactory(){
	// TODO
	// register http server daemon handle 
	//
	HttpHandler::SetHttpHandle();
	return true;
}
