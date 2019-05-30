#include "WSHandle.h"

void CWSHandler::SetHttpHandle(){
	CEchoHttpHandle ce;
	ce.registedHttpHandle(ms_handles);
}

std::map<int, std::function<void(std::string&)> > CWSHandler::ms_handles;
