#include <unistd.h>
#include "HttpServer.h"

int main(){
	auto http_DPtr = new CHttpServerDaemon("0.0.0.0", 5555);
	http_DPtr->Start();
	//system("read");
	pause();
}
