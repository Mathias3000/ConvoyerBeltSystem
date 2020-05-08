#include "MotorController.h"

MotorController::MotorController(Motor* Motor, SpeedProfile* Speedprofile)
{
	printf("MotorController Konstruktor!\n");
	this->mySpeedProfile = Speedprofile;
	this->myMotor = Motor;
	this->myMotor->initMotor();
}

int MotorController::setSpeed(double speed)
{
	return this->myMotor->setSpeed(speed);
}

int MotorController::followProfile(int direction)
{
	return this->myMotor->followProfile(direction);
}

int MotorController::move(bool Direction)
{
	return this->myMotor->startMotor(Direction);
}

int MotorController::stop()
{
	return this->myMotor->stopMotor();
}
