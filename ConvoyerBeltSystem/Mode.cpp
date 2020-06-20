#include "Mode.h"

Mode::Mode()
{
	motorController = new MotorController();
	display = new Display();
	receivedCommand = new Command();
	communication = UserInterface::getInstance();

}

