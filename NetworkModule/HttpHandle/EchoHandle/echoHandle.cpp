#include "echoHandle.h"

bool CEchoHttpHandle::Handle(std::string& content){
	content = "ECHO_HELLO_WORLD";
	return true;
}
