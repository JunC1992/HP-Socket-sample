#include "Session.h"

void Session::Write(const std::string& content) {
	if(m_sender == nullptr) {
		return;
	}

	// TODO
	// send ws response
}
