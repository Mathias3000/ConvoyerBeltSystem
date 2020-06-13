#pragma once
#include "Command.h"
//#include "MotorController.h"
//#include "Display.h"
//#include "ICommand.h"

class Mode
{
private: 
	Command* receivedCommand;

public: 
	//MotorController* motorController;
	//Display* display;
	//ICommand* currentCommandType;

	// Mode();
	virtual void recv() = 0;	// ICommand is used only for recv(): probably neccessary to change return type of recv()
	virtual void send(Command command)  = 0;
};

