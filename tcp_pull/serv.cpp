#include <hpsocket/HPSocket.h>
#include <hpsocket/common/GlobalDef.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>

/* Listener Class */
class CListenerImpl : public CTcpPullServerListener
{

public:
	// 5. process network events
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen){
		std::cout<< "OnPrepareListen...\n";

		TCHAR szAddress[50];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;
		pSender->GetListenAddress(szAddress, iAddressLen, usPort);
		std::cout<< "servser addr: "<< szAddress << ", port: " << usPort <<"\n";

		return HR_OK;
	};

	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient){
		TCHAR szAddress[50];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;

		pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
		std::cout<< "get one connect: " << szAddress << ":" << usPort << "\n";

		return HR_OK;
	};

	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID){
		//std::cout<< "OnHandShake...\n";
		return HR_OK;
	};

        virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
/*
 *        virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength){
 *                TPkgInfo* pInfo	= ::FindPkgInfo(pSender, dwConnID);
 *                ITcpPullServer* pServer	= ITcpPullServer::FromS(pSender);
 *
 *                if(pInfo != nullptr)
 *                {
 *                        int required = pInfo->length;
 *                        int remain = iLength;
 *
 *                        while(remain >= required)
 *                        {
 *                                remain -= required;
 *                                CBufferPtr buffer(required);
 *
 *                                EnFetchResult result = pServer->Fetch(dwConnID, buffer, (int)buffer.Size());
 *
 *                                if(result == FR_OK)
 *                                {
 *                                        ::PostOnReceive(dwConnID, buffer, (int)buffer.Size());
 *
 *                                        if(pInfo->is_header)
 *                                        {
 *                                                TPkgHeader* pHeader = (TPkgHeader*)buffer.Ptr();
 *#ifdef DEBUG
 *                                                PRINTLN("(head) -> seq: %d, body_len: %d", pHeader->seq, pHeader->body_len);
 *#endif
 *                                                required = pHeader->body_len;
 *                                        }
 *                                        else
 *                                        {
 *#ifdef DEBUG
 *                                                TPkgBody* pBody = (TPkgBody*)(BYTE*)buffer;
 *                                                PRINTLN("(body) -> name: %s, age: %d, desc: %s", pBody->name, pBody->age, pBody->desc);
 *#endif
 *                                                required = sizeof(TPkgHeader);
 *                                        }
 *
 *                                        pInfo->is_header = !pInfo->is_header;
 *                                        pInfo->length	 = required;
 *
 *                                        if(!pSender->Send(dwConnID, buffer, (int)buffer.Size()))
 *                                                return HR_ERROR;
 *                                }
 *                        }
 *                }
 *
 *                return HR_OK;
 *        };
 */

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

EnHandleResult CListenerImpl::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength){
	std::vector<BYTE> vec;

	ITcpPullServer* pServer = ITcpPullServer::FromS(pSender);
	// package size 16
	int required = 16;
	int remain = iLength;

	while(remain > 0){
		BYTE buf[required];
		if (required > remain) {
			required = remain;
		}
		EnFetchResult result = pServer->Fetch(dwConnID, buf, required);
		if(result == FR_OK) {
			vec.insert(vec.end(), buf, buf+required);
		}
		remain -= required;
	}
	
	std::string res(vec.begin(), vec.end());
	std::cout<< res << std::endl;
}

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
	//
	pause();
	
	std::cout<< "ending...\n";

	// 6. (optional) Stop component object
	s_pserver->Stop();

	return 0;

	// 7. Destroy component object automatically
	// 8. Destroy listener object automatically
}
