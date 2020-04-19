#pragma once
#include "Command.h"

class Mode
{
private: 
	Command currentCommand;

public: 
	virtual int recv() = 0;
};

