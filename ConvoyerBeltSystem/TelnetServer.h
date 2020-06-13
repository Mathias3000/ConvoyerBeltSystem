#pragma once
#include "TCPServer.h"
#include "ICommand.h"

class TelnetServer: public ICommand
{
private: 
	int telnetPort = 23;
	TCPServer* telnetServer;


public: 

	double buffer = 0;		// buffer to save last speed value
	bool dirBuffer = true;	// buffer to save last direction value: true = right & false = left

	TelnetServer();
	Command* parse();
	void sendData(string data);

};

