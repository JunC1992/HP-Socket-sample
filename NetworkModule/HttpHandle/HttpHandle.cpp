#include "HttpHandle.h"

void HttpHandler::SetHttpHandle(){
	CEchoHttpHandle ce;
	ce.registedHttpHandle(ms_handles);
}

std::map<int, std::function<void(std::string&)> > HttpHandler::ms_handles;
