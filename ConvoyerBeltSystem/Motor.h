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
#include <cmath>
#include "Encoder.h"
#include "Controller.h"

extern "C" {
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
}

class Motor
{
public:
	Motor();
	Motor(Encoder* encoder, Controller* controller);
	~Motor();
	int initMotor(); //init the spi connection and configure with default values
	int setSpeed(double speed); //0-100
	int getSpeed();
	int setDirection(bool direction);
	int startMotor(bool direction); 
	int stopMotor();
	bool isStopped();
	
	//To dos:
	double getCurrentSpeed();
	int getCurrentStatus();

	//no good design, needs fixing: 
	gpioDescriptor* IN1;
	pwmDescriptor* pwmMotor;
	spiDescriptor* spiDescMotor;
	gpioDescriptor* bridgeEN;
	gpioDescriptor* bridgeDIS;
	bool motorStopped = true;

private:
	unsigned short readBackValSPI = 0;
	double speed = 0;
	bool direction;
	Encoder* myEncoder;
	Controller* myController;
};

