#pragma once
#include "Command.h"
#include "MotorController.h"
#include "Display.h"
#include "ICommand.h"

class Mode
{
private: 
	Command currentCommand;
	MotorController* motorController;
	Display* display;
	ICommand* icommand;
public: 
	virtual int recv() = 0;
};

