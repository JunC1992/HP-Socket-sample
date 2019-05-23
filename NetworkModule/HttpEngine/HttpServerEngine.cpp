#include "HttpServerEngine.h"

EnHandleResult CHttpServerListenerImpl::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;
	
	pSender->GetListenAddress(szAddress, iAddressLen, usPort);
	std::cout<< "http server: " << szAddress << " port: " << usPort << std::endl;

	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)
{
	BOOL bPass = TRUE;
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	std::cout<< "get one connect: " << szAddress << " port: " << usPort << std::endl;

	return bPass ? HR_OK : HR_ERROR;
}

EnHandleResult CHttpServerListenerImpl::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{

	std::cout<< "receive data: " << pData << std::endl;
	/*
	 *if(pSender->Send(dwConnID, pData, iLength))
	 *        return HR_OK;
	 *else
	 *        return HR_ERROR;
	 */
	 return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
/*
 *
 *        CBufferPtr* pBuffer = nullptr;
 *        pSender->GetConnectionExtra(dwConnID, (PVOID*)&pBuffer);
 *
 *        if(pBuffer) delete pBuffer;
 *
 */
	std::cout << dwConnID << "on close" << std::endl;
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnShutdown(ITcpServer* pSender)
{
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CHttpServerListenerImpl::OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)
{
	std::cout<< "on message begin" << std::endl;
	//std::cout<< m_strName << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)
{
	//std::cout<< "on request line " << std::endl;
	std::cout<< lpszMethod << ":" << lpszUrl << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	//std::cout<< "on header" << std::endl;
	std::cout<< lpszName << ":" << lpszValue << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnHeadersComplete(IHttpServer* pSender, CONNID dwConnID)
{
	/*
	 *CStringA strSummary = GetHeaderSummary(pSender, dwConnID, "    ", 0, TRUE);
	 */
	std::cout<< "on header complete" << std::endl;

	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	std::cout<< "on body" << std::endl;
	//std::cout<< pData << std::endl;
	pSender->SetConnectionExtra(dwConnID, PVOID(pData));

	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	std::cout<< "on message complete : " << dwConnID << std::endl;

	// TODO 
	// thread
	std::thread th(&CHttpServerListenerImpl::HttpHandle, this, pSender, dwConnID);
	th.detach();
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
/*
 *
 *        if(enUpgradeType == HUT_HTTP_TUNNEL)
 *        {
 *                pSender->SendResponse(dwConnID, HSC_OK, "Connection Established");
 *        }
 *        else if(enUpgradeType == HUT_WEB_SOCKET)
 *        {
 *                int iHeaderCount = 2;
 *                THeader header[] = {{"Connection", UPGRADE_HEADER},
 *                                                        {UPGRADE_HEADER, WEB_SOCKET_HEADER_VALUE},
 *                                                        {nullptr, nullptr},
 *                                                        {nullptr, nullptr}};
 *
 *
 *                LPCSTR lpszAccept = nullptr;
 *                
 *                if(!pSender->GetHeader(dwConnID, "Sec-WebSocket-Key", &lpszAccept))
 *                        return HPR_ERROR;
 *
 *                CStringA strAccept;
 *                ::MakeSecWebSocketAccept(lpszAccept, strAccept);
 *
 *                header[2].name	= "Sec-WebSocket-Accept";
 *                header[2].value	= strAccept;
 *                ++iHeaderCount;
 *
 *                CStringA strFirst;
 *                LPCSTR lpszProtocol = nullptr;
 *
 *                if(pSender->GetHeader(dwConnID, "Sec-WebSocket-Protocol", &lpszProtocol))
 *                {
 *                        int i = 0;
 *                        CStringA strProtocol(lpszProtocol);
 *                        strFirst = strProtocol.Tokenize(", ", i);
 *
 *                        if(!strFirst.IsEmpty())
 *                        {
 *                                header[3].name	= "Sec-WebSocket-Protocol";
 *                                header[3].value	= strFirst;
 *                                ++iHeaderCount;
 *                        }
 *                }
 *
 *                pSender->SendResponse(dwConnID, HSC_SWITCHING_PROTOCOLS, nullptr, header, iHeaderCount);
 *                pSender->SetConnectionExtra(dwConnID, new CBufferPtr);
 *        }
 *        else
 *                ASSERT(FALSE);
 *
 */
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnParseError(IHttpServer* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)
{
	std::cout<< "on parse error" << std::endl;
	return HPR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{

	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
/*
 *
 *        CBufferPtr* pBuffer = nullptr;
 *        pSender->GetConnectionExtra(dwConnID, (PVOID*)&pBuffer);
 *        VERIFY(pBuffer);
 *
 *        pBuffer->Cat(pData, iLength);
 *
 */
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
/*
 *
 *        CBufferPtr* pBuffer = nullptr;
 *        pSender->GetConnectionExtra(dwConnID, (PVOID*)&pBuffer);
 *        VERIFY(pBuffer);
 *
 *        BOOL bFinal;
 *        BYTE iReserved, iOperationCode;
 *
 *        VERIFY(pSender->GetWSMessageState(dwConnID, &bFinal, &iReserved, &iOperationCode, nullptr, nullptr, nullptr));
 *
 *        pSender->SendWSMessage(dwConnID, bFinal, iReserved, iOperationCode, nullptr, pBuffer->Ptr(), (int)pBuffer->Size());
 *        pBuffer->Free();
 *
 *        if(iOperationCode == 0x8)
 *                pSender->Disconnect(dwConnID);
 *
 */
	return HR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::HttpHandle(IHttpServer* pSender, CONNID dwConnID){
	// http extra body;
	LPVOID pExBody = nullptr;
	if(!pSender->GetConnectionExtra(dwConnID, (PVOID*)&pExBody)) {
		std::cout << "get connection extra error" << std::endl;
 		return HPR_ERROR;
	}
	if (pExBody == nullptr) {
		// default extra body init
		pExBody = (LPVOID)"HX_DEFAULT";
	}

	std::string strRes;
	auto res = HttpHandleProcess((char*) pExBody, strRes);

	// set http response header 
	THeader header[] = {{"Content-type", "text/plain"}};
        int iHeaderCount = sizeof(header) / sizeof(THeader);
	int reCode = HSC_OK;
	std::string reStatus = "OK";
	if (!res) {
		/*
		 *reCode = HSC_INTERNAL_SERVER_ERROR;
		 *reStatus = "ERROR";
		 */
	}
	pSender->SendResponse(dwConnID, 
			reCode, reStatus.data(),
			header, iHeaderCount,
			//(const BYTE*)(LPCSTR)"",
			(const BYTE*)strRes.data(),
			strRes.length()
			);

        if(!pSender->IsKeepAlive(dwConnID)) {
		pSender->Release(dwConnID);
	} else {
		// reset http extra body
		const char* pData = "HX_DEFAULT";
		pSender->SetConnectionExtra(dwConnID, PVOID(pData));
	}

	return HPR_OK;
}

bool CHttpServerListenerImpl::HttpHandleProcess(const std::string& sBody, std::string& sResponse) {
	//TODO
	// parse content json body
	Json::Reader reader;
	Json::Value rootValue;
	if (!reader.parse(sBody, rootValue)) {
		sResponse = "ERROR_HTTP_BODY";
		return false;
	}
	bool res = false;
	int cmdCode = 0;

	try{
		// handle request action
		cmdCode = rootValue["cmdcode"].asInt();
		//TODO
		// do some secure check, md5, access time, etc..
		if(HttpHandler::ms_handles.find(cmdCode) != HttpHandler::ms_handles.end()) {
			auto handle = HttpHandler::ms_handles[cmdCode];
			handle(sResponse);
		} else {
			res = false;
			sResponse = "UNKNOW_HTTP_CMD";
		}
		/*
		 *
		 *switch (cmdCode) {
		 *case ECHO_TEST: {
		 *        CEchoHttpHandlePtr handle = std::make_shared<CEchoHttpHandle>();
		 *        res = handle->Handle(sResponse);
		 *        break;
		 *}
		 *default: {
		 *        res = false;
		 *        sResponse = "UNKONW_HTTP_CMD";
		 *}
		 *}
		 */
	} 
	catch(std::exception& e) {
		sResponse = e.what();
	}

	return res;
}
