/*
 *#include "../../global/helper.h"
 *#include "../../../src/HttpServer.h"
 */
#include "CHttpServerListenerImpl.h"
#include <iostream>
#include <cstring>

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CHttpServerListenerImpl::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;
	
	pSender->GetListenAddress(szAddress, iAddressLen, usPort);
	std::cout<< "http server: " << szAddress << " port: " << usPort << std::endl;
	//::PostOnPrepareListen(szAddress, usPort, m_strName);

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
	//::PostOnAccept(dwConnID, szAddress, usPort, bPass, m_strName);

	return bPass ? HR_OK : HR_ERROR;
}

EnHandleResult CHttpServerListenerImpl::OnHandShake(ITcpServer* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	//::PostOnReceive(dwConnID, pData, iLength, m_strName);

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
	//::PostOnSend(dwConnID, pData, iLength, m_strName);
	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
/*
 *        iErrorCode == SE_OK ? ::PostOnClose(dwConnID, m_strName)	:
 *        ::PostOnError(dwConnID, enOperation, iErrorCode, m_strName)	;
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
	//::PostOnShutdown(m_strName);
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CHttpServerListenerImpl::OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)
{
	//::PostOnMessageBegin(dwConnID, m_strName);
	std::cout<< "on message begin" << std::endl;
	//std::cout<< m_strName << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)
{
	//::PostOnRequestLine(dwConnID, lpszMethod, pSender->GetUrlFieldSet(dwConnID), lpszUrl, m_strName);
	//std::cout<< "on request line " << std::endl;
	std::cout<< lpszMethod << ":" << lpszUrl << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	//::PostOnHeader(dwConnID, lpszName, lpszValue, m_strName);
	//std::cout<< "on header" << std::endl;
	std::cout<< lpszName << ":" << lpszValue << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnHeadersComplete(IHttpServer* pSender, CONNID dwConnID)
{
	/*
	 *CStringA strSummary = GetHeaderSummary(pSender, dwConnID, "    ", 0, TRUE);
	 *::PostOnHeadersComplete(dwConnID, strSummary, m_strName);
	 */
	std::cout<< "on header complete" << std::endl;

	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	//::PostOnBody(dwConnID, pData, iLength, m_strName);
	std::cout<< "on body" << std::endl;
	//std::cout<< pData << std::endl;
	pSender->SetConnectionExtra(dwConnID, PVOID(pData));

	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)
{
	//::PostOnChunkHeader(dwConnID, iLength, m_strName);
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)
{
	//::PostOnChunkComplete(dwConnID, m_strName);
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnMessageComplete(IHttpServer* pSender, CONNID dwConnID)
{
	std::cout<< "on message complete" << std::endl;
	std::cout<< dwConnID << std::endl;

	//http extra body;
	LPVOID pExBody = nullptr;
	if(!pSender->GetConnectionExtra(dwConnID, (PVOID*)&pExBody)) {
		std::cout << "get connection extra error" << std::endl;
 		return HPR_ERROR;
	}

	std::cout<< (char* )pExBody << std::endl;

	THeader header[] = {{"Content-type", "text/plain"}};
        int iHeaderCount = sizeof(header) / sizeof(THeader);
	//auto pData = "hello world";
	auto lenBody = strlen((char*) (pExBody));

	pSender->SendResponse(dwConnID, 
			HSC_OK, "OK",
			header, iHeaderCount,
			(const BYTE*)(LPCSTR) pExBody,
			lenBody
			);		                              
        if(!pSender->IsKeepAlive(dwConnID))
		pSender->Release(dwConnID);
	//::PostOnMessageComplete(dwConnID, m_strName);

/*
 *        if(pSender->IsUpgrade(dwConnID))
 *                return HPR_OK;
 *
 *        CStringA strBody = GetHeaderSummary(pSender, dwConnID, "    ", 0, FALSE);
 *        int iBodyLength  = strBody.GetLength();
 *        BOOL bSkipBody	 = FALSE;
 *
 *        if(strcmp(pSender->GetMethod(dwConnID), HTTP_METHOD_HEAD) == 0)
 *                bSkipBody = TRUE;
 *
 *        CStringA strContentLength;
 *        strContentLength.Format("%u", iBodyLength);
 *
 *        DWORD dwSeq				= 1;
 *        LPCSTR lpszReqSequence	= nullptr;
 *        CStringA strSeq;
 *
 *        if(pSender->GetCookie(dwConnID, "__reqSequence_1", &lpszReqSequence))
 *                dwSeq += atoi(lpszReqSequence);
 *
 *        strSeq.Format("%u", dwSeq);
 *
 *        CStringA strSeqCookie1 = CCookie::ToString("__reqSequence_1", strSeq, nullptr, nullptr, -1, TRUE, TRUE, CCookie::SS_LAX);
 *
 *        dwSeq			= 1;
 *        lpszReqSequence	= nullptr;
 *
 *        if(pSender->GetCookie(dwConnID, "__reqSequence_2", &lpszReqSequence))
 *                dwSeq += atoi(lpszReqSequence);
 *
 *        strSeq.Format("%u", dwSeq);
 *
 *        CStringA strSeqCookie2 = CCookie::ToString("__reqSequence_2", strSeq, nullptr, "/", 300, FALSE, FALSE, CCookie::SS_NONE);
 *
 *        THeader header[] = {{"Content-Type", "text/plain"}, {"Content-Length", strContentLength}, {"Set-Cookie", strSeqCookie1}, {"Set-Cookie", strSeqCookie2}};
 *        int iHeaderCount = sizeof(header) / sizeof(THeader);
 *
 *        if(bSkipBody)
 *        {
 *                strBody.Empty();
 *                iBodyLength = 0;
 *        }
 *
 *        pSender->SendResponse(	dwConnID,
 *                                                        HSC_OK,
 *                                                        "HP Http Server OK",
 *                                                        header, iHeaderCount,
 *                                                        (const BYTE*)(LPCSTR)strBody,
 *                                                        iBodyLength);
 *
 *        if(!pSender->IsKeepAlive(dwConnID))
 *                pSender->Release(dwConnID);
 *
 */
	return HPR_OK;
}

EnHttpParseResult CHttpServerListenerImpl::OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
/*
 *        ::PostOnUpgrade(dwConnID, enUpgradeType, m_strName);
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
	//::PostOnParseError(dwConnID, iErrorCode, lpszErrorDesc, m_strName);
	std::cout<< "on parse error" << std::endl;
	return HPR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CHttpServerListenerImpl::OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{
	//::PostOnWSMessageHeader(dwConnID, bFinal, iReserved, iOperationCode, lpszMask, ullBodyLen, m_strName);

	return HR_OK;
}

EnHandleResult CHttpServerListenerImpl::OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
/*
 *        ::PostOnWSMessageBody(dwConnID, pData, iLength, m_strName);
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
 *        ::PostOnWSMessageComplete(dwConnID, m_strName);
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

// ------------------------------------------------------------------------------------------------------------- //

//CStringA CHttpServerListenerImpl::GetHeaderSummary(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszSep, int iSepCount, BOOL bWithContentLength)
std::string CHttpServerListenerImpl::GetHeaderSummary(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszSep, int iSepCount, BOOL bWithContentLength)
{
	//CStringA strSEP1;
/*
 *        std::string strSEP1;
 *
 *        for(int i = 0; i < iSepCount; i++)
 *                strSEP1 += lpszSep;
 *
 *        //CStringA strSEP2(strSEP1);
 *        std::string strSEP2(strSEP1);
 *        strSEP2 += lpszSep;
 *
 *        LPCSTR SEP1 = (LPCSTR)strSEP1;
 *        LPCSTR SEP2 = (LPCSTR)strSEP2;
 *
 *        //CStringA strResult;
 *        std::string strResult;
 *
 *        //USHORT usUrlFieldSet = pSender->GetUrlFieldSet(dwConnID);
 *
 *        strResult.AppendFormat("%s[URL Fields]%s", SEP1, CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "SCHEMA", pSender->GetUrlField(dwConnID, HUF_SCHEMA), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "HOST", pSender->GetUrlField(dwConnID, HUF_HOST), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "PORT", pSender->GetUrlField(dwConnID, HUF_PORT), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "PATH", pSender->GetUrlField(dwConnID, HUF_PATH), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "QUERY", pSender->GetUrlField(dwConnID, HUF_QUERY), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "FRAGMENT", pSender->GetUrlField(dwConnID, HUF_FRAGMENT), CRLF);
 *        strResult.AppendFormat("%s%8s: %s%s", SEP2, "USERINFO", pSender->GetUrlField(dwConnID, HUF_USERINFO), CRLF);	
 *
 *        DWORD dwHeaderCount = 0;
 *        pSender->GetAllHeaders(dwConnID, nullptr, dwHeaderCount);
 *
 *        strResult.AppendFormat("%s[Request Headers]%s", SEP1, CRLF);
 *
 *        if(dwHeaderCount == 0)
 *                strResult.AppendFormat("%s(no header)%s", SEP2, CRLF);
 *        else
 *        {
 *                unique_ptr<THeader[]> headers(new THeader[dwHeaderCount]);
 *                VERIFY(pSender->GetAllHeaders(dwConnID, headers.get(), dwHeaderCount));
 *
 *                for(DWORD i = 0; i < dwHeaderCount; i++)
 *                        strResult.AppendFormat("%s%s: %s%s", SEP2, headers[i].name, headers[i].value, CRLF);
 *        }
 *
 *        DWORD dwCookieCount = 0;
 *        pSender->GetAllCookies(dwConnID, nullptr, dwCookieCount);
 *
 *        strResult.AppendFormat("%s[Cookies]%s", SEP1, CRLF);
 *
 *        if(dwCookieCount == 0)
 *                strResult.AppendFormat("%s(no cookie)%s", SEP2, CRLF);
 *        else
 *        {
 *                unique_ptr<TCookie[]> cookies(new TCookie[dwCookieCount]);
 *                VERIFY(pSender->GetAllCookies(dwConnID, cookies.get(), dwCookieCount));
 *
 *                for(DWORD i = 0; i < dwCookieCount; i++)
 *                        strResult.AppendFormat("%s%s: %s%s", SEP2, cookies[i].name, cookies[i].value, CRLF);
 *        }
 *
 *        std::string strVersion;
 *        ::HttpVersionToString((EnHttpVersion)pSender->GetVersion(dwConnID), strVersion);
 *        EnHttpUpgradeType enUpgType	= pSender->GetUpgradeType(dwConnID);
 *        LPCSTR lpszUpgrade			= enUpgType != HUT_NONE ? "true" : "false";
 *        LPCSTR lpszKeepAlive		= pSender->IsKeepAlive(dwConnID) ? "true" : "false";
 *
 *        strResult.AppendFormat("%s[Basic Info]%s", SEP1, CRLF);
 *        strResult.AppendFormat("%s%13s: %s%s", SEP2, "Version", (LPCSTR)strVersion, CRLF);
 *        strResult.AppendFormat("%s%13s: %s%s", SEP2, "Method", pSender->GetMethod(dwConnID), CRLF);
 *        strResult.AppendFormat("%s%13s: %s%s", SEP2, "IsUpgrade", lpszUpgrade, CRLF);
 *        if(enUpgType != HUT_NONE)
 *                strResult.AppendFormat("%s%13s: %d%s", SEP2, "UpgradeType", enUpgType, CRLF);
 *        strResult.AppendFormat("%s%13s: %s%s", SEP2, "IsKeepAlive", lpszKeepAlive, CRLF);
 *        if(bWithContentLength)
 *                strResult.AppendFormat("%s%13s: %lld%s", SEP2, "ContentLength", pSender->GetContentLength(dwConnID), CRLF);
 *        strResult.AppendFormat("%s%13s: %s%s", SEP2, "ContentType", pSender->GetContentType(dwConnID), CRLF);
 * 
 */
	//return strResult;
}


// ------------------------------------------------------------------------------------------------------------- //


// ------------------------------------------------------------------------------------------------------------- //

//const CString SPECIAL_SERVER_NAME	= _T("hpsocket.org");
//int SPECIAL_SERVER_INDEX			= -1;

int CALLBACK SIN_ServerNameCallback(LPCTSTR lpszServerName)
{
/*
 *        if(::IsIPAddress(lpszServerName))
 *                return 0;
 *
 *        int len  = lstrlen(lpszServerName);
 *        int diff = len - SPECIAL_SERVER_NAME.GetLength();
 *
 *        if(diff < 0)
 *                return 0;
 *
 *        if(SPECIAL_SERVER_NAME.CompareNoCase(lpszServerName + diff) != 0)
 *                return 0;
 *
 *        return SPECIAL_SERVER_INDEX;
 */
}
/*
 *
 *CHttpServerListenerImpl s_listener_1("http");
 *CHttpServerListenerImpl s_listener_2(HTTPS_NAME);
 *CHttpServerPtr s_http_server(&s_listener_1);
 *CHttpsServer s_https_server(&s_listener_2);
 *int main(int argc, char* const argv[])
 *{
 *
 *        s_http_server->Start("0.0.0.0", 5555);
 *        pause();
 *
 *        return 0;
 *}
 */
