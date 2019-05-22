#pragma once
#include <memory>

class CEchoHttpHandle{
public:
	bool Handle(std::string& content);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoHttpHandle> CEchoHttpHandlePtr;
