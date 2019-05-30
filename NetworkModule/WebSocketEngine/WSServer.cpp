#include "WSServer.h"

#define HTTP_NAME "http"

CWSServerListenerImpl g_WSEngine(HTTP_NAME);
CHttpServerPtr g_HttpServer(&g_WSEngine);

bool CWSServerDaemon::Init(){
	// TODO
	// init http server engine
	g_WSEngine.Init();
	return true;
}

bool CWSServerDaemon::Start(){
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

bool CWSServerDaemon::Stop(){
	// stop http server daemon
	g_HttpServer->Stop();
	return true;
}

bool CWSServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	CWSHandler::SetHttpHandle();
	return true;
}
