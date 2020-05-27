#include "MotorController.h"

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
	//this->workProfile = thread(&MotorController::followProfile, this);
}

int MotorController::setSpeedPercent(int speed)
{
	return this->myMotor->setSpeed(speed);
}

int MotorController::getConfiguredSpeedPercent()
{
	return this->myMotor->getSpeed();
}

int MotorController::setDirection(Direction direction)
{
	return myMotor->setDirection(direction);
}

int MotorController::move(bool direction)
{
	if (direction == Right) this->myMotor->setStatus(movingRight);
	else this->myMotor->setStatus(movingLeft);
	return this->myMotor->startMotor(direction);
}

int MotorController::stop()
{	
	this->resetStepCounter();
	return this->myMotor->stopMotor();
}

int MotorController::getStepCounter()
{
	return this->mySpeedProfile->getStepCounter();
}

int MotorController::resetStepCounter()
{
	return this->mySpeedProfile->resetStepCounter();
}

int MotorController::incrementStepCounter()
{
	return this->mySpeedProfile->incrementStepCounter();
}

int MotorController::startProfile()
{
	if (this->profileRunning == true){
		printf("Profile already running!");
		return -1;
	}
	else if (this->profileRunning == false)
	{
		this->profileRunning = true;
		return 0;
	}
}

int MotorController::followProfile()
{	
	unsigned int steps = 0;
	double referenceVal, measuredVal, error;
	pwmSetDuty_B(this->myMotor->pwmMotor, 1);
	pwmSetEnable_B(this->myMotor->pwmMotor, 1);
	while (true)
	{
		if (this->profileRunning == true) {
			if (myMotor->getDirection() == Right) {
				this->myMotor->setStatus(movingRight);
			}
			else if (myMotor->getDirection() == Left) {
				this->myMotor->setStatus(movingLeft);
			}
			steps = 0;
			while (steps < 400 && this->myMotor->getStatus() != Stop) {
				steps = this->mySpeedProfile->getStepCounter();
				referenceVal = 
				measuredVal = 
				error = 
				//accelerate
				if (steps <= RAMP_UP) {
					int value = (steps * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_UP));
					pwmSetDuty_B(this->myMotor->pwmMotor, value);
				}
				//steady
				else if (steps <= RAMP_STEADY) {}
				//decelerate
				else if (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
					pwmSetDuty_B(this->myMotor->pwmMotor, (400 - steps) * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_DOWN));
				}
			}
			this->myMotor->stopMotor();
			this->resetStepCounter();
			this->profileRunning = false;
		}
		usleep(250);
	}
	return 0;
}

MotorState MotorController::getMotorState()
{
	return this->myMotor->getStatus();
}

double MotorController::getCurrentSpeed()
{
	return this->myMotor->getCurrentSpeed();
}

void MotorController::oneStep()
{
	myMotor->oneStep();
}

 

