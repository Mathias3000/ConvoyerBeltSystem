#pragma once
#include "Command.h"

class ICommand
{
	virtual Command* parse() = 0;
};

// how to use: Interface
/*
In Mode: currentCommandType: 
	- Set this to a specific class after sendEvent() 
	- in Mode::recv() call the parse() function to parse the received function from the appointed class
	- the parse implementation of the appointed class is used
*/

