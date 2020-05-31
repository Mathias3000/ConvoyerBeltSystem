#include "MotorController.h"

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	printf("MotorController Konstruktor!\n");
	this->myMotor->initMotor();
	this->workProfile = thread(&MotorController::followProfile, this);
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

int MotorController::move(bool direction)
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
			if (myMotor->getDirection() == Right) {
				this->myMotor->setStatus(movingRight);
			}
			else if (myMotor->getDirection() == Left) {
				this->myMotor->setStatus(movingLeft);
			}
			steps = 0;
			int speed = this->getConfiguredSpeedRPM();
			int desiredSpeed, currentSpeed, error;
			while (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN) && this->myMotor->getStatus() != Stop) {
				steps = this->mySpeedProfile->getStepCounter();
				//accelerate
				if (steps <= RAMP_UP) {
					desiredSpeed = (steps * speed /  RAMP_UP);
					currentSpeed = this->getCurrentSpeedInRPM();
					error = desiredSpeed - currentSpeed;
					Discrete_U.u = error;
					this->oneStep();
					double outputInvolts = (Discrete_Y.y);
					double duty = (outputInvolts * PWM_PER) / 7;
					this->setMotorDutyCycle((int)duty);
				}
				//steady
				else if (steps > RAMP_UP && steps <= (RAMP_UP + RAMP_STEADY)) {}
				//decelerate
				else if (steps > (RAMP_UP + RAMP_STEADY) && steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
					desiredSpeed = (((RAMP_UP + RAMP_STEADY + RAMP_DOWN) - steps) * speed) / RAMP_DOWN;
					currentSpeed = this->getCurrentSpeedInRPM();
					error = desiredSpeed - currentSpeed;
					Discrete_U.u = error;
					this->oneStep();
					double outputInvolts = (Discrete_Y.y);
					double duty = (outputInvolts * PWM_PER) / 7;
					this->setMotorDutyCycle((int)duty);
				}
				usleep(18000);
			}
			if (this->myMotor->getStatus() != Stop) this->resetStepCounter();
			this->myMotor->stopMotor();
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

double MotorController::getCurrentSpeedInRPM()
{
	return this->myMotor->getCurrentSpeed();
}

/*
int MotorController::updateController()
{
	int steps, value;
	while (steps < 400 && this->myMotor->getStatus() != Stop) {
		steps = myMotorController->getStepCounter();
		//accelerate
		if (steps <= RAMP_UP) {
			value = (steps * PWM_PER * speed / (MAX_SPEED_RPM * RAMP_UP));
			pwmSetDuty_B(this->myMotor->pwmMotor, value);
		}
		//steady
		else if (steps <= RAMP_STEADY) {}
		//decelerate
		else if (steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
			value = (400 - steps) * PWM_PER * speed / (MAX_SPEED_RPM * RAMP_DOWN);
			pwmSetDuty_B(this->myMotor->pwmMotor, value);
		}
	}
	int speedConfigured = myMotorController->getConfiguredSpeedRPM();
	int currrentSpeed = myMotorController->getCurrentSpeedInRPM();
	int error = speedConfigured - currrentSpeed;
	Discrete_U.u = error;
	myMotorController->oneStep();
	double outputInvolts = (Discrete_Y.y);
	double duty = (outputInvolts * 50000) / 7;
	myMotorController->setMotorDutyCycle((int)duty);
	return 0;
}
*/
void MotorController::oneStep()
{
	myMotor->oneStep();
}

 

