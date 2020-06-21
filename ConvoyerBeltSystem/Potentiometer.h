#pragma once
#include <string>
#include <fcntl.h>
#include <math.h>

extern "C" {
	#include "spi.h"
	#include "gpio.h"
}

#define ADC_MAX_VAL 65535.0f
#define SPEED_MAX 2200.0f
#define SPEED_MIN 110.0f

class Potentiometer
{
private: 
	spiPinmux* pinMux;
	spiDescriptor* potiDesc;

	uint16_t readValue = 0;
	unsigned short controlByte = 0b10010000;	// from datasheet
	int a = 0;

public : 

	Potentiometer();
	int getValue();
	int getSpeed();

};




