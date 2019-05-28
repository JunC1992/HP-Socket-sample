#include <unistd.h>

#include "TcpServer.h"

int main(){
	auto tcpDPtr = new CTcpServerDaemon("127.0.0.1", 5555);
	tcpDPtr->Start();
	pause();
}
