#pragma once
#include "keyboard.h"
#include "stateMachine.h"

class SystemManager
{
public: 
	int n, m;
	Keyboard* keyBoard;
	StateMachine* stateMaschine;

	SystemManager();
	~SystemManager();
	void init();
	void startStateMaschine();


};

