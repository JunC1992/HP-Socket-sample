#pragma once
#include <hpsocket/HPSocket.h>
#include <hpsocket/common/GlobalDef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <vector>

//#include "../global/helper.h"
struct HX_MSG {
	std::string msg;
};

/* Listener Class */
class CTcpServerEngine: public CTcpPullServerListener {

public:
	// HP-Socket tcp pull components func
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient);
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);

public:
	//parse recrived pkg
	std::vector<std::string> Parser(const std::string &content);
	//packet responsed msg
	std::string Packet(const std::string &content);

	void Handle(const std::string &content);
	void Register();

private:

	// tcp stream remain data
	std::string m_remain;
};
