#pragma once
#include "Mode.h"

class LocalMode: public Mode
{
public: 
	LocalMode();
	~LocalMode();
	Command* recv();
};

