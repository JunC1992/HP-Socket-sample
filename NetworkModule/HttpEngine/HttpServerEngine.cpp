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
	m_bodyData.erase(dwConnID);
	//m_bodyMEMPool.deallocate(mC_bodyData[dwConnID]);
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
	//if mC_bodyData.find();
	//mC_bodyData[dwConnID] = m_bodyMEMPool.allocate();
	//
	// set $CONNID body buffer 
	m_bodyData.insert(std::make_pair(dwConnID, ""));
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
	//pSender->SetConnectionExtra(dwConnID, PVOID(pData));
	//std::string tmp += (char*) pData;
	//memncpy(mC_bodyData[dwConnID], tmp.data(), tmp.length);
	//
	// TODO
	// rwmutex
	std::string body(pData, pData + iLength);
	m_bodyData[dwConnID] += body;

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
/*
 *        std::thread th(&CHttpServerListenerImpl::HttpHandle, this, pSender, dwConnID);
 *        th.detach();
 */
	m_handleTHPool.AddTask([=]{
		HttpHandle(pSender, dwConnID);
	});
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
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
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::HttpHandle(IHttpServer* pSender, CONNID dwConnID){
	// http extra body;
	/*
	 *LPVOID pExBody = nullptr;
	 *if(!pSender->GetConnectionExtra(dwConnID, (PVOID*)&pExBody)) {
	 *        std::cout << "get connection extra error" << std::endl;
         *n HPR_ERROR;
	 *}
	 *if (pExBody == nullptr) {
	 *        // default extra body init
	 *        pExBody = (LPVOID)"HX_DEFAULT";
	 *}
	 */

	std::string strRes;
	std::string pExBody = m_bodyData[dwConnID];
	auto res = HttpHandleProcess(pExBody, strRes);

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

        if(!pSender->IsKeepAlive(dwConnID))
		pSender->Release(dwConnID);

	// reset ws body buffer
	m_bodyData[dwConnID] = "";
	return HPR_OK;
}

bool CHttpServerListenerImpl::HttpHandleProcess(const std::string& sBody, std::string& sResponse) {
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
			auto handler = HttpHandler::ms_handles[cmdCode];
			handler(sResponse);
		} else {
			res = false;
			sResponse = "UNKNOW_HTTP_CMD";
		}
		/*
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

void CHttpServerListenerImpl::Init() {
	// set http handle thread pool
	m_handleTHPool.Start();
}
