#include <iostream>
#include "echoHandle.h"

bool CEchoTcpHandle::Handle(std::string& content){
	content = "ECHO_HELLO_WORLD";
	std::cout<< "in echo handle: " << content <<std::endl;
	return true;
}

void CEchoTcpHandle::registedTcpHandle(std::map<int, std::function<void(std::string&)>>& handleMap) {
	// registed ECHO_TEST
	handleMap[ECHO_TEST] = std::bind(&CEchoTcpHandle::Handle, this, std::placeholders::_1);
}
