#include "TcpServer.h"

/*
 *void CListenerImpl::Stop(){
 *
 *        6. (optional) Stop component object
 *        s_pserver->Stop();
 *}
 */

CTcpServerEngine g_listener;
CTcpPullServerPtr g_pserver(&g_listener);

// HP-Socket tcp daemon start
bool CTcpServerDeamon::Start(){
         if(!g_pserver->Start(m_ip, m_port)) {
		 //TODO
		 //log error msg
		 return false;
	 }
	 return true;
}
