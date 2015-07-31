#include <cstdio>
#include <cstdlib>

#include "../../Base.h/Base/base.h"

#define INPUT_PATH "D:\\Steam\\SteamApps\\common\\Age2HD\\savegame\\MP Replay v4.2 @2015.07.23 194624 (1).msx2"
#define OUTPUT_PATH "D:\\temp\\glumpp.out"

using namespace Base::Sockets;
using namespace Base::Utils;

void ClientConnected(TcpClient* client)
{
	printf("There is some Client\n");
}

int main()
{		
	InitSocketLibrary();

	TcpListener listener;
	listener.Bind(IpAddress.Any, 4444);

	bool result = listener.StartListening(ClientConnected);

	if (result == false)
	{
		printf("Kaputt\n");
	}

	while (true)
	{
		SleepMilliseconds(100);
	}

	system("PAUSE");
	return 0;
}