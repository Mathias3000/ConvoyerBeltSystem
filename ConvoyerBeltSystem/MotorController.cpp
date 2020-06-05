#include "MotorController.h"

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
	this->threadFollowProfile = thread(&MotorController::followProfile, this);
}

int MotorController::setSpeedInRPM(int speed)
{
	return this->myMotor->setSpeedRPM(speed);
}

int MotorController::getConfiguredSpeedRPM()
{
	return this->myMotor->getSpeed();
}

Direction MotorController::getConfiguredDirection()
{
	return myMotor->getDirection();
}

int MotorController::setDirection(Direction direction)
{
	return myMotor->setDirection(direction);
}

int MotorController::setMotorDutyCycle(int duty)
{
	int err = myMotor->setDutyCycle(duty);
	return err;
}

int MotorController::move(Direction direction)
{
	if (direction == Right) this->myMotor->setStatus(movingRight);
	else this->myMotor->setStatus(movingLeft);
	return this->myMotor->startMotor(direction);
}

int MotorController::enableMotorPWM()
{	
	int err = pwmSetEnable_B(this->myMotor->pwmMotor, 1);
	return err;
}

int MotorController::stop()
{	
	this->profileRunning = false;
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
	this->enableMotorPWM();
	if (this->profileRunning == true){
		printf("Profile already running!\n");
		return -1;
	}
	else if (this->profileRunning == false)
	{
		this->profileRunning = true;
		//usleep(100000); //sync time - for MotorState to be set
		return 0;
	}
}

int MotorController::followProfile()
{	
	unsigned int steps = 0;
	double output;
	while (true)
	{
		if (this->profileRunning == true) {
			pwmSetEnable_B(this->myMotor->pwmMotor, 1);
			steps = 0;
			MotorState debugState = myMotor->getStatus();
			int speed = this->getConfiguredSpeedRPM();
			int desiredSpeed, currentSpeed, error;
			Discrete_initialize();
			while (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN) && this->myMotor->getStatus() != Stop) {
				steps = this->mySpeedProfile->getStepCounter();
				//accelerate
				if (steps <= RAMP_UP) {
					desiredSpeed = (steps * speed / RAMP_UP);
					currentSpeed = this->getCurrentSpeedRPM();
					error = desiredSpeed - currentSpeed;
					Discrete_U.u = error;
					this->oneStep();
					double outputInvolts = (Discrete_Y.y);
					double duty = (outputInvolts * PWM_PER) / 7;
					this->setMotorDutyCycle((int)duty);
				}
				//steady
				else if (steps > RAMP_UP&& steps <= (RAMP_UP + RAMP_STEADY)) {}
				//decelerate
				else if (steps > (RAMP_UP + RAMP_STEADY) && steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
					desiredSpeed = (((RAMP_UP + RAMP_STEADY + RAMP_DOWN) - steps) * speed) / RAMP_DOWN;
					currentSpeed = this->getCurrentSpeedRPM();
					error = desiredSpeed - currentSpeed;
					Discrete_U.u = error;
					this->oneStep();
					double outputInvolts = (Discrete_Y.y);
					double duty = (outputInvolts * PWM_PER) / 7;
					this->setMotorDutyCycle((int)duty);
				}
				usleep(18000);
			}
			if (400 <= steps) {
				this->myMotor->stopMotor();
				this->resetStepCounter();
			}
			this->profileRunning = false;
		}
		usleep(500);
	}
	return 0;
}

MotorState MotorController::getMotorState()
{
	return this->myMotor->getStatus();
}

int MotorController::setMotorState(MotorState state)
{
	int err = this->myMotor->setStatus(state);
	return err;
}

double MotorController::getCurrentSpeedRPM()
{
	return this->myMotor->getCurrentSpeed();
}

void MotorController::oneStep()
{
	myMotor->oneStep();
}

 

