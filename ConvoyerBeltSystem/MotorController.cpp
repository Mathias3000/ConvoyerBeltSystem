#include "MotorController.h"

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
}

int MotorController::setSpeed(double speed)
{
	return this->myMotor->setSpeed(speed);
}

int MotorController::followProfile(int direction)
{
	/*
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
	
	*/
}

int MotorController::move(bool Direction)
{
	return this->myMotor->startMotor(Direction);
}

int MotorController::stop()
{
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
