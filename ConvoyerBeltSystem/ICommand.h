#pragma once
#include "Command.h"

class ICommand
{
	virtual Command parse() = 0;
};

