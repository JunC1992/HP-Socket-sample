#include "TcpHandle.h"

void CTcpHandler::SetTcpHandle(){
	CEchoTcpHandle ce;
	ce.registedTcpHandle(ms_handles);
}

std::map<int, std::function<void(std::string&)> > CTcpHandler::ms_handles;
