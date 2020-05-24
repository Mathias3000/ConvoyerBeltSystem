#pragma once
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "defines.h"
#include <thread>
#include <cstdlib>

using namespace std;

extern "C" {
#include "qep.h"
}

// Creates two threads, one to poll the Encoder, one to calculate the current speed, running forever!
class Encoder
{
private:
	int encVal;
	double rpm;
	qepDescriptor* qepMotor;
	thread threadPollEncoder;
	thread threadCalcSpeed;
	void pollEncoder();
	void calcSpeed();
	int init();
public:
	Encoder();
	double getSpeedRPM();
};
