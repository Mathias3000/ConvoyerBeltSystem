#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(inet_addr(HOST_IP), TELNET_PORT);
}

Command* TelnetServer::parse()
{


	return nullptr;
}

void TelnetServer::sendData(string data)
{
	telnetServer->sendData(data);
}
