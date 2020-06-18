#pragma once
#include "Command.h"

class ICommunication
{
public: 
	virtual Command* parse() = 0;
};

// how to use: Interface
/*
In Mode: currentCommandType:
	- Set this to a specific class after sendEvent()
	- in Mode::recv() call the parse() function to parse the received function from the appointed class
	- the parse implementation of the appointed class is used

How to use in thread:
	- create a thread in Mode
	- recv() of Servers is called + sendEvent with SM
	- call inferface::recv() in action() of SM
*/
