#pragma once
#include "LocalMode.h"
#include "ChainMode.h"
#include "stateMachine.h"
#include <mutex>
#include <type_traits>
#include "Helpers.h"

using namespace std;

class ConveyorBelt
{
public: 
	ConveyorBelt();
	~ConveyorBelt();
	Mode* currentMode;
	mutex updateMutex;
	mutex displayMutex;
	string* currentAction = new string("No Actions at the moment. ");
	void showDisplayOutput();
	int displayUI();
	// void updateCurrentCommunicationType();
	// void resetCommunicationFlags();
	void stopDisplayUI();
private:
	void init();
	bool stop = false;
	thread workerDisplayUI;

	char* commands[7] = {
		"KEYBOARD commands: ",
		"[F] chain mode\t [E] local mode\t [D] speed with poti",
		"[1] right dir\t [2] left dir\t [3] start profile\t [4] stop profile",
		"--------------------------------------------------------------------------------",
		"TELNET commands: ",
		"[tel start]\t [tel stop]",
		"[tel dir:r]\t [tel dir:l] \t [tel speed:x]",
	};

	char* commands2[4] = {
		"--------------------------------------------------------------------------------",
		"TCP commands: ",
		"[request]\t [wait]\t\t [ready]\t [release]",
		"================================================================================",
	};

};

extern ConveyorBelt* myConveyorBelt;

