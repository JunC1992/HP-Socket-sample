#include <unistd.h>
#include "WSServer.h"

int main(){
	auto http_DPtr = new CWSServerDaemon("0.0.0.0", 5555);
	http_DPtr->Start();
	//system("read");
	pause();
}
