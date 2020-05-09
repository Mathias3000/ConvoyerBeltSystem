#include "MotorController.h"

int MotorController::followProfile(int direction)
{
	cout << "Following speed profile with direction " << direction << ". " << endl;
	return 0;
}

int MotorController::setSpeed(double speed)
{
	cout << "set speed to " << speed << " rpm" << endl;
	return 0; 
}

int MotorController::setDirection(int direction)
{
	cout << "Direction set to " << direction << ". " << endl;
	return 0;
}
