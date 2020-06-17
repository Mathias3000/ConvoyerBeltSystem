#pragma once
#include "KeyPad.h"
#include "Potentiometer.h"
#include "ICommunication.h"
#include "Helpers.h"

class UserInterface: public ICommunication
{
private: 
	KeyPad* keyPad;
	Potentiometer* potentiometer;

public: 

	bool updateCommunicationType = false;

	UserInterface();
	~UserInterface();
	Command* parse();
	Command* pollingData();
};

