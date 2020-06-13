#pragma once
#include "ICommand.h"
#include "TCPClient.h"
#include "TCPServer.h"

class Network: public ICommand
{
private: 
	TCPServer* leftConveyorBelt;
	TCPClient* rightConveyorBelt;
	TCPServer* master;

public: 
	Network();
	Command* parse();
	enum Destination {
		LeftConveyorBelt, 
		RightConveyorBelt, 
		Master
	};
	void send(string data, Destination destination);
};

