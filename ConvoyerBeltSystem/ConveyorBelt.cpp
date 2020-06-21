#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt()
{
	init();
}

ConveyorBelt::~ConveyorBelt()
{
	delete this;
}

void ConveyorBelt::stopDisplayUI()
{
	this->stop == true;
}

void ConveyorBelt::init()
{
	// Instiate local and chain mode + set local default
	// use singleton design pattern to avoid multiple instances of local and chain mode
	currentMode = ChainMode::getInstance();
	currentMode = LocalMode::getInstance();
	this->workerDisplayUI = thread(&ConveyorBelt::displayUI, this); //start thread Display UI
}

void ConveyorBelt::showDisplayOutput()
{
	this->currentMode->display->displayClear();

	//display the very top lines
	for (int i = 0; i < 7; i++) {
		this->currentMode->display->displayLine(commands[i]);
	}
	for (int i = 0; i < 4; i++) {
		this->currentMode->display->displayLine(commands2[i]);
	}

	usleep(10000);
	string s = typeid(*myConveyorBelt->currentMode).name();
	char* writable = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), writable);
	writable[s.size()] = '\0'; // don't forget the terminating 0
	char* data = writable + 1;

	char* currentOpMode[2] = {
		stringToCharArray(new string("SYSTEM PARAMETERS: ")),
		stringToCharArray(new string("current operation mode: " + string(data)))
	};

	// TODO: in one line: concat char*
	for (int i = 0; i < 2; i++) {
		this->currentMode->display->displayLine(currentOpMode[i]);
	}

	char* currentState[4] = {
		"",
		"current states in statemaschine: ",
		"[LOCAL diagram]\t\t\t[CHAIN diagram]",
		stringToCharArray(new string(myStateMaschine->actualState[0] + "\t\t\t\t" + myStateMaschine->actualState[1]))
	};
	for (int i = 0; i < 4; i++) {
		this->currentMode->display->displayLine(currentState[i]);
	}

	string dir;
	if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == 0) {
		dir = "Right";
	}
	else
	{
		dir = "Left";
	}

	string state;
	switch (myConveyorBelt->currentMode->motorController->getMotorState())
	{
	case MotorState::movingLeft: 
		state = "MovingLeft";
		break;
	case MotorState::movingRight: 
		state = "MovingRight";
		break;
	case MotorState::Stop: 
		state = "Stop";
		break;
	default:
		break;
	}

	char* motorInfo[10] = {
		"",
		"MOTOR PARAMETERS: ",
		stringToCharArray(new string("defined max speed: \t" + to_string(myConveyorBelt->currentMode->motorController->getConfiguredSpeedRPM()) + "rpm")),
		stringToCharArray(new string("direction: \t\t" + dir)),
		stringToCharArray(new string("motor state: \t\t" + state)), 
		"",
		"Note: - After starting program, select Local or Chain Mode first. ",
		"      - Display requires longer for updates when changing operation modes. ",
		"================================================================================",
		"CURRENT ACTIONS",
	};
	for (int i = 0; i < 10; i++) {
		this->currentMode->display->displayLine(motorInfo[i]);
	}

	// print current action
	this->currentMode->display->displayLine(stringToCharArray(currentAction));

}

int ConveyorBelt::displayUI()
{
	while (!stop)
	{
		// test
		// displayMutex.lock();
		showDisplayOutput();
		usleep(500000);
		// this_thread::sleep_for(chrono::milliseconds(300));		

	}
	return 0;
}


