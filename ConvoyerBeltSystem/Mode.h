#pragma once
#include "Command.h"
#include "MotorController.h"
#include "Display.h"
#include "ICommand.h"
#include <thread>

using namespace std;

class Mode
{
private: 
	Command currentCommand;

	//Thread to dispay the U/I relevant data etc:
	thread displayUserInterface;
	int displayUserInterface();
	bool stop;

public: 
	MotorController* motorController;
	Display* display;
	ICommand* icommand;
	virtual int recv() = 0;
};

