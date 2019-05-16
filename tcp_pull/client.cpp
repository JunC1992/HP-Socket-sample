#include <hpsocket/HPSocket.h>
#include <hpsocket/SocketInterface.h>
#include <hpsocket/HPTypeDef.h>
#include <hpsocket/common/GlobalDef.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#define TCP_KEEPALIVE_TIME		(60 * 1000)
/* Listener Class */
class CListenerImpl : public CTcpPullClientListener
{

public:
	// 5. process network events
	virtual EnHandleResult OnPrepareListen(ITcpClient* pSender, SOCKET soListen){
		std::cout<< "OnPrepareListen...\n";
	}
	virtual EnHandleResult OnAccept(ITcpClient* pSender, CONNID dwConnID, UINT_PTR soClient){
		std::cout<< "OnAccept...\n";
	}
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID){
		std::cout<< "OnHandShake...\n";
	}
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength){
		std::cout<< "OnReceive...\n";
	}
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength){
		std::cout<< "OnSend...\n";
	}
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode){
		std::cout<< "OnClose...\n";
	}
	virtual EnHandleResult OnShutdown(ITcpClient* pSender){
		std::cout<< "OnShutdown...\n";
	}

	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID) {
		std::cout<< "OnConnect...\n";
	}
};

int main(int argc, char* const argv[])
{
	// 1. Create listener object
	CListenerImpl s_listener;
	// 2. Create component object (and binding with listener object)
	CTcpPullClientPtr s_pclient(&s_listener);
	// 3. Start component object
	if(!s_pclient->Start("127.0.0.1", 5555, true, "127.0.0.1"))
		exit(1);
	
	//s_pclient->Send("hello", 5);
	/* wait for exit */
	pause();

	std::cout<< "ending...\n";

	// 6. (optional) Stop component object
	s_pclient->Stop();

	return 0;

	// 7. Destroy component object automatically
	// 8. Destroy listener object automatically
}
