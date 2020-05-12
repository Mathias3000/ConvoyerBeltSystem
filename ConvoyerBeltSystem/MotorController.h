#pragma once

#include <pthread.h>

#include "defines.h"
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:
	MotorController(Motor* motor, SpeedProfile* profile);
	int setSpeed(double speed);
	int initProfile(Direction direction); //to set the gpio for direction and refresh myMotor.state
	int move(bool Direction); //time neccessary?
	int stop();

	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int updateMotorDuty();
	MotorState getMotorState();
	long getCurrentSpeed();
	//To do:
	bool readyToRecvPayload(void);
	bool finishedProfile(void);
private:
	int stepIncrements;
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	int currentSteps;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

