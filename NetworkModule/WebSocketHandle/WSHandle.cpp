#include "WSHandle.h"

void CWSHandler::SetHttpHandle(){
	CEchoHttpHandle ce;
	ce.registedHttpHandle(ms_handles);
}

WS_HANDLE_MAP CWSHandler::ms_handles;
