#pragma once
#include "defines.h"
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:
	enum MotorState
	{
		movingLeft, movingRight, Stop
	};
	MotorController(Motor* motor, SpeedProfile* profile);
	int setSpeed(double speed);
	int followProfile(int direction); //followProfile() is still in Motor.h -> change to SpeedProfile
	int move(bool Direction); //time neccessary?
	int stop();

	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();

	//To do:
	double getCurrentSpeed(void);
	MotorState getCurrentMotorState(void);
	bool readyToRecvPayload(void);
	bool finishedProfile(void);
private:
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	int currentSteps;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

