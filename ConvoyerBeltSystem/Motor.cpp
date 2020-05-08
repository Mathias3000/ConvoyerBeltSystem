#include "Motor.h"

Motor::Motor()
{
	printf("Motor Konstruktor!\n");
	//Create instances for hardware usage
	this->IN1 = new gpioDescriptor;
	this->pwmMotor = new pwmDescriptor;
	this->spiDescMotor = new spiDescriptor;
	this->bridgeEN = new gpioDescriptor;
	this->bridgeDIS = new gpioDescriptor;
}

int Motor::initMotor()
{
	this->bridgeEN->gpioNum = 79;
	strcpy(this->bridgeEN->direction, "out");
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

	this->IN1->gpioNum = 22;
	strcpy(this->IN1->direction, "out");
	if (gpioOpen(this->IN1) < 0) return -1;
	//default direction: 
	if (gpioSetValue(this->IN1, 1) < 0) return -1;

	strcpy(this->pwmMotor->pinNameB, "P8_13_pinmux");
	this->pwmMotor->pwmNum = 7;
	if (pwmSetPinmux_B(this->pwmMotor) < 0) return -1;
	if (pwmOpen_B(this->pwmMotor) < 0) return -1;
	if (pwmSetPeriod_B(this->pwmMotor, 50000) < 0) return -1;
	//if (pwmSetDuty_B(this->pwmMotor, 35000)) return -1;
	if (pwmSetPolarity_B(this->pwmMotor, 0)) return -1;
	printf("SPI for Motor initialized!\n");
	return 0;
}

int Motor::setSpeed(double speed)
{
	if (speed >= 0 && speed <= 100) {
		this->speed = speed;
		return 0;
	}
	else {
		this->speed = 0;
		printf("speed should be between 0 - 100!\n");
		return -1;
	}
}

int Motor::getSpeed()
{
	return this->speed;
}

int Motor::startMotor(bool direction)
{	
	if (direction == 0) {
		gpioSetValue(this->IN1, 1);
		pwmSetDuty_B(this->pwmMotor, this->speed * PWM_PER / MAX_SPEED);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->motorStopped = false;
		return 1;
	}
	else if (direction == 1) {
		gpioSetValue(this->IN1, 0);
		pwmSetDuty_B(this->pwmMotor, this->speed * PWM_PER / MAX_SPEED);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->motorStopped = false;
		return 1;
	}
	else return -1;
}

int Motor::stopMotor()
{
	if (pwmSetEnable_B(pwmMotor, 0) < 0) return -1;
	this->motorStopped = true;
	return 0;
}

int Motor::followProfile(bool direction)
{
	unsigned short countPrev = 0;
	double speed = 0;
	if (direction == 0) {
		gpioSetValue(this->IN1, 1);
		pwmSetDuty_B(this->pwmMotor, 1);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->motorStopped = false;
	}
	else if (direction == 1) {
		gpioSetValue(this->IN1, 0);
		pwmSetDuty_B(this->pwmMotor, 1);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->motorStopped = false;
	}
	do {
		if (countPrev != stepCounterFollowProf) {
			countPrev = stepCounterFollowProf;
			//accelerate
			if (stepCounterFollowProf <= RAMP_UP) {
				pwmSetDuty_B(this->pwmMotor, speed * PWM_PER / MAX_SPEED);
				speed = (speed + (this->speed / 50));
			}
			//steady speed
			else if (stepCounterFollowProf <= RAMP_STEADY) {}
			//decelerate
			else if (stepCounterFollowProf < RAMP_DOWN) {
				speed = (speed - (this->speed / 50));
				pwmSetDuty_B(this->pwmMotor, speed * PWM_PER / MAX_SPEED);
			}
			//stop Motor
			else if (stepCounterFollowProf >= RAMP_DOWN) {
				this->stopMotor();
				this->motorStopped = true;
			}
		}
	} while (stepCounterFollowProf <= 400 && this->motorStopped == false); //Motor muss auf jeden Fall stoppen, da this.motorStopped = true sonst nur in this.stopMotor() passieren kann...
	
	return 0;
}

int Motor::setDirection(bool direction)
{	
	this->direction = direction;
	return 0;
}
