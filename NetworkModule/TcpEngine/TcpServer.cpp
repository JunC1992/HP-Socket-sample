#include "TcpServer.h"

/*
 *void CListenerImpl::Stop(){
 *
 *        6. (optional) Stop component object
 *        s_pserver->Stop();
 *}
 */

// HP-Socket tcp daemon start
bool CTcpServerDeamon::Run(){
         // 1. Create listener object
         CListenerImpl s_listener;
         // 2. Create component object (and binding with listener object)
         CTcpPullServerPtr s_pserver(&s_listener);
 
         // 3. Start component object
         if(!s_pserver->Start(m_ip, m_port)) {
		 //TODO
		 //log error msg
		 return false;
	 }
	 return true;
}
