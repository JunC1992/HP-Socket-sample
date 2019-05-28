#pragma once
#include <functional>
#include <memory>
#include <map>

#include "../NetCommandCode.h"

class CEchoTcpHandle{
public:
	CEchoTcpHandle()=default;
	~CEchoTcpHandle()=default;
public:
	void registedTcpHandle(std::map<int, std::function<void(std::string&)>>& handleMap);

public:
	bool Handle(std::string& content);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoTcpHandle> CEchoHttpHandlePtr;
