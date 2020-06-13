#pragma once
#include "KeyPad.h"
#include "Potentiometer.h"
#include "ICommand.h"

class UserInterface: public ICommand
{
private: 
	KeyPad* keyPad;
	Potentiometer* potentiometer;

public: 
	UserInterface();
	~UserInterface();
	Command* parse();
};

