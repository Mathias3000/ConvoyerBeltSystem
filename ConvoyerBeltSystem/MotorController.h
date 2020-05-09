#pragma once
#include "defines.h"
#include <iostream>

using namespace std;

class MotorController
{
private:
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	int currentSteps;
	enum MotorState
	{
		movingLeft, movingRight, Stop
	};
public:
	int followProfile(int direction);
	int move(double speed, double time);
	int stop(void);
	int setSpeed(double speed);
	double getCurrentSpeed(void);
	MotorState getCurrentMotorState(void);
	int setDirection(int direction);
	bool readyToRecvPayload(void);
	bool finishedProfile(void);
};

