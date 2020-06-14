#pragma once
#include "Mode.h"
#include "TelnetServer.h"
#include "UserInterface.h"

class LocalMode: public Mode
{
public: 
	
	UserInterface* userInterface;
	TelnetServer* telnetServer;

	LocalMode();
	~LocalMode();
	Command* recv();
};

