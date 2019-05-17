#include "TcpServerEngine.h"

//set msg header & end
const char* const G_MSGHEADER = "<HX>";
const char* const G_MSGEND = "<END>";
const char* const G_ZEORMSG = "<HX><END>";
const int G_ZEORMSGLEN = 9;

EnHandleResult CTcpServerEngine::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
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

EnHandleResult CTcpServerEngine::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	std::cout<< "get one connect: " << szAddress << ":" << usPort << "\n";

	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnHandShake(ITcpServer* pSender, CONNID dwConnID) 
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength) 
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
	Handle(std::move(res));
	//TODO
	// std::cout<< res << std::endl;
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

EnHandleResult CTcpServerEngine::OnShutdown(ITcpServer* pSender) 
{
	return HR_OK;
}

std::vector<std::string> CTcpServerEngine::Parser(const std::string &content){
/*
 *        std::string allMsgStr = m_remain + content;
 *        auto str_startpos = content.find(G_MSGHEADER); 
 *        auto end_startpos = content.find(G_MSGEND);
 *
 *        if (str_startpos == std::string::npos || end_startpos == std::string::npos)
 *                m_remain = allMsgStr;
 *
 *        std::vector<std::string> res;
 *        while (str_startpos != std::string::npos && end_startpos != std::string::npos){
 *                //std::string res(content.begin()+4, content.end()-5);
 *                m_remain = allMsgStr.substr(end_startpos + strlen(G_MSGEND));
 *                str_startpos = allMsgStr.find(G_MSGHEADER, str_startpos + strlen(G_MSGHEADER));
 *                end_startpos = allMsgStr.find(G_MSGEND, end_startpos + 1);
 *
 *                str_startpos = str_startpos + strlen(G_MSGHEADER);
 *                auto tmp = allMsgStr.substr(str_startpos, end_startpos - str_startpos);
 *                res.push_back(tmp);
 *        }
 *
 */
 	std::vector<std::string> res;
        auto str_startpos = content.find(G_MSGHEADER); 
        auto end_startpos = content.find(G_MSGEND);
        if (str_startpos == std::string::npos || end_startpos == std::string::npos) {
		// incomplete pkg
		return res;
	}
	//res.push_back(content.substr(str_startpos, end_startpos - str_startpos));
	auto pos = str_startpos + strlen(G_MSGHEADER);
	res.push_back(content.substr(pos, end_startpos - pos));

	return res;
}

void CTcpServerEngine::Handle(const std::string &content){
	if(content.length() < G_ZEORMSGLEN) {
		return;
	}
	// parse recrived pkg
	auto res = Parser(content);
	//TODO
	// business handle
	// push response into sys_mq
	for(auto v : res) {
		std::cout<< v << std::endl;
	}
}
