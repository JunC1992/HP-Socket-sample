#include "WSServer.h"

CWSServerEngine g_WSEngine(HTTP_NAME);
CHttpServerPtr g_HttpServer(&g_WSEngine);

CWSServerDaemon::CWSServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){
	m_engine = std::make_shared<CWSServerEngine>(HTTP_NAME);
	m_server = std::make_shared<CHttpServerPtr>(m_engine.get());
};

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
