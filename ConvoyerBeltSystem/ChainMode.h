#pragma once
#include "Mode.h"
#include "Command.h"
#include "string"

using namespace std; 

class ChainMode : public Mode
{
private: 

public: 
	int send(Command command);
	int handleRequest(string ReadyWait);	// TODO: choose proper datatype for ready and wait status. maybe even a class for better usability
};

