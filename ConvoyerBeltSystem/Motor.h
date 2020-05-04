#pragma once

#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


extern "C" {
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
}

class Motor
{
public:
	Motor();
	~Motor();
	int initMotor();
	int setSpeed(int speed);
	int getSpeed();
	int startMotor(bool direction);
	int stopMotor();
private:
	unsigned short readBackValSPI = 0;
	int speed;
	gpioDescriptor* IN1;
	pwmDescriptor* pwmMotor;
	spiDescriptor* spiDescMotor;
	gpioDescriptor* bridgeEN;
	gpioDescriptor* bridgeDIS;
};

