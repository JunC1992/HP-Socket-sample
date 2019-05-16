#pragma once
#include <hpsocket/HPSocket.h>
#include <hpsocket/common/GlobalDef.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>

//#include "../global/helper.h"

/* Listener Class */
class CListenerImpl : public CTcpPullServerListener
{

public:
	// HP-Socket tcp pull compoents func
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient);
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);
};
