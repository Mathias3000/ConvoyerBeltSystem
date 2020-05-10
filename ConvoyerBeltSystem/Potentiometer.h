#pragma once
#include <string>
#include <fcntl.h>

extern "C" {
	#include "spi.h"
	#include "gpio.h"
}

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

};

// salam
// i am fine
// Cvid was bas
// has to stay at home for 1 month no work no school
// now better. had 15k cases now 1k new active cases
// do you have school or work or are you still staying at home


