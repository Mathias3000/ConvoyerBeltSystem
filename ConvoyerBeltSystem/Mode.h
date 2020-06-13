#pragma once
#include "Command.h"
#include "MotorController.h"
#include "Display.h"
#include "UserInterface.h"
#include "Network.h"
#include "ICommunication.h"

class Mode
{
private: 
	Command* receivedCommand;


public: 
	MotorController* motorController;
	Display* display;
	ICommunication* communication;

	Mode();

	// Mode();
	virtual Command* recv() = 0;	// ICommand is used only for recv(): probably neccessary to change return type of recv()
};

