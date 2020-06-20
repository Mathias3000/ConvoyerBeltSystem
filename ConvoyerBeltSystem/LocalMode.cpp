#include "LocalMode.h"

LocalMode::LocalMode():Mode()
{
	userInterface = UserInterface::getInstance();
	telnetServer = TelnetServer::getInstance();
}

LocalMode* LocalMode::getInstance()
{
	if (instance == NULL) {
		instance = new LocalMode();
	}
	return instance;
}

LocalMode::~LocalMode()
{
	delete this;
}

Command* LocalMode::recv()
{
	communication->parse();


	// Delete later
	//if (userInterface->updateCommunicationType) {
	//	userInterface->parse();
	//}
	//else if (telnetServer->updateCommunicationType)
	//{
	//	telnetServer->parse();
	//}

}

void LocalMode::send(Command* command)
{
	// send some data to telnet server
	telnetServer->sendData(command->data);
}

