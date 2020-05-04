#include "Motor.h"

Motor::Motor()
{
	printf("Motor Konstruktor!");
	IN1 = new gpioDescriptor;
	pwmMotor = new pwmDescriptor;
	spiDescMotor = new spiDescriptor;
	bridgeEN = new gpioDescriptor;
	bridgeDIS = new gpioDescriptor;
}

int Motor::initMotor()
{
	//gpioDescriptor* bridgeEN = new gpioDescriptor;
	this->bridgeEN->gpioNum = 79;
	strcpy(this->bridgeEN->direction, "out");
	//gpioDescriptor* bridgeDIS = new gpioDescriptor;
	this->bridgeDIS->gpioNum = 76;
	strcpy(this->bridgeDIS->direction, "out");

	gpioOpen(this->bridgeEN);
	if (gpioSetValue(this->bridgeEN, 1) < 0) return -1;
	gpioOpen(this->bridgeDIS);
	if (gpioSetValue(this->bridgeDIS, 0) < 0) return -1;
	
	spiPinmux spiMotor;
	spiPinmux& spiMotorRef = spiMotor;
	strcpy(spiMotorRef.CSpin, "P9_28_pinmux");
	strcpy(spiMotorRef.MISOpin, "P9_29_pinmux");
	strcpy(spiMotorRef.MOSIpin, "P9_30_pinmux");
	strcpy(spiMotorRef.SCLKpin, "P9_31_pinmux");

	//spiDescriptor* spiDescMotor = new spiDescriptor;
	this->spiDescMotor->spiNum = 2;
	this->spiDescMotor->bitsPerWord = 8;
	this->spiDescMotor->mode = 1;
	this->spiDescMotor->flags = O_RDWR;
	this->spiDescMotor->speed = 1000000;
	this->spiDescMotor->pinmux = spiMotorRef;

	if (spiSetPinmux(this->spiDescMotor) < 0) return -1;
	if (spiOpen(this->spiDescMotor) < 0) return -1;

	spiXfer16Bits(this->spiDescMotor, 0xED18);
	usleep(50);
	this->readBackValSPI = spiXfer16Bits(this->spiDescMotor, 0x6D18);

	//gpioDescriptor* IN1 = new gpioDescriptor;
	this->IN1->gpioNum = 22;
	strcpy(this->IN1->direction, "out");
	if (gpioOpen(this->IN1) < 0) return -1;
	//default direction: 
	if (gpioSetValue(this->IN1, 1) < 0) return -1;

	//pwmDescriptor* pwmMotor = new pwmDescriptor;
	strcpy(this->pwmMotor->pinNameB, "P8_13_pinmux");
	this->pwmMotor->pwmNum = 7;
	if (pwmSetPinmux_B(this->pwmMotor) < 0) return -1;
	if (pwmOpen_B(this->pwmMotor) < 0) return -1;
	if (pwmSetPeriod_B(this->pwmMotor, 50000) < 0) return -1;
	if (pwmSetDuty_B(this->pwmMotor, 35000)) return -1;
	if (pwmSetPolarity_B(this->pwmMotor, 0)) return -1;
	return 0;
}

int Motor::setSpeed(int speed)
{
	if (speed >= 0 && speed <= 100) {
		this->speed = speed;
	}
	else return -1;
	return 0;
}

int Motor::startMotor(bool direction)
{	
	//speed is missing!!!
	if (direction == 0) {
		gpioSetValue(this->IN1, 1);
		pwmSetEnable_B(pwmMotor, 1);
	}
	if (direction == 1) {
		gpioSetValue(this->IN1, 0);
		pwmSetEnable_B(pwmMotor, 1);
	}
	return 0;
}

int Motor::stopMotor()
{
	pwmSetEnable_B(pwmMotor, 0);
	return 0;
}
