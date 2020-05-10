#include "Potentiometer.h"
#include <string.h>

// using namespace std;

Potentiometer::Potentiometer()
{
	pinMux = new spiPinmux();
	
	strcpy(pinMux->CSpin, "P9_17_pinmux");
	strcpy(pinMux->MISOpin, "P9_21_pinmux");
	strcpy(pinMux->MOSIpin, "P9_18_pinmux");
	strcpy(pinMux->SCLKpin, "P9_22_pinmux");

	potiDesc = new spiDescriptor();
	potiDesc->spiNum = 1;	// spi0 for poti
	potiDesc->bitsPerWord = 8;
	potiDesc->mode = 0;		// for spi0
	potiDesc->speed = 1e6;	// max sampling rate with internal clock = 43 kSps
	potiDesc->flags = O_RDWR;	// O_RDWR needed? 
	potiDesc->pinmux = *pinMux;

	if (spiSetPinmux(potiDesc) < 0) {
		perror("Failed to set Pinmux for Potentiometer");
	}
	if (spiOpen(potiDesc) < 0) {
		perror("Failed to open spi for Potentiometer");
	}

}

int Potentiometer::getValue()
{
	readValue = spiXfer16Bits(potiDesc, controlByte);

	return readValue;
}
