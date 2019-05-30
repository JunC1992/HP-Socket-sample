#include "HttpHandle.h"

void CHttpHandler::SetHttpHandle(){
	CEchoHttpHandle ce;
	ce.registedHttpHandle(ms_handles);
}

std::map<int, std::function<void(std::string&)> > CHttpHandler::ms_handles;
