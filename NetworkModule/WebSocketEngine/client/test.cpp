#include "WSClient.h"
#include <unistd.h>


int main(int argc, char* const argv[])
{
	auto ip = "futures-quote-test.hengxifintech.com";
	auto port = 80;

	/*
	 *const char* ip = "139.224.233.67";
	 *int port = 5522;
	 */

	//CWSClient wsClient("127.0.0.1", 5555);
	//CWSClient wsClient("baidu.com", 80);
	//CWSClientEngine g_engine(HTTP_NAME);
	CWSClient wsClient(ip, port);
	wsClient.Run();
	//auto content = "<HX>{\"cmdcode\" :1000}<END>"; 

	//wsClient.SendWebSocket(content);
	pause();
}
