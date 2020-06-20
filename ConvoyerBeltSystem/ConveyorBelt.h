#pragma once

#include "LocalMode.h"
#include "ChainMode.h"
#include "stateMachine.h"
#include <mutex>
#include <type_traits>

using namespace std;

class ConveyorBelt
{
public: 
	ConveyorBelt();
	~ConveyorBelt();
	Mode* currentMode;
	mutex updateMutex;


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

	// reset all communication flags
	void resetCommunicationFlags();
	void stopDisplayUI();
private:


	/*
	Instantiate all needed classes
	Both local and chain mode have to be instiate at the very be, so that the threads(tcp connections, user input from keypad)
	can start at the very beginning
	Singleton for communication classes maybe not needed. No new instantiation during runtime, only reassignments.
	*/
	void init();
	bool stop = false;
	thread workerDisplayUI;
	int displayUI();
};

extern ConveyorBelt* myConveyorBelt;

