#pragma once
#include "Mode.h"

class LocalMode: public Mode
{
public: 
	LocalMode();
	~LocalMode();
	void recv();
	void send(Command command);
};

