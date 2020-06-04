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
	int setSpeedRPM(int speed); 
	int getSpeed();
	int setDutyCycle(int duty);
	int setDirection(Direction direction);
	Direction getDirection();
	int startMotor(bool direction); 
	int stopMotor();
	double getCurrentSpeed();

	void oneStep();

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
	int speed;
	MotorState state = Stop;
	Direction direction;
	Encoder* myEncoder;
	Controller* myController;
};

