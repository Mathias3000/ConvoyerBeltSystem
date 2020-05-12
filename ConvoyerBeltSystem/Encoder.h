#pragma once
#include <string.h>
#include <stdio.h>

extern "C" {
#include "qep.h"
}

class Encoder
{
private:
	double currentSpeed;
	qepDescriptor* qepMotor;
public:
	Encoder();
	void init();
	long getSpeed(void);
};
