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
	int setSpeedInRPM(int speed); 
	int getConfiguredSpeedRPM();
	Direction getConfiguredDirection();
	int setDirection(Direction direction);
	int setMotorDutyCycle(int duty);
	int move(bool Direction); 
	int enableMotorPWM();
	int stop(); //resets the step counter! Neccessary to memorize step counter?!
	MotorState getMotorState();
	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int startProfile();
	double getCurrentSpeedInRPM();
	//int updateController();
	void oneStep();

	bool readyToRecvPayload();
	bool finishedProfile();
private:
	int followProfile();
	bool profileRunning = false;
	int currentSteps;
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	thread workProfile;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

