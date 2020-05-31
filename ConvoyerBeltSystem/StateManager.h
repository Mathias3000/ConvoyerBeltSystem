#pragma once
#include "keyboard.h"
#include "stateMachine.h"
#include <iostream>
#include "SpeedProfile.h"
#include <thread>
#include <mutex>
#include "MotorController.h"
#include "Helpers.h"

using namespace std;


class StateManager
{
public: 

	mutex mtx;

	StateManager();
	~StateManager();
	void init();
	void startStateMaschine();

};

// Function for reading keyInputs
void readKeyInputs();

// implement noAction() only once for actual implementation
void noAction1();
void noAction2();
void noAction3();
void noAction4();
void noAction5();
void actionSetSpeed1();
void actionSetSpeed2();
void actionSetDirection();
void actionFollowProfile1();
void actionFollowProfile2();
void actionSetSpeedAndSteps();
void actionHandleRequest_Wait1();
void actionHandleRequest_Wait2();
void actionHandleRequest_Wait3();
void actionHandleRequest_Wait4();
void actionHandleRequest_Ready();
void actionSendRequest();
void actionMotorStop1();
void actionMotorStop2();
void actionMotorMove();

bool noCondition();
bool conditionTotalSteps();
