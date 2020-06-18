#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(inet_addr(HOST_IP), TELNET_PORT);
	// delete thread
	// thread* telnetThread = new thread(&TelnetServer::handleUserInput, this);
}

Command* TelnetServer::parse()
{
	Command* receivedCommand;

	if (telnetServer->updateCommunicationType) {
		receivedCommand = new Command(telnetServer->buffer, TelnetUser, Self);
	}
	else {
		receivedCommand = new Command("", NoLocation, NoLocation);
	}
	return receivedCommand;

}

void TelnetServer::sendData(string data)
{
	telnetServer->sendData(data);
}
