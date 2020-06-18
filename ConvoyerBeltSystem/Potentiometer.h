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

// salam
// i am fine
// Cvid was bas
// has to stay at home for 1 month no work no school
// now better. had 15k cases now 1k new active cases
// do you have school or work or are you still staying at home


