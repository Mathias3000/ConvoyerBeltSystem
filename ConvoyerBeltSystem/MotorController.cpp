#include "MotorController.h"

//typedef void* (*THREADFUNCPTR)(void*);
//pthread_t threadSpeedProfile;

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
}

int MotorController::setSpeed(double speed)
{
	this->stepIncrements = speed / 50;
	return this->myMotor->setSpeed(speed);
}

int MotorController::initProfile(Direction direction)
{
	this->myMotor->setDirection(direction);
	if (direction == Right) this->myMotor->setStatus(movingRight);
	else this->myMotor->setStatus(movingLeft);
	pwmSetDuty_B(this->myMotor->pwmMotor, 1);
	pwmSetEnable_B(this->myMotor->pwmMotor, 1);
	if (direction == Right) {
		gpioSetValue(this->myMotor->IN1, 1);
		this->myMotor->setStatus(movingRight);
	}
	else if (direction == Left) {
		gpioSetValue(this->myMotor->IN1, 0);
		this->myMotor->setStatus(movingLeft);
	}
}

int MotorController::move(bool Direction)
{
	return this->myMotor->startMotor(Direction);
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

int MotorController::updateMotorDuty()
{	
	unsigned int steps = this->mySpeedProfile->getStepCounter();
	if (steps <= RAMP_UP) {
		pwmSetDuty_B(this->myMotor->pwmMotor, (this->stepIncrements * steps * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_UP)));
	}

	else if (steps <= RAMP_STEADY) {}

	else if (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
		pwmSetDuty_B(this->myMotor->pwmMotor, (this->stepIncrements * (400 - steps) * PWM_PER * this->myMotor->getSpeed() / (MAX_SPEED * RAMP_DOWN)));
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

 

