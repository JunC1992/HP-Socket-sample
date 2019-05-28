#include "TcpServer.h"

/*
 *void CListenerImpl::Stop(){
 *
 *        s_pserver->Stop();
 *}
 */

CTcpServerEngine g_listener;
CTcpPullServerPtr g_pserver(&g_listener);

// HP-Socket tcp daemon start
bool CTcpServerDaemon::Start(){
	SetHandleFactory();
	if(!g_pserver->Start(m_ip, m_port)) {
		//TODO
		//log error msg
		return false;
	}
	return true;
}

bool CTcpServerDaemon::SetHandleFactory(){
	// register tcp request handle
	TcpHandler::SetTcpHandle();
	return true;
}
