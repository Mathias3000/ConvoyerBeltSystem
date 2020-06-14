#include "LocalMode.h"

LocalMode::LocalMode():Mode()
{
	userInterface = new UserInterface();
	telnetServer = new TelnetServer();
}

LocalMode::~LocalMode()
{
	delete this;
}

Command* LocalMode::recv()
{
	return nullptr;
}

