#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(inet_addr(HOST_IP), TELNET_PORT);
}
