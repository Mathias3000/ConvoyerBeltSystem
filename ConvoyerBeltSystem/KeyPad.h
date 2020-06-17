#pragma once
#include <thread>

#include "keyboard.h"
#include "stateMachine.h"
#include "MotorController.h"

class KeyPad
{

private: 
	Keyboard* keyboard;
	char readValue;

public: 
	KeyPad();
	~KeyPad();
	void handleKeyInput();
	string readKey();
	char getLastKeyInput();

};

