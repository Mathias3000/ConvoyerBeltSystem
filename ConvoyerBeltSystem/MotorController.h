#pragma once

#include <thread>
#include "defines.h"
#include <iostream>
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:

	MotorController(Motor* motor, SpeedProfile* profile); //call init() and starts thread, which polls variable 'profileRunning' --> startProfile() sets the variable to true
	//move for time 1s !!! implementieren!
	int move(Direction Direction);
	int stop(); //resets the step counter! Neccessary to memorize step counter?!
	int setSpeedInRPM(int speed); 
	int getConfiguredSpeedRPM();
	double getCurrentSpeedRPM();
	int setMotorDutyCycle(int duty);
	int enableMotorPWM();
	Direction getConfiguredDirection();
	int setDirection(Direction direction);
	MotorState getMotorState();
	int setMotorState(MotorState state);

	enum MotorState
	{
		movingLeft, movingRight, Stop
	};
	MotorController();
	MotorController(Motor* motor, SpeedProfile* profile);
	
	int setDirection(int direction);
	int move(bool Direction); //time neccessary?
	int stop();


	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int startProfile();
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
	thread threadFollowProfile;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

