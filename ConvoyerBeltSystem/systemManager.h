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

void noAction();
void actionSetSpeed();
void actionSetDirection();
void actionFollowProfile();
void actionSetSpeedAndSteps();
void actionHandleRequest_Wait();
void actionHandleRequest_Ready();
void actionSendRequest();
void actionMotorStop();
void actionMotorMove();

bool noCondition();
bool conditionTotalSteps();

