#pragma once
#include "ICommunication.h"
#include "TCPClient.h"
#include "TCPServer.h"
#include "SystemLocation.h"

class Network: public ICommunication
{
private: 


public: 

	TCPServer* leftConveyorBelt;
	TCPClient* rightConveyorBelt;
	TCPServer* master;

	Network();
	Command* parse();
	void send(string data, SystemLocation src, SystemLocation dest);
	void send(string data, SystemLocation dest);
};

