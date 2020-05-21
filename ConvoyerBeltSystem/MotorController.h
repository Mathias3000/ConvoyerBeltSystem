#pragma once

#include <thread>
#include "defines.h"
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:
	MotorController(Motor* motor, SpeedProfile* profile); //call init() and starts thread, which polls variable 'profileRunning' --> startProfile() sets the variable to true
	int setSpeed(double speed); 
	Direction setDirection(Direction direction);
	int move(bool Direction); //starts motor in Direction
	int stop(); //resets the step counter! Neccessary to memorize step counter?!
	MotorState getMotorState();
	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int startProfile();
	long getCurrentSpeed();
	//To do:
	bool readyToRecvPayload();
	bool finishedProfile();
private:
	//notwendig?
	int followProfile();
	bool profileRunning;
	int stepIncrements;
	int currentSteps;
	double currentSpeed;
	//current State not used for now:
	char currentState[MAX_STATE_NAME];
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

