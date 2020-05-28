#include "Encoder.h"

Encoder::Encoder()
{ 
	printf("Encoder Konstruktor!\n");
	this->qepMotor = new qepDescriptor;
	this->init();
	threadPollEncoder = thread(&Encoder::pollEncoder, this);
	threadCalcSpeed = thread(&Encoder::calcSpeed, this);
}

int Encoder::init()
{	
	strcpy(this->qepMotor->qepNum, "48302000.epwmss/48302180.eqep");
	strcpy(this->qepMotor->pinNameA, "P8_35_pinmux");
	strcpy(this->qepMotor->pinNameB, "P8_33_pinmux");
	strcpy(this->qepMotor->pinNameIndex, "P8_31_pinmux");
	int err = qepSetPinmux(this->qepMotor);
	err = qepSetMode(this->qepMotor, 1);
	err = qepSetPeriod(this->qepMotor, ENC_DELAY_NSEC); 
	printf("Encoder initialized!\n");
	return err;
}

void Encoder::pollEncoder()
{	
	while (true)
	{
		this->encVal = qepGetPosition(this->qepMotor);
		usleep(ENC_DELAY_READ_QEP);
	}
}

void Encoder::calcSpeed()
{
	while (true)
	{	
		double rpm = (((encVal * (1 / ENC_DELAY_SEC) * 60) / ENC_TICKS_PER_TURN));
		if (rpm < 0) rpm = rpm * (-1); 
		this->rpm = rpm;
		usleep(ENC_DELAY_CALC_SPEED);
	}
}
	
double Encoder::getSpeedRPM()
{
	return this->rpm;
}



