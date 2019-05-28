#include "echoHandle.h"

bool CEchoHttpHandle::Handle(std::string& content){
	content = "ECHO_HELLO_WORLD";
	return true;
}

void CEchoHttpHandle::registedHttpHandle(std::map<int, std::function<void(std::string&)>>& handleMap) {
	// registed ECHO_TEST
	handleMap[ECHO_TEST] = std::bind(&CEchoHttpHandle::Handle, this, std::placeholders::_1);
}
