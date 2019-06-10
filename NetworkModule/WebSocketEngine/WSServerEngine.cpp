#include "WSServerEngine.h"

// ws msg header & end
const char* const G_MSGHEADER = "<HX>";
const char* const G_MSGEND = "<END>";

EnHandleResult CWSServerEngine::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;
	
	pSender->GetListenAddress(szAddress, iAddressLen, usPort);
	std::cout<< "http server: " << szAddress << " port: " << usPort << std::endl;

	return HR_OK;
}

EnHandleResult CWSServerEngine::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	BOOL bPass = TRUE;
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	std::cout<< "get one connect: " << szAddress << " port: " << usPort << std::endl;

	return bPass ? HR_OK : HR_ERROR;
}

EnHandleResult CWSServerEngine::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CWSServerEngine::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::cout<< "receive data: " << pData << std::endl;
	return HR_OK;
}

EnHandleResult CWSServerEngine::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CWSServerEngine::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	std::cout << dwConnID << "on close" << std::endl;
	m_bodyData.erase(dwConnID);
	m_remain.erase(dwConnID);
	//m_bodyMEMPool.deallocate(mC_bodyData[dwConnID]);
	return HR_OK;
}

EnHandleResult CWSServerEngine::OnShutdown(ITcpServer* pSender)
{
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CWSServerEngine::OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)
{
	std::cout<< "on message begin" << std::endl;
	m_bodyData.insert(std::make_pair(dwConnID, ""));
	m_remain.insert(std::make_pair(dwConnID, ""));
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)
{
	//std::cout<< "on request line " << std::endl;
	std::cout<< lpszMethod << ":" << lpszUrl << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	//std::cout<< "on header" << std::endl;
	std::cout<< lpszName << ":" << lpszValue << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnHeadersComplete(IHttpServer* pSender, CONNID dwConnID)
{
	/*
	 *CStringA strSummary = GetHeaderSummary(pSender, dwConnID, "    ", 0, TRUE);
	 */
	std::cout<< "on header complete" << std::endl;

	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::cout<< "on body" << std::endl;
	//m_bodyData[dwConnID] += (char*) pData;

	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	std::cout<< "on message complete : " << dwConnID << std::endl;
	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{

	if(enUpgradeType != HUT_WEB_SOCKET) {
		pSender->SendResponse(dwConnID, HSC_OK, "WebSocket Protocol Only");
		return HPR_OK;
	}

	int iHeaderCount = 2;
	THeader header[] = {{"Connection", UPGRADE_HEADER},
		{UPGRADE_HEADER, WEB_SOCKET_HEADER_VALUE},
		{nullptr, nullptr},
		{nullptr, nullptr}};


	LPCSTR lpszAccept = nullptr;

	//TODO
	// add "Sec-WebSocket-Protocol" auth
	//
	pSender->SendResponse(dwConnID, HSC_SWITCHING_PROTOCOLS, nullptr, header, iHeaderCount);

	return HPR_OK;
}

EnHttpParseResult CWSServerEngine::OnParseError(IHttpServer* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)
{
	return HPR_OK;
}

EnHandleResult CWSServerEngine::OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{

	return HR_OK;
}

EnHandleResult CWSServerEngine::OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::string body(pData, pData + iLength);
	std::cout << "ws message body: " << body << std::endl;
	m_bodyData[dwConnID] += body;
	return HR_OK;
}

EnHandleResult CWSServerEngine::OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID) {
	HttpHandle(pSender, dwConnID);

	return HR_OK;
}

EnHandleResult CWSServerEngine::HttpHandle(IHttpServer* pSender, CONNID dwConnID){
        BOOL bFinal;
        BYTE iReserved, iOperationCode;
	// check current ws state
        if (!pSender->GetWSMessageState(dwConnID, &bFinal, &iReserved, &iOperationCode, nullptr, nullptr, nullptr)) {
		pSender->Disconnect(dwConnID);
		return HR_OK;
	}
	// 0x8: websocket send DISCONNECT operation
	if(iOperationCode == 0x8) {
		pSender->Disconnect(dwConnID);
		return HR_OK;
	}	
	auto body = m_bodyData[dwConnID];
	if (body == "ping") {
		std::string resp = "pong";
		BYTE optCode = 0x1;
		pSender->SendWSMessage(dwConnID, bFinal, iReserved, optCode, nullptr, (BYTE*)resp.data(), resp.length());

		return HR_OK;
	}

	auto vec = Parser(dwConnID, body);
	std::cout << "cmd: " << vec.size() << std::endl;
	for (auto v : vec) {
		m_handleTHPool.AddTask([=]{
			std::string resp;
			HttpHandleProcess(v, resp);
			// 0x1: websocket send TEXT frame
			BYTE optCode = 0x1;
			pSender->SendWSMessage(dwConnID, bFinal, iReserved, optCode, nullptr, (BYTE*)resp.data(), resp.length());
			std::cout << "resp: " << resp << std::endl;
		});

	}
	// reset ws body buffer
	m_bodyData[dwConnID] = "";

	return HR_OK;
}

bool CWSServerEngine::HttpHandleProcess(const std::string& content, std::string& response) {
	// parse content json body
	Json::Reader reader;
	Json::Value rootValue;
	if (!reader.parse(content, rootValue)) {
		response = "ERROR_HTTP_BODY";
		return false;
	}
	bool res = false;
	int cmdCode = 0;

	try{
		// handle request action
		cmdCode = rootValue["cmdcode"].asInt();
		//TODO
		// do some secure check, md5, access time, etc..
		if(CWSHandler::ms_handles.find(cmdCode) != CWSHandler::ms_handles.end()) {
			auto handler = CWSHandler::ms_handles[cmdCode];
			handler(content, response);
		} else {
			res = false;
			response = "UNKNOW_HTTP_CMD";
		}
	} 
	catch(std::exception& e) {
		response = e.what();
	}

	return res;
}

void CWSServerEngine::Init() {
	// set http handle thread pool
	m_handleTHPool.Start();
}

std::vector<std::string> CWSServerEngine::Parser(const CONNID dwConnID, const std::string &content){
	// unpack content
	// trim the package flag, <HX>&&<END>
	auto allMsgStr = m_remain[dwConnID] + content;
	auto startPos = allMsgStr.find(G_MSGHEADER); 
	auto endPos = allMsgStr.find(G_MSGEND);
	auto headLen = strlen(G_MSGHEADER);
	auto endLen = strlen(G_MSGEND);

	if (startPos == std::string::npos || endPos == std::string::npos)
		m_remain[dwConnID] = allMsgStr;

	std::vector<std::string> res;
	while (startPos != std::string::npos && endPos != std::string::npos){
		auto pkg = allMsgStr.substr(startPos + headLen, endPos - startPos - headLen);
		res.push_back(pkg);

		allMsgStr = allMsgStr.substr(endPos + endLen);
		startPos = allMsgStr.find(G_MSGHEADER); 
		endPos = allMsgStr.find(G_MSGEND);
		m_remain[dwConnID] = allMsgStr;
	}

	return res;
}
