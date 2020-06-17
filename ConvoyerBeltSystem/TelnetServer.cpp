#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(inet_addr(HOST_IP), TELNET_PORT);
	thread* telnetThread = new thread(&TelnetServer::handleUserInput, this);
}

Command* TelnetServer::parse()
{


	return nullptr;
}

void TelnetServer::sendData(string data)
{
	telnetServer->sendData(data);
}

void TelnetServer::handleUserInput()
{
	string input(telnetServer->buffer);

	// debug
	cout << "Received from User: " << input << endl;

	updateCommunicationType = true;
	if (input == "tel start\r\n") {
		myStateMaschine->sendEvent("RecvCmdRequest");
	}
	else if (input == "tel stop\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReleased");
	}
	else if (input == "tel dir right\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdReady");
	}
	else if (input == "tel dir left\r\n")
	{
		myStateMaschine->sendEvent("RecvCmdWait");
	}
	else if (input.find(SPEED_CMD) != string::npos)		// check if speed command string
	{
		string s = input;
		std::string delimiter = ":";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			std::cout << token << std::endl;
			s.erase(0, pos + delimiter.length());
		}
		std::cout << token << std::endl;
		speedBuffer = stoi(token);
	}
	else
	{
		updateCommunicationType = false;
	}

}
