#include <iostream>
#include <string>
#include <unistd.h>

#include <hpsocket/HPSocket.h> 
#include <hpsocket/HPSocket-SSL.h> 
#include <hpsocket/common/GlobalDef.h> 

#define HTTP_NAME "http"
#define HTTPS_NAME "https"
#define UPGRADE_HEADER                  "Upgrade"
#define WEB_SOCKET_HEADER_VALUE         "WebSocket"

const BYTE HTTP_WEB_SOCKET_MASK_KEY[]	= {0x1, 0x2, 0x3, 0x4};

class CHttpClientListenerImpl : public CHttpClientListener
{
private:
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID);

	virtual EnHttpParseResult OnMessageBegin(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc);
	virtual EnHttpParseResult OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue);
	virtual EnHttpParseResult OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHttpParseResult OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength);
	virtual EnHttpParseResult OnChunkComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnMessageComplete(IHttpClient* pSender, CONNID dwConnID);
	virtual EnHttpParseResult OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType);
	virtual EnHttpParseResult OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc);

	virtual EnHandleResult OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen);
	virtual EnHandleResult OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID);

public:
	CHttpClientListenerImpl(LPCTSTR lpszName)
		: m_strName(lpszName)
	{
	}

public:
	std::string m_strName;

};

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CHttpClientListenerImpl::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteHost(szAddress, iAddressLen, usPort);
	std::cout<< "connect" << std::endl;
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnHandShake(ITcpClient* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHttpParseResult CHttpClientListenerImpl::OnMessageBegin(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "message begin" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "header complete" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnChunkComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{
	std::cout<< "message complete" << std::endl;
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
	return HPR_OK;
}

EnHttpParseResult CHttpClientListenerImpl::OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)
{
	std::cout<< "parse error" << std::endl;
	return HPR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

EnHandleResult CHttpClientListenerImpl::OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHttpClientListenerImpl::OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{
	BYTE iOperationCode;

	pSender->GetWSMessageState(nullptr, nullptr, &iOperationCode, nullptr, nullptr, nullptr);

	if(iOperationCode == 0x8)
		return HR_ERROR;

	return HR_OK;
}

// ------------------------------------------------------------------------------------------------------------- //

CHttpClientListenerImpl s_listener_1(HTTP_NAME);
CHttpClientPtr s_pClient(&s_listener_1);

void UpgradeProtocal() {
	THeader header[] = {
		{"Connection", UPGRADE_HEADER},
		{UPGRADE_HEADER, WEB_SOCKET_HEADER_VALUE},
		{"Sec-WebSocket-Version", "13"},
		//{"Sec-WebSocket-Key", "w4v7O6xFTi36lq3RNcgctw=="},
		{nullptr, nullptr},         
		{nullptr, nullptr}};

	if(!s_pClient->SendGet("/", header, 3)) {
		std::cout<< "UpgradeProtocal error" << std::endl;
	}
}

void SendWebSocket()
{
	BYTE bCode		= 0x1;
	int iLength		= 14;
	BYTE* pData		= (BYTE*)"<HX>hello<END>";
	//CONNID dwConnID = s_pClient->GetConnectionID();

	//s_pClient->SendWSMessage(TRUE, 0, bCode, HTTP_WEB_SOCKET_MASK_KEY, pData, iLength);
	s_pClient->SendWSMessage(TRUE, 0, bCode, nullptr, pData, iLength);

}

int main(int argc, char* const argv[])
{
	if (!s_pClient->Start("127.0.0.1", 5555, false, "127.0.0.1")) {
		std::cout<< "http start error" << std::endl;
	}
	UpgradeProtocal();

	SendWebSocket();
	pause();
}
