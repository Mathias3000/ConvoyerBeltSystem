#include "Mode.h"

int Mode::displayUserInterface()
{
	this->stop = false;
	while (!stop)
	{
		MotorState motorState = this->motorController->getMotorState();
		// getPotiValue
		// getKeypadValue
		// display data 
		�sleep(100000);
	}
	return 0;
}
