#pragma once
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "defines.h"
#include <thread>

using namespace std;

extern "C" {
#include "qep.h"
}

class Encoder
{
private:
	double currentSpeed;
	qepDescriptor* qepMotor;
	long encVal, speed;
	//threads for pollin the encoder and calculatin the speed 
	void pollEncoder(); 
	void calcSpeed();
	int init();
public:
	Encoder();
	long getSpeedRPM();
};
