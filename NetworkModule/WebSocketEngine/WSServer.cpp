#include "WSServer.h"

CWSServerDaemon::CWSServerDaemon(const char* ip, const int port):m_ip(ip), m_port(port){
	m_engine = std::make_shared<CWSServerEngine>(HTTP_NAME);
	m_server = std::make_shared<CHttpServerPtr>(m_engine.get());
};

bool CWSServerDaemon::Init(){
	// TODO
	// init http server engine
	m_engine->Init();
	return true;
}

bool CWSServerDaemon::Start(){
	// start http server daemon
	Init();
	SetHandleFactory();
	if((*m_server)->Start(m_ip, m_port)) {
		// TODO
		// log launch error
		return false;
	}
	return true;
}

bool CWSServerDaemon::Stop(){
	// stop http server daemon
	(*m_server)->Stop();
	return true;
}

bool CWSServerDaemon::SetHandleFactory(){
	// register http server daemon handle 
	CWSHandler::SetHttpHandle();
	return true;
}
