#pragma once


#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "defines.h"
#include "systemManager.h"
#include <cmath>

extern "C" {
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
}

extern int stepCounterFollowProf; //declared in systemManager.cpp

class Motor
{
public:
	Motor();
	~Motor();
	int initMotor(); //init the spi connection and configure with default values
	int setSpeed(double speed); //0-100
	int getSpeed();
	int setDirection(bool direction);
	int startMotor(bool direction); 
	int stopMotor();
	int followProfile(bool direction); //depends on polling a global variable named stepCounterFollowProf (timer should do the increment steps every 20ms)
	
	double getCurrentSpeed();
	int getCurrentStatus();

private:
	unsigned short readBackValSPI = 0;
	double speed = 0;
	bool direction;
	bool motorStopped = true;
	gpioDescriptor* IN1;
	pwmDescriptor* pwmMotor;
	spiDescriptor* spiDescMotor;
	gpioDescriptor* bridgeEN;
	gpioDescriptor* bridgeDIS;
};

