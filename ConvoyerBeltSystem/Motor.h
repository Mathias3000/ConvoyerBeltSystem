#pragma once

#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cmath>
#include "defines.h"
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
	Motor(Encoder* encoder, Controller* controller);
	~Motor();
	int initMotor(); 
	int setSpeed(double speed); //0-100
	int getSpeed();
	int setDirection(Direction direction);
	Direction getDirection();
	int startMotor(bool direction); 
	int stopMotor();
	double getCurrentSpeed();
	MotorState setStatus(MotorState motorstate);
	MotorState getStatus();
	//no good design, needs fixing!: 
	gpioDescriptor* IN1;
	pwmDescriptor* pwmMotor;
	spiDescriptor* spiDescMotor;
	gpioDescriptor* bridgeEN;
	gpioDescriptor* bridgeDIS;
private:
	unsigned short readBackValSPI;
	double speed;
	MotorState state;
	Direction direction;
	Encoder* myEncoder;
	Controller* myController;
};

