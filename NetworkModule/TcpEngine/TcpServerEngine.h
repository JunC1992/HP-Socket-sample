#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

#include <hpsocket/HPSocket.h>
#include <hpsocket/common/GlobalDef.h>
#include <jsoncpp/json/json.h>

#include "../TcpHandle/TcpHandle.h"

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
	// registed handler
	void Register();

	//parse recrived pkg
	std::vector<std::string> Parser(const CONNID dwConnID, const std::string& content);
	void Handle(const CONNID dwConnID, const std::string& content);
	void HandleProcess(const std::string& content);

	//packet responsed msg
	std::string Packet(const std::string& content);

private:

	// tcp stream remain data
	//std::string m_remain;
	std::map<CONNID, std::string> m_remain;
};
