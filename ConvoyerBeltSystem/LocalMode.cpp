#include "LocalMode.h"

LocalMode::LocalMode():Mode()
{
	userInterface = new UserInterface();
	telnetServer = new TelnetServer();
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
	return nullptr;
}

void LocalMode::send(Command* command)
{
	// send some data to telnet server
	telnetServer->sendData(command->data);
}

