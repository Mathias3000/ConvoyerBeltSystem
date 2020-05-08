#pragma once
#include "keyboard.h"
#include "stateMachine.h"
#include <iostream>

using namespace std;

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

