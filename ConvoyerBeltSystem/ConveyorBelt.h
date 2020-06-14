#pragma once

#include "LocalMode.h"
#include "ChainMode.h"
#include "stateMachine.h"
#include <mutex>

class ConveyorBelt
{
public: 
	ConveyorBelt();
	~ConveyorBelt();
	Mode* currentMode;
	mutex updateMutex;

private:
	/*
	Purpose updateCurrentCommunicationType: 
	Das setzen des CurrentCommunicationType im TCPServer geht nicht, weil durch das includieren des ConveyorBelt.h es zu einer zirkulären Referenz kommt. 
	Daher muss das anders gelöst werden: update Funktion im Thread, welches schaut, ob ein update gemacht werden muss. 
	Suche im: 
		- TCP Server
		- TCP Client 
		- Telnet Server
		- UserInterface
	*/
	void updateCurrentCommunicationType();
};

extern ConveyorBelt* myConveyorBelt;

