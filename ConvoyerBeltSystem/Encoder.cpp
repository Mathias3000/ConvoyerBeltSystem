#include "Encoder.h"

Encoder::Encoder()
{ 
	printf("Encoder Konstruktor!\n");
	this->qepMotor = new qepDescriptor;
	this->init();
}

void Encoder::init()
{	
	strcpy(this->qepMotor->qepNum, "48302000.epwmss/48302180.eqep");
	strcpy(this->qepMotor->pinNameA, "P8_35_pinmux");
	strcpy(this->qepMotor->pinNameB, "P8_33_pinmux");
	strcpy(this->qepMotor->pinNameIndex, "P8_31_pinmux");
	int err = qepSetPinmux(this->qepMotor);
	unsigned char mode = '1';
	err = qepSetMode(this->qepMotor, mode);
	err = qepSetPeriod(this->qepMotor, 50000); 
}

long Encoder::getSpeed(void)
{	
	long val = qepGetPosition(this->qepMotor);
	//calculate speed!!!
	return val;
}

