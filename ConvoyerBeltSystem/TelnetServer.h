#pragma once
#include "TCPServer.h"

class TelnetServer
{
private: 
	int telnetPort = 23;
	TCPServer* telnetServer;


public: 
	TelnetServer();

};

