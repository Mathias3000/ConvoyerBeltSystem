#pragma once
#include "Mode.h"
#include "Command.h"
#include "string"
#include "Network.h"

using namespace std; 

class ChainMode : public Mode
{
private: 
	Network* network;

public: 
	ChainMode();
	void handleRequest(string ReadyWait);	// TODO: choose proper datatype for ready and wait status. maybe even a class for better usability
	Command* recv();
	void send(Command* command);
};

