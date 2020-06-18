#pragma once
#include "Mode.h"
#include "TelnetServer.h"
#include "UserInterface.h"

class LocalMode: public Mode
{
	static LocalMode* instance;
private: 

	LocalMode();

public: 

	UserInterface* userInterface;
	TelnetServer* telnetServer;

	// singleton 
	static LocalMode* getInstance();

	~LocalMode();
	Command* recv();
	void send(Command* command);	// send info to telnet server
};

