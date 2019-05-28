#include "HttpServer.h"

#define HTTP_NAME "http"

CHttpServerListenerImpl g_HttpEngine(HTTP_NAME);
CHttpServerPtr g_HttpServer(&g_HttpEngine);

bool CHttpServerDaemon::Init(){
	// TODO
	// init http server engine
	g_HttpEngine.Init();
	return true;
}

bool CHttpServerDaemon::Start(){
	// start http server daemon
	Init();
	SetHandleFactory();
	if(g_HttpServer->Start(m_ip, m_port)) {
		// TODO
		// log launch error
		return false;
	}
	return true;
}

bool CHttpServerDaemon::Stop(){
	// stop http server daemon
	g_HttpServer->Stop();
	return true;
}

bool CHttpServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	HttpHandler::SetHttpHandle();
	return true;
}
