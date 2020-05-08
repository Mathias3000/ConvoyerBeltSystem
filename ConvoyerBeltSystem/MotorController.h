#pragma once
#include "defines.h"
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
private:
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	int currentSteps;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
	enum MotorState
	{
		movingLeft, movingRight, Stop
	};
public:
	MotorController(Motor* Motor, SpeedProfile* Speedprofile);
	int setSpeed(double speed);
	int followProfile(int direction);
	int move(bool Direction); //time neccessary?
	int stop();
	
	//To do:
	double getCurrentSpeed(void);
	MotorState getCurrentMotorState(void);
	bool readyToRecvPayload(void);
	bool finishedProfile(void);
};

