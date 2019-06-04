#include "WSClient.h"
#include <unistd.h>


int main(int argc, char* const argv[])
{
	/*
	 *auto ip = "futures-quote-dev.hengxifintech.com";
	 *auto port = 80;
	 */

	CWSClient wsClient("127.0.0.1", 5555);
	wsClient.Start();
	auto content = "<HX>{\"cmdcode\" :1000}<END>"; 

	wsClient.SendWebSocket(content);
	pause();
}
