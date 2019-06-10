#include "TcpServer.h"

/*
 *void CListenerImpl::Stop(){
 *
 *        s_pserver->Stop();
 *}
 */
	
CTcpServerDaemon::CTcpServerDaemon(const char* ip, const int port): m_ip(ip), m_port(port){
	m_engine = std::make_shared<CTcpServerEngine>();
	m_server = std::make_shared<CTcpPullServerPtr>(m_engine.get());
}

// HP-Socket tcp daemon start
bool CTcpServerDaemon::Start(){
	SetHandleFactory();
	if(!(*m_server)->Start(m_ip, m_port)) {
		//TODO
		//log error msg
		return false;
	}
	return true;
}

bool CTcpServerDaemon::SetHandleFactory(){
	// register tcp request handle
	CTcpHandler::SetTcpHandle();
	return true;
}
