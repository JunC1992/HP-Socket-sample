#include <hpsocket/HPSocket.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#define TCP_KEEPALIVE_TIME		(60 * 1000)
/* Listener Class */
class ListenerImpl : public CTcpPullServerListener
{

public:
	// 5. process network events
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen){
		std::cout<< "OnPrepareListen...\n";
	};
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient){
		std::cout<< "OnAccept...\n";
	};
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID){
		std::cout<< "OnHandShake...\n";
	};
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength){
		std::cout<< "OnReceive...\n";
	};
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength){
		std::cout<< "OnSend...\n";
	};
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode){
		std::cout<< "OnClose...\n";
	};
	virtual EnHandleResult OnShutdown(ITcpServer* pSender){
		std::cout<< "OnShutdown...\n";
	};

};

int main(int argc, char* const argv[])
{
	// 1. Create listener object
	CListenerImpl s_listener;
	// 2. Create component object (and binding with listener object)
	CTcpPullServerPtr s_pserver(&s_listener);

	// 3. Start component object
	if(!s_pserver->Start("0.0.0.0", 5555))
		exit(1);

	/* wait for exit */
	// ... ... 
	while(1) {
		s_pserver->GetAllConnectionIDs()
		s_pserver->Fetch();
		sleep(3);
	}
	std::cout<< "ending...\n";

	// 6. (optional) Stop component object
	s_pserver->Stop();

	return 0;

	// 7. Destroy component object automatically
	// 8. Destroy listener object automatically
}
