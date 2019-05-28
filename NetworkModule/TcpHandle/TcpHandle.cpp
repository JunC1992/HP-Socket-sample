#include "TcpHandle.h"

void TcpHandler::SetTcpHandle(){
	CEchoTcpHandle ce;
	ce.registedTcpHandle(ms_handles);
}

std::map<int, std::function<void(std::string&)> > TcpHandler::ms_handles;
