#include "HttpServer.h"

CHttpServerDaemon::CHttpServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){
	m_engine = std::make_shared<CHttpServerEngine>(HTTP_NAME);
	m_server = std::make_shared<CHttpServerPtr>(m_engine.get());
}

bool CHttpServerDaemon::Init(){
	// TODO
	// init http server engine
	m_engine->Init();
	return true;
}

bool CHttpServerDaemon::Start(){
	// start http server daemon
	Init();
	SetHandleFactory();
	//if(g_HttpServer->Start(m_ip, m_port)) {
	if((*m_server)->Start(m_ip, m_port)) {
		// TODO
		// log launch error
		return false;
	}
	return true;
}

bool CHttpServerDaemon::Stop(){
	// stop http server daemon
	(*m_server)->Stop();
	return true;
}

bool CHttpServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	CHttpHandler::SetHttpHandle();
	return true;
}
