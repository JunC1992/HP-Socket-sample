#pragma once
#include <functional>
#include <memory>
#include <map>

#include "../NetCommandCode.h"

class CEchoHttpHandle{
public:
	CEchoHttpHandle()=default;
	~CEchoHttpHandle()=default;
public:
	void registedHttpHandle(std::map<int, std::function<void(std::string&)>>& handleMap);

public:
	bool Handle(std::string& content);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoHttpHandle> CEchoHttpHandlePtr;
