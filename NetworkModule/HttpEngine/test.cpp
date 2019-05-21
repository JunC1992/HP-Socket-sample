#include "HttpServer.h"

int main(){
	auto http_DPtr = new CHttpServerDaemon();
	http_DPtr->Start();
	//system("read");
	pause();
}
