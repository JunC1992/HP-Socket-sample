#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>

#include "NetCommandCode.h"
#include "EchoHandle/echoHandle.h"

class CHttpHandler{

public:
	static void SetHttpHandle();

public:
	static std::map<int, std::function<void(std::string&)> > ms_handles;
};
