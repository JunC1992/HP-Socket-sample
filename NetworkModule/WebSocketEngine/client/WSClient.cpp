#include "WSClient.h"

#include <thread>
#include <unistd.h>

CWSClientEngine g_engine(HTTP_NAME);
CHttpClientPtr g_pClient(&g_engine);

bool CWSClient::upgradeProtocal() {
	THeader header[] = {
		{"Connection", UPGRADE_HEADER},
		{UPGRADE_HEADER, WEB_SOCKET_HEADER_VALUE},
		//{"Sec-WebSocket-Version", "13"},
		//{"Sec-WebSocket-Key", "w4v7O6xFTi36lq3RNcgctw=="},
		{nullptr, nullptr},         
		{nullptr, nullptr}};

	if(!g_pClient->SendGet("/", header, 2)) {
		// log error msg
		std::cout<< "UpgradeProtocal error" << std::endl;
		return false;
	}

	return true;
}

bool CWSClient::Start(){
	// TODO
	// init ws client engine

	// start ws client
	const char* cliIP = "127.0.0.1";
	if (!g_pClient->Start(m_serverIp, m_serverPort, false, cliIP)) {
		// TODO
		// log error msg
		std::cout<< "ws start error" << std::endl;
		return false;
	}

	// upgrade ws potocal
	if (!upgradeProtocal()) {
		// log error msg
		std::cout<< "ws upgrade protocal error" << std::endl;
		return false;
	}

	// quotation request

	return true;
}

bool CWSClient::Stop(){
	return g_pClient->Stop();
}

void CWSClient::HeartBeat(){
	while(true) {
		if(!g_engine.PongWatcher()) {
			// restart ws client
			Stop();
			Start();
		}

		// send ping to ws server
		SendWebSocket("ping");
		sleep(10);
	}
}

void CWSClient::Run(){
	// start client
	Start();

	// heart beat
	std::thread th([=]{
		HeartBeat();
	});
	th.detach();
}

void CWSClient::SendWebSocket(const std::string& content)
{
	BYTE bCode = 0x1;
	std::string data = content;
	int iLength = data.length();
	g_pClient->SendWSMessage(TRUE, 0, bCode, nullptr, (BYTE*)data.data(), iLength);
}
