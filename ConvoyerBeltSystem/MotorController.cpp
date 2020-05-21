#include "MotorController.h"

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
	thread threadProfile(&MotorController::followProfile, this);
	threadProfile.detach();
}

int MotorController::setSpeed(double speed)
{
	this->stepIncrements = speed / 50;
	return this->myMotor->setSpeed(speed);
}

Direction MotorController::setDirection(Direction direction)
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
	this->profileRunning = true;
}

int MotorController::followProfile()
{	
	unsigned int steps;
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
			while (steps <= 400 && this->myMotor->getStatus() != Stop) {
				steps = this->mySpeedProfile->getStepCounter();
				//accelerate
				if (steps <= RAMP_UP) {
					pwmSetDuty_B(this->myMotor->pwmMotor, (this->stepIncrements * steps * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_UP)));
				}
				//steady
				else if (steps <= RAMP_STEADY) {}
				//decelerate
				else if (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
					pwmSetDuty_B(this->myMotor->pwmMotor, (this->stepIncrements * (400 - steps) * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_DOWN)));
				}
			}
			this->profileRunning = false;
			this->resetStepCounter();
			this->myMotor->setStatus(Stop);
		}
		usleep(10000);
	}
	return 0;
}

MotorState MotorController::getMotorState()
{
	return this->myMotor->getStatus();
}

long MotorController::getCurrentSpeed()
{
	return this->myMotor->getCurrentSpeed();
}

 

