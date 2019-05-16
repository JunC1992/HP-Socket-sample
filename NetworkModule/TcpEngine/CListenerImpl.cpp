#include "CListenerImpl.h"

EnHandleResult CListenerImpl::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetListenAddress(szAddress, iAddressLen, usPort);
	//TODO
	//log start info
	std::cout<< "OnPrepareListen...\n";
	std::cout<< "servser addr: "<< szAddress << ", port: " << usPort <<"\n";
	return HR_OK;
}

EnHandleResult CListenerImpl::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	std::cout<< "get one connect: " << szAddress << ":" << usPort << "\n";

	return HR_OK;
}

EnHandleResult CListenerImpl::OnHandShake(ITcpServer* pSender, CONNID dwConnID) 
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength) 
{
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
			remain -= required;
		} else if (result == FR_DATA_NOT_FOUND) {
			//TODO
			//handle err
			return HR_ERROR;
		}
	}
	
	std::string res(vec.begin(), vec.end());
	std::cout<< res << std::endl;
	return HR_OK;
}

EnHandleResult CListenerImpl::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnShutdown(ITcpServer* pSender) 
{
	return HR_OK;
}

int main(){}
