#include "TcpServer.h"

int main(){
	auto tcpDPtr = new CTcpServerDeamon("127.0.0.1", 5555);
	tcpDPtr->Start();
	pause();
}
